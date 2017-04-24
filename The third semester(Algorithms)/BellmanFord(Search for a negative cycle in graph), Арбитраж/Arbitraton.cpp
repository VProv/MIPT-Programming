#include "Arbitration.h"
#include <algorithm>

// ������ ������ ������ ������������� ������ � �����, ��������� �������� ��������-�����.
bool CArbitration::DoArbitration( const COrGraph& graph, std::size_t startVertex )
{
    // ���� ���������� ���� �� ������ �������(�������� ���), �.�. ��� �� ������ �� ������������� �����.
    for( vector<double>::iterator i = d.begin(); i != d.end(); ++i ) {
        *i = 0;
    }
    // true, ���� ���� ��������� ����������, false �����.
    bool relaxed = false;
    // ���������� ������ � �����.
    int graphVerticesCount = graph.GetVerticesCount();
    // � ������� ��������� ��������-�����, ���� ���� �� ������� �� 1 �������� ������, �� �� ���� �����. ���� �� ���������.
    for( int i = 1; i <= graphVerticesCount; ++i ) {
        relaxed = false;
        for( int u = 0; u < graphVerticesCount; ++u ) {
            for( int v = 0; v < graph.GetOutEdgesFromVertex( u ).size( ); ++v ) {
                if( graph.GetOutEdgesFromVertex( u )[v] != -1 && d[v] > d[u] + graph.GetOutEdgesFromVertex( u )[v] ) {
                    d[v] = d[u] + graph.GetOutEdgesFromVertex( u )[v]; // ������ ���������� �������.
                    relaxed = true;
                }
            }
        }
        // ���� �� ��������� ���� ���� ��������� ����������, ������ ������������� ���� ����.
        if( i == graphVerticesCount && relaxed == true ) {
            return true;
        }
    }
    return false; // ������������� ������ ���.
}
