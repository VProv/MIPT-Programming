#pragma once
// ����� ��������� ������ ������� ���� � "����������", ��������� ����� � ������ �� ����������.
// ��������� ����. ��. 593.
#include <queue>
#include <set>
#include"Board.h"

using std::queue;
using std::set;
class CTag8 {
public:
    CTag8(int _node) : 
        nodes(), passedTops()
    {
        CBoard tempBoard( _node );
        nodes.push( tempBoard );
    }
    string solveTag();
private:
    // ������� ����� � ����� ������.
    queue<CBoard> nodes;
    // �������� ���������� ������, ���������� ��� ������ ����.
    set<int> passedTops;
};