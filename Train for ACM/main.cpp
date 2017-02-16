// ���������� ������������� ������ �� ����� ���������� "������� � � ������".
// ��������� ����. ��.593.
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

    // ������ �������.
    // ��� ������������� ������� u ��������� �������� �������, ���� ��� �������,
    // ��� ������� � ���������� ���� ���� ����� �� u, ����������� �� ���� u.
    // � ���������� ������� ������ ������� ������� ���������� �� ������� ������ ������ ����� ������ ������� ������� � ���������� ����, 
    // ���������� ���� ���������� ��� ������� ���� �����, �� �������� ����� ����������� �����.
    void relabel( int u )
    {
        int height = 2 * n;
        for( list<int>::iterator it = neighbors[u].begin(); it != neighbors[u].end(); ++it )
            if( c[u][*it] > f[u][*it] ) // >>
                height = min( height, h[*it] );
        h[u] = height + 1;
    }

    // �������� ����� ����������� ����� ������� �����������.
    void push( int u, int v )
    {
        // ������� �� ������� ������� � ���������� ���������� �����������.
        int flowValue = min( c[u][v] - f[u][v], e[u] );
        // ����� ������� �������, ���������� ���������� ����������� � ����� �� ��������� ����� ����������� �� �������� ������.
        // � ������� ������� � ����� �� ����� uv ������������� �� �� �� ��������.
        f[u][v] += flowValue;
        f[v][u] = -f[u][v];
        e[u] -= flowValue;
        e[v] += flowValue;
    }

    // ��������, ����������� � ������������� ������� u, ��� ���� ����� ����������� ����� ����� ���������� ����� � ������� �������,
    // ��� ������������� �������� u, ����� ������������ �����, ��������� �� ������� u, �����������.
    // �������� ���������� ������ �����, ����� ������� e(u) ������ ������ ����, � �� ������, �� ����������� ��������� current[u] �� ������ �� �������� e(u).
    bool discharge( int u )
    {
        // ���� �����.
        bool relabeled = false;
        // ���� ���������� ����� ��� ����.
        while( e[u] > 0 ) {
            if( current[u] == neighbors[u].end() ) { // ���� �� �� �����.
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

    // �������������� ���������.
    void initializePreflow()
    {
        // ��������� ����������� ��������� ����� �� ������, ����������� ������, 
        // �������� ���������� ����� ��� ������ ������� � ������� �������� �� ��������������� ��������.
        for( int u = 0; u < n; ++u )
            if( c[start][u] > 0 ) {
                f[start][u] = c[start][u];
                f[u][start] = -f[start][u];
                e[u] = c[start][u];
                e[start] -= c[start][u];
            }
        h[start] = n;
    }

    // ��� ��������, ���������� �������� ������������� ������.
    int raiseToBegin()
    {
        initializePreflow();
        // �������� ������ ������� ������� ��� ������ �������.
        for( int u = 0; u < n; ++u ) {
            for( int v = 0; v < n; ++v )
                if( c[u][v] > 0 || c[v][u] > 0 )
                    neighbors[u].push_back( v );
            if( u != start && u != destination ) {
                current[u] = neighbors[u].begin();
            }
        }
        // ��� ������� ����� ����� � ������.
        list<int> selectedVertices;
        for( int u = 0; u < n; ++u )
            if( u != start && u != destination )
                selectedVertices.push_back( u );

        list<int>::iterator curVert = selectedVertices.begin();
        while( curVert != selectedVertices.end() ) {
            /*int u = *curVert;
            if( discharge( u ) ) {
            // ����������� � ������ ������.
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
    // ���������� ������ �����.
    int n;
    // ����� ������ (� 0).
    int start;
    // ����� �����.
    int destination;
    // ���������.
    vector<vector<int> > f;
    // ��������� ���������� �����������, ��� ����.
    vector<vector<int> >& c;
    // ������ ������.
    vector<int> h;
    // ���������� ����� �������� � �������.
    vector<int> e;
    // ��� ������ ������� ������ ������ ������� ������, � ��� ������ ��� ���� ����� uv ��� vu.
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

        // ������� ������������ �����.
        CRaiseBegin solveClass( n, start, destination, c );
        int result = solveClass.raiseToBegin();
        cout << result << endl;
        cin >> n;
    }
    return 0;
}