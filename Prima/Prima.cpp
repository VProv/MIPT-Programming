#include "Prima.h"

void CPrima::findMST() {
    // ������������� �������� mkey � parentMin � ������������.
    /*auto comp = [&]( int i, int j ) {
        return Graph.getEdgeLength( i, parentMin[i] ) < Graph.getEdgeLength( j, parentMin[j] );
    };*/
    a = this;
    // ������������ ������� ������, ��� ���� ���. ��� ����� �� ����������� ������ � ���������� ����� �����.
    std::set<int,CCompare> VertexQueue;
    //decltype(comp)
    // ������������ ������� �����.
    int rand = 0;
    key[rand] = 0;
    for( int i = 0; i < VerticesCount; ++i )
        VertexQueue.insert( i );
    while( !VertexQueue.empty() ) {
        int v = *VertexQueue.begin();
        VertexQueue.erase(v);
        vector<CVertex>& tempEdges = Graph.getEdges( v );
        int curSize = tempEdges.size();
        for( auto it = tempEdges.begin(); it != tempEdges.end(); ++it ) {
            if( VertexQueue.find( it->to ) != VertexQueue.end() && key[it->to] > it->cost ) {
                parentMin[it->to] = v;
                key[it->to] = it->cost;
                VertexQueue.erase( it->to );
                VertexQueue.insert( it->to );
                answer += Graph.getEdgeLength( it->to, parentMin[it->to] );
            }
        }
    }
    return;
}
