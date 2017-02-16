#pragma once
// ����� ���������� ������������ ��������� ������ �� ����� ��� ������� �����, ��������� �������� �����.
// ��������� ���� ��.593.
#include <vector>
#include <set>
#include <algorithm>

using std::vector;
using std::pair;
using std::set;
using std::make_pair;
// ����� ���������.
class CPrim {
public:
    CPrim( const vector < vector < pair<int, int> > >& _graph, int _vCount ) :
        minWeight( _vCount, infinity ), minEnding( _vCount, -1 ),
        graph( _graph )
    {
        verticesCount = _vCount;  answer = 0;
    }
    // ������� ��������� ����������� ����� MST.
    void solveMST();
    int getAnswer()const { return answer; }

private:
    int verticesCount;
    // ����� ������������ ��������� ������.
    int answer;
    const static int infinity = 1000000000;
    // ���� (������ ����� �����, ��� �����), ��� ��� ����.
    const vector < vector < pair<int, int> > >& graph;
    // ������ ���� ����������� ����� �� ������ �� �������� � ������� ������, �� ����.
    vector<int> minWeight;
    // ������ � ���������, �� ������� ����������� ����������� ��������.
    vector<int> minEnding;
    // ���� �� ���� � ����� �������, � ������� �����������.
    set < pair<int, int> > q;
};