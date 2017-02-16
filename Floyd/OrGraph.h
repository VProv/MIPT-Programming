#pragma once
// ��������������� ����, ������ ��� ������ ������, ��������� �� �������� �����.
#include <vector>
using std::vector;
using std::pair;

// ��������������� ����.
class COrGraph {
public:
    // �����������, � ���������� ���������� ������ � ��������� ������ ���������, �������� �����.
    COrGraph( int verticesCount, const vector< vector<double> >& edges );

    // ���������� � �������.(������ ��������� �����, ��� ����� ���������).
    const vector<double>& GetOutEdgesFromVertex( int index ) const;
    //���������� ������ ��������� �����, � ������ ���������.
    vector<double>& operator [] ( const int a );
    // ���������� ������.
    int GetVerticesCount() const { return vertices.size( ); }
private:
    // �������.
    struct CVertex {
        vector<double> OutEdges; // ��������� �����.
    };
    
    // ��������� ������.
    vector<CVertex> vertices;
};