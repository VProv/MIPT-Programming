// Нахождение максимального потока на графе алгоритмом "Поднять и в начало".
// Провилков Иван. гр.593.
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using std::vector;
using std::list;
using std::min;

class CRaiseBegin {

public:

    CRaiseBegin( int _n, int _start, int _destination, vector< vector<int> >& _c ) :
        c( _c ), neighbors( _n ), current( _n ), e( _n, 0 ), h( _n, 0 ), f( _n, vector<int>( _n, 0 ) )
    {
        n = _n;
        start = _start;
        destination = _destination;
    }

    // Подъем вершины.
    // Для переполненной вершины u применима операция подъема, если все вершины,
    // для которых в остаточной сети есть ребра из u, расположены не ниже u.
    // В результате подъема высота текущей вершины становится на единицу больше высоты самый низкой смежной вершины в остаточной сети, 
    // вследствие чего появляется как минимум одно ребро, по которому можно протолкнуть поток.
    void relabel( int u )
    {
        int height = 2 * n;
        for( list<int>::iterator it = neighbors[u].begin(); it != neighbors[u].end(); ++it )
            if( c[u][*it] > f[u][*it] ) // >>
                height = min( height, h[*it] );
        h[u] = height + 1;
    }

    // Операция может применяться когда вершина переполнена.
    void push( int u, int v )
    {
        // Минимум из избытка вершины и остаточной пропускной способности.
        int flowValue = min( c[u][v] - f[u][v], e[u] );
        // Далее избыток вершины, остаточная пропускная способность и поток по обратному ребру уменьшаются на величину потока.
        // А избыток вершины и поток по ребру uv увеличиваются на ту же величину.
        f[u][v] += flowValue;
        f[v][u] = -f[u][v];
        e[u] -= flowValue;
        e[v] += flowValue;
    }

    // Операция, применяемая к переполненной вершине u, для того чтобы протолкнуть поток через допустимые ребра в смежные вершины,
    // при необходимости поднимая u, делая недопустимые ребра, выходящие из вершины u, допустимыми.
    // Операция завершится только тогда, когда избыток e(u) станет равным нулю, и ни подъем, ни перемещение указателя current[u] не влияет на значение e(u).
    bool discharge( int u )
    {
        // Флаг конца.
        bool relabeled = false;
        // Пока избыточный поток еще есть.
        while( e[u] > 0 ) {
            if( current[u] == neighbors[u].end() ) { // Если мы на конце.
                relabel( u );
                relabeled = true;
                current[u] = neighbors[u].begin(); // >>
                continue;
            }
            int v = *current[u];
            if( c[u][v] > f[u][v] && h[u] == h[v] + 1 ) {
                push( u, v );
            }
            else {
                current[u]++;
            }
        }
        return relabeled;
    }

    // Инициализируем предпоток.
    void initializePreflow()
    {
        // Пропустим максимально возможный поток по ребрам, инцидентным истоку, 
        // увеличив избыточный поток для каждой смежной с истоком вершиной на соответствующую величину.
        for( int u = 0; u < n; ++u )
            if( c[start][u] > 0 ) {
                f[start][u] = c[start][u];
                f[u][start] = -f[start][u];
                e[u] = c[start][u];
                e[start] -= c[start][u];
            }
        h[start] = n;
    }

    // Сам алгоритм, возвращает значение максимального потока.
    int raiseToBegin()
    {
        initializePreflow();
        // Построим вектор списков соседей для каждой вершины.
        for( int u = 0; u < n; ++u ) {
            for( int v = 0; v < n; ++v )
                if( c[u][v] > 0 || c[v][u] > 0 )
                    neighbors[u].push_back( v );
            if( u != start && u != destination ) {
                current[u] = neighbors[u].begin();
            }
        }
        // Все вершины кроме стока и истока.
        list<int> selectedVertices;
        for( int u = 0; u < n; ++u )
            if( u != start && u != destination )
                selectedVertices.push_back( u );

        list<int>::iterator curVert = selectedVertices.begin();
        while( curVert != selectedVertices.end() ) {
            /*int u = *curVert;
            if( discharge( u ) ) {
            // Передвигаем в начало списка.
            selectedVertices.erase( curVert );
            curVert = selectedVertices.insert( selectedVertices.begin(), u );
            }
            curVert++;*/
            int u = *curVert;
            int oldHeight = h[u];
            discharge( u );
            if( h[u] > oldHeight ) {
                selectedVertices.erase( curVert );
                selectedVertices.push_front( u );
                curVert = selectedVertices.begin();
            }
            curVert++;
        }
        return e[destination];
    }

private:
    // Количество вершин графа.
    int n;
    // Номер истока (с 0).
    int start;
    // Номер стока.
    int destination;
    // Предпоток.
    vector<vector<int> > f;
    // Начальные пропускные способности, наш граф.
    vector<vector<int> >& c;
    // Высота вершин.
    vector<int> h;
    // Избыточный поток входящий в вершину.
    vector<int> e;
    // Для каждой вершины храним список смежных вершин, в том смысле что есть ребра uv или vu.
    vector<list<int> > neighbors;
    vector<list<int>::iterator > current;
};


using namespace std;
int main()
{
    int i = 0, j = 0, edgeCount = 0;
    int n = -1, start = 0, destination = 0;
    cin >> n;
    while( n != 0 ) {
        cin >> start >> destination >> edgeCount;
        start--;
        destination--;
        vector< vector<int> > c( n, vector<int>( n, 0 ) );
        while( edgeCount-- ) {
            int val = 0;
            cin >> i >> j >> val;
            i--;
            j--;
            c[i][j] += val;
            c[j][i] += val;
        }

        // Находим максимальный поток.
        CRaiseBegin solveClass( n, start, destination, c );
        int result = solveClass.raiseToBegin();
        cout << result << endl;
        cin >> n;
    }
    return 0;
}