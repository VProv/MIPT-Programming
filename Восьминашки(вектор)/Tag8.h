#pragma once
// ����� ��������� ������ ������� ���� � "�����������", ��������� ����� � ������ �� ����������.
// ��������� ����. ��. 593.
#include <set>
#include"Board.h"

using std::set;
using std::queue;
using std::shared_ptr;
using std::fstream;
using std::weak_ptr;
using std::vector;

class CTag8 {
public:
    CTag8() : nodes(), result(), passedNodes() {};
    // ������� ����������� ������� � ��������� ��������� � output.
    void solveTag( shared_ptr<CBoard> startVertex, fstream& output );
    // ������� �������� ������������� ������� �� ������ ������.
    bool CheckPossibility(const vector<int>& numbers ) const;
private:
    // �������, � ������� �������� ��������� �� �������, ������� ���� ���������.
    queue<shared_ptr<CBoard>> nodes;
    // ��������� �� ������� �� ������� ��������� ���������.
    weak_ptr<CBoard> result;
    // ��������� ��� ���������� ������.
    set<int> passedNodes;
};