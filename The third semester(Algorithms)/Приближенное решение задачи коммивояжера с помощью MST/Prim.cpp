#include "Prim.h"

void CPrim::solveMST() 
{
    // Уже использованные вершины.
    vector<bool> used( verticesCount );
    // Минимальный вес ребра на этой вершине и на какой вершине достигается этот минимум.
    vector<double> minWeight( verticesCount, infinity ), minEnding( verticesCount, -1 );
    
    minWeight[0] = 0;
    for( int i = 0; i < verticesCount; ++i ) {
        int v = -1;
        for( int j = 0; j < verticesCount; ++j )
            if( !used[j] && ( v == -1 || minWeight[j] < minWeight[v] ) )
                v = j;
        used[v] = true;

        if( minEnding[v] != -1 ) {
            MSTlen += graph[v][minEnding[v]];
            MST[v].push_back( minEnding[v] );
            MST[minEnding[v]].push_back( v );
        }

        for( int to = 0; to < verticesCount; ++to ) {
            if( graph[v][to] < minWeight[to] ) {
                minWeight[to] = graph[v][to];
                minEnding[to] = v;
            }
        }
    }
}