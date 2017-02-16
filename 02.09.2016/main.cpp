#include <vector>
#include <set>
#include <algorithm>
#include <fstream>

using std::vector;
using std::pair;
using std::set;
using std::make_pair;
// ����� ���������.
class CPrim {
public:
    CPrim( vector < vector < pair<int, int> > > _graph, int _vCount ) :
        minWeight( _vCount, infinity ), minEnding( _vCount, -1 ),
        graph( _graph ) {
        verticesCount = _vCount;
        answer = 0;
    }
    // ������� ��������� ����������� ����� MST.
    void solveMST();
    int getAnswer()const {
        return answer;
    }
private:
    int verticesCount;
    // ����� ������������ ��������� ������.
    int answer;
    const static int infinity = 1000000000;
    // ���� (������ ����� �����, ��� �����)
    vector < vector < pair<int, int> > > graph;
    // ������ ���� ����������� ����� �� ������ �� �������� � ������� ������, �� ����.
    vector<int> minWeight;
    // ������ � ���������, �� ������� ���������� ����������� ��������.
    vector<int> minEnding;
    // ���� �� ���� � ����� �������, � ������� �����������.
    set < pair<int, int> > q;
};


void CPrim::solveMST() {
    minWeight[0] = 0;
    for( int i = 0; i < verticesCount; ++i ) {
        q.insert( std::make_pair( minWeight[i], i ) );
    }

    while( !q.empty() ) {
        int v = q.begin()->second;
        q.erase( q.begin() );

        answer += minWeight[v];

        for( int j = 0; j < graph[v].size(); ++j ) {
            int to = graph[v][j].first;
            int cost = graph[v][j].second;

            if( q.find( std::make_pair( minWeight[to], to ) ) != q.end() && cost < minWeight[to] ) {
                q.erase( make_pair( minWeight[to], to ) );
                minWeight[to] = cost;
                minEnding[to] = v;
                q.insert( make_pair( minWeight[to], to ) );
            }
        }
    }
}

using namespace std;

int main() {
    fstream input( "kruskal.in", fstream::in );
    fstream output( "kruskal.out", fstream::out );
    int verticesCount = 0;
    input >> verticesCount;
    int edgesCount = 0;
    input >> edgesCount;
    vector < vector < pair<int, int> > > graph( verticesCount );
    const int infinity = 1000000000;

    for( int i = 0; i < edgesCount; ++i ) {
        int to = 0, from = 0, cost = 0;
        input >> from >> to >> cost;
        to -= 1;
        from -= 1;
        // ��������� ���� ��� ����� ����� ����� ��������� ��� ���� � �����.
        bool indik = false;
        for( int t = 0; t < graph[from].size(); ++t ) {
            if( graph[from][t].first == to ) {
                indik = true;
                if( cost < graph[from][t].second ) {
                    graph[from][t].second = cost;
                    for( int i = 0; i < graph[to].size(); ++i ) {
                        if( graph[to][i].first == from ) {
                            graph[to][i].second = cost;
                            break;
                        }
                    }
                    break;
                }
            }
        }
        if( indik == false ) {
            graph[from].push_back( std::make_pair( to, cost ) );
            graph[to].push_back( std::make_pair( from, cost ) );
        }
    }
    CPrim solveClass( graph, verticesCount );
    solveClass.solveMST();
    int answer = solveClass.getAnswer();
    output << answer;
    input.close();
    output.close();
    return 0;
}
