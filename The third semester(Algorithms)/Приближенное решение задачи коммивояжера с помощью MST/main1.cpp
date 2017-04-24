
/*#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    fstream input( "kruskal.in", fstream::in );
    fstream output( "kruskal.out", fstream::out );
    int verticesCount = 0;
    input >> verticesCount;
    int edgesCount = 0;
    input >> edgesCount;
    const int infinity = 1000000000;
    vector < vector<int> > graph(verticesCount,vector<int>(verticesCount,infinity));
    if( verticesCount == 0 || verticesCount == 1 ) {
        output << 0;
        return 0;
    }
    int answer = 0;
    for( int i = 0; i < edgesCount; ++i ) {
        int to = 0, from = 0, cost = 0;
        input >> from >> to >> cost;
        to -= 1;
        from -= 1;
        if( cost < graph[from][to] ) {
            graph[from][to] = cost;
            graph[to][from] = cost;
        }
    }
    // Индикатор вкючения вершины в остов.
    vector<bool> used( verticesCount );
    vector<int> minWeight( verticesCount, infinity ), minEnding( verticesCount, -1 );

    minWeight[0] = 0;
    for( int i = 0; i < verticesCount; ++i ) {
        int v = -1;
        for( int j = 0; j < verticesCount; ++j )
            if( !used[j] && ( v == -1 || minWeight[j] < minWeight[v] ) )
                v = j;
        used[v] = true;

        if( minEnding[v] != -1 ) {
            answer += graph[v][minEnding[v]];
        }

        for( int to = 0; to < verticesCount; ++to ) {
            if( graph[v][to] < minWeight[to] ) {
                minWeight[to] = graph[v][to];
                minEnding[to] = v;
            }
        }
    }
    output << answer;
    input.close();
    output.close();
    return 0;
}*/