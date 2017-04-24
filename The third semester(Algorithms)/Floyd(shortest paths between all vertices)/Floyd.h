#pragma once
// �������� ������-�������, ���������� ���������� ���������� ����� ����� ��������� ���������������� ����������� �����.
// ���� ��� ������������� ������.
#include <vector>
#include "OrGraph.h"

using std::vector;
// ����� �������.
class CFloyd {
public:
    CFloyd( const COrGraph& _Graph ) :
        Shortcuts( _Graph.GetVerticesCount(), vector<double>( _Graph.GetVerticesCount(), 0 ) ), OrGraph( _Graph ) {};
    // ��������� ��������.���������� ���������� �� ������ ������� �� ������.
    const vector<vector<double> >& performFloyd();

private:
    // ������ �� ����.
    const COrGraph& OrGraph;
    // ���������� ����.
    vector<vector<double> > Shortcuts;
};