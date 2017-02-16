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
        for( vector<int>::iterator it = neighbors[u].begin(); it != neighbors[u].end(); ++it )
            if( c[u][*it] > f[u][*it] ) 
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
    vector<vector<int> >& getFlow() {
        return f;
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
    vector<vector<int> > neighbors;
    vector<vector<int>::iterator > current;
};



#include <vector>
#include <string>
#include <queue>

using std::vector;
using std::string;
using std::pair;
using std::queue;

class CHamming {

public:
    CHamming( string& _st, string& _temp ) :
        st( _st ), temp( _temp ) {}

    void solveHamming() {
        int questionNum = 0;
        int stSize = st.size();
        int tempSize = temp.size();
        // Изначально все элементы массива индексов -1.
        stIndex.assign( stSize, -1 );
        tempIndex.assign( tempSize, -1 );
        index.push_back( std::make_pair( false, -1 ) );
        // Считаем количество вопросиков.
        for( int i = 0; i < stSize; ++i ) {
            if( st[i] == '?' ) {
                index.push_back( std::make_pair( false, i ) );
                stIndex[i] = questionNum + 1;
                questionNum++;
            }
        }
        for( int i = 0; i < tempSize; ++i ) {
            if( temp[i] == '?' ) {
                index.push_back( std::make_pair( true, i ) );
                tempIndex[i] = questionNum + 1;
                questionNum++;
            }
        }
        index.push_back( std::make_pair( false, -2 ) );
        graph.assign( questionNum + 2, vector<int>( questionNum + 2, 0 ) );
        int start = 0;
        int destination = questionNum + 1;
        int conflicts = 0;

        for( int i = 0; i < stSize - tempSize + 1; ++i ) {
            for( int j = 0; j < tempSize; ++j ) {
                if( ( st[j + i] == '1' && temp[j] == '0' ) || ( st[j + i] == '0' && temp[j] == '1' ) ) {
                    conflicts++;
                }
                else if( st[j + i] == '?' && temp[j] == '0' ) {
                    graph[stIndex[j + i]][0] += 1;
                    graph[0][stIndex[j + i]] += 1;
                }
                else if( st[j + i] == '?' && temp[j] == '1' ) {
                    graph[stIndex[j + i]][questionNum + 1] += 1;
                    graph[questionNum + 1][stIndex[j + i]] += 1;
                }
                else if( temp[j] == '?' ) {
                    if( st[j + i] == '?' ) {
                        graph[tempIndex[j]][stIndex[j + i]] = 1;
                        graph[stIndex[j + i]][tempIndex[j]] = 1;
                    }
                    else if( st[j + i] == '0' ) {
                        graph[tempIndex[j]][0] += 1;
                        graph[0][tempIndex[j]] += 1;
                    }
                    else if( st[j + i] == '1' ) {
                        graph[tempIndex[j]][questionNum + 1] += 1;
                        graph[questionNum + 1][tempIndex[j]] += 1;
                    }
                }
            }
        }
        // Строим граф.
        /*int k = index.size();
        for( int i = 0; i < k; ++i ) {
            if( index[i].first == 1 ) {
                // Индекс текущего вопроса в строке temp.
                int curIndex = index[i].second;
                for( int j = 0; j < stSize - tempSize + 1; ++j ) {
                    if( st[curIndex + j] == '?' ) {
                        graph[i][stIndex[curIndex + j]] = 1;
                        graph[stIndex[curIndex + j]][i] = 1;
                    }
                    else if( st[curIndex + j] == '0' ) {
                        graph[0][i] += 1; // >>
                        graph[i][0] += 1;
                    }
                    else if( st[curIndex + j] == '1' ) {
                        graph[questionNum + 1][i] += 1;
                        graph[i][questionNum + 1] += 1;
                    }
                }
            }
        }*/
        answerSize = 0;

        CRaiseBegin solver( questionNum + 2, 0, questionNum + 1, graph );
        answerSize = solver.raiseToBegin();
        answerSize += conflicts;
        visited.assign( questionNum + 2, false );
        vector<vector<int>>& flow = solver.getFlow();
        //bfs( flow, questionNum + 2, visited );
        dfs( 0, flow );

        for( int i = 1; i < questionNum + 1; ++i ) {
            if( visited[i] == true ) {
                if( index[i].first == false ) {
                    st[index[i].second] = '0';
                }
                else if( index[i].first == true ) {
                    temp[index[i].second] = '0';
                }
            }
            else {
                if( index[i].first == false ) {
                    st[index[i].second] = '1';
                }
                else if( index[i].first == true ) {
                    temp[index[i].second] = '1';
                }
            }
        }
    }

    void bfs( vector<vector<int>> flow, int num, vector<bool>& used ) 
    {
        queue<int> q;
        q.push( 0 );
        used[0] = true;
        while( !q.empty() ) {
            int v = q.front();
            q.pop();
            for( int i = 0; i < graph[v].size(); ++i ) {
                int to = i;
                if( !used[to] && graph[v][to] != flow[v][to] ) {
                    used[to] = true;
                    q.push( to );
                }
            }
        }
    }

    void dfs( int v, vector<vector<int>>& flow ) {
        visited[v] = true;
        int k = graph[v].size();
        for( int i = 0; i < k; ++i )
            if( !visited[i] && graph[v][i] != flow[v][i] )
                dfs( i, flow );
    }

    int getAnswerSize()const {
        return answerSize;
    }

private:
    // Номера вопросиков в графе, пара из номера строки в индекс в этой строке.
    // По номеру получаем индекс в строке.
    vector<pair<bool, int> > index;

    // Вектор длины строк, если на этом месте стоит ?, то в нем записан его номер в графе.
    // По индексу получаем номер.
    vector<int> stIndex;
    vector<int> tempIndex;
    int answerSize;
    string& st;
    string& temp;
    vector<vector<int> > graph;
    vector<bool> visited;
};


using namespace std;

int main() {
    string st;
    string temp;
    cin >> st;
    cin >> temp;

    CHamming sol( st, temp );
    sol.solveHamming();
    int answer = sol.getAnswerSize();
    cout << answer << endl;
    cout << st << endl;
    cout << temp << endl;
    cin >> answer;
    // коммент
    return 0;
}