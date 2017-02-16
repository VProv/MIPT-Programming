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
        for( vector<int>::iterator it = neighbors[u].begin(); it != neighbors[u].end(); ++it )
            if( c[u][*it] > f[u][*it] ) 
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
        // ���������� ��� �������� ������� �������� -1.
        stIndex.assign( stSize, -1 );
        tempIndex.assign( tempSize, -1 );
        index.push_back( std::make_pair( false, -1 ) );
        // ������� ���������� ����������.
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
        // ������ ����.
        /*int k = index.size();
        for( int i = 0; i < k; ++i ) {
            if( index[i].first == 1 ) {
                // ������ �������� ������� � ������ temp.
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
    // ������ ���������� � �����, ���� �� ������ ������ � ������ � ���� ������.
    // �� ������ �������� ������ � ������.
    vector<pair<bool, int> > index;

    // ������ ����� �����, ���� �� ���� ����� ����� ?, �� � ��� ������� ��� ����� � �����.
    // �� ������� �������� �����.
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
    // �������
    return 0;
}