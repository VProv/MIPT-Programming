#include "RaiseBegin.h"

void CRaiseBegin::relabel( int u )
{
    int height = 2 * n;
    for( list<int>::iterator it = neighbors[u].begin(); it != neighbors[u].end(); ++it )
        if( c[u][*it] > f[u][*it] ) // >>
            height = min( height, h[*it] );
    h[u] = height + 1;
}

void CRaiseBegin::push( int u, int v )
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

bool CRaiseBegin::discharge( int u )
{
    // Флаг конца.
    bool relabeled = false;
    // Пока избыточный поток еще есть.
    while( e[u] > 0 ) {
        if( current[u] == neighbors[u].end() ) { // Если мы на конце.
            relabel( u );
            relabeled = true;
            current[u] = neighbors[u].begin();
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

void CRaiseBegin::initializePreflow()
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

int CRaiseBegin::raiseToBegin()
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