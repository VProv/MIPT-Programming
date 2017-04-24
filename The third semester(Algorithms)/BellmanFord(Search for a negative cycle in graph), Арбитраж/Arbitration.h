#pragma once
//�����-������� ������ ��������.(����� ������������� ������ � ������� ��������� ��������-�����).
#include "OrGraph.h"//���� ��� ������, �������-������, �����-����� ������.

using std::vector;

//������ ��������.
class CArbitration {
public:
    CArbitration( std::size_t vertixesCount = 1000 ) :
        d( vertixesCount ) {}

    // ������� ���������� true ���� �������� ��������, false �����
    bool DoArbitration( const COrGraph& graph, std::size_t startVertex = 0 );
    
private:
    // ��������
    vector<double> d;
};