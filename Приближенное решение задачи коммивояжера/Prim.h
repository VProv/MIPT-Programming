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
    CPrim( int _verticesCount, const vector< vector<double> >& _graph ) : graph( _graph ), MST(_verticesCount) 
    {
        verticesCount = _verticesCount;
        MSTlen = 0;
    }
    void solveMST();
    vector<vector<int> > getMST()const 
    {
        return MST;
    }
    double getMSTlen()const { return MSTlen; }
private:
    int verticesCount;
    double MSTlen;
    const static int infinity = 1000000000;
    // ���� ������������� �������� ���������.
    const vector < vector<double> >& graph;
    vector <vector<int> > MST;
};