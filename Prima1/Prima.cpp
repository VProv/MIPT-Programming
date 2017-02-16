#include"Prime.h"

void CPrime::solveMST() {
    // �������� ��������� �������.
    minWeight[0] = 0;
    // ������� ������. ���� �� ���� ������������ ����� � ������� �� �������� ��� �������.
    set < pair<int, int> > q;
    // ��������� ��� �������.
    for( int i = 0; i < verticesCount; ++i ) {
        q.insert( std::make_pair( minWeight[i], i ) );
    }
    // �������� �����.
    while( !q.empty() ) {
        int v = q.begin()->second;
        q.erase( q.begin() );

        answer += minWeight[v];

        for( int j = 0; j < graph[v].size(); ++j ) {
            int to = graph[v][j].first;
            int cost = graph[v][j].second;

            if( q.find( std::make_pair( minWeight[to], to ) ) != q.end() && cost < minWeight[to] ) {
                q.erase( std::make_pair( minWeight[to], to ) );
                minWeight[to] = cost;
                minEnding[to] = v;
                q.insert( std::make_pair( minWeight[to], to ) );
            }
        }
    }
    return;
}