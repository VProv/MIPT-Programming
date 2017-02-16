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
    // ������� �� ������� ������� � ���������� ���������� �����������.
    int flowValue = min( c[u][v] - f[u][v], e[u] );
    // ����� ������� �������, ���������� ���������� ����������� � ����� �� ��������� ����� ����������� �� �������� ������.
    // � ������� ������� � ����� �� ����� uv ������������� �� �� �� ��������.
    f[u][v] += flowValue;
    f[v][u] = -f[u][v];
    e[u] -= flowValue;
    e[v] += flowValue;
}

bool CRaiseBegin::discharge( int u )
{
    // ���� �����.
    bool relabeled = false;
    // ���� ���������� ����� ��� ����.
    while( e[u] > 0 ) {
        if( current[u] == neighbors[u].end() ) { // ���� �� �� �����.
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

int CRaiseBegin::raiseToBegin()
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