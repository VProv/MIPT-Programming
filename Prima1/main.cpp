#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include "Prime.h"
using namespace std;

int main() {
    fstream input( "kruskal.in", fstream::in );
    fstream output( "kruskal.out", fstream::out );
    int verticesCount = 0;
    input >> verticesCount;
    int edgesCount = 0;
    input >> edgesCount;
    const int infinity = 1000000000;
    // ѕары (второй конец ребра, вес ребра)
    vector < vector < pair<int, int> > > graph( verticesCount );
    // —читывем ребра, если есть кратные, из них оставл€ем минимальное.
    for( int i = 0; i < edgesCount; ++i ) {
        int to = 0, from = 0, cost = 0;
        input >> from >> to >> cost;
        to -= 1;
        from -= 1;
        // »ндикатор того что ребро между этими вершинами уже было в графе.
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
    CPrime solveClass( graph, verticesCount );
    solveClass.solveMST();
    output << solveClass.getAnswer();
    input.close();
    output.close();
    return 0;
}