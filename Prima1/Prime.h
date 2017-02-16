#pragma once
// ����� ������ ������������ ��������� ������ �� ����� ��� ������� ����� � ������� ��������� �����.
// ��������� ���� ��.593.
#include <set>
#include <vector>
#include <algorithm>
#include <set>

using std::set;
using std::vector;
using std::pair;

// ����� �������.
class CPrime {
public:
    // �������������� ������ ���������� ��������������, ������ ������� -1.
    CPrime( vector < vector < pair<int, int> > > _graph, int _verticesCount ) :
        minWeight( _verticesCount, infinity ), minEnding( verticesCount, -1 ), graph( _graph ), verticesCount( _verticesCount ) {};
    // �������, ������������ ����� ������������ ��������� ������.
    void solveMST();
    int getAnswer()const { return answer; }
private:
    // ���������� ������.
    const int verticesCount;
    // ����, ��� ���������� �����. ���� (������ ����� �����, ��� �����).
    vector < vector < pair<int, int> > > graph;
    // �����, ����� ����������� ��������� ������.
    int answer;
    // ������, ���������� ����������� ���������� �� ������ ������� �� ����� �����, ��� �������� � MST.
    vector<int> minWeight;
    // ������, ���������� ������ ������, �� ������� ����������� minWeight.
    vector<int> minEnding;
    const static int infinity = 1000000000;
};