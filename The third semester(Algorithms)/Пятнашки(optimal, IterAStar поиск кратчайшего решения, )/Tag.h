#pragma once
// ����� ��������� ������ ������� ���� � ��������. ���������� �������� IDA Star.
// ��������� ����. ��. 593.
#include <set>
#include <queue>
#include <map>
#include <unordered_map>
#include <algorithm>
#include"Board.h"

using std::set;
using std::queue;
using std::priority_queue;
using std::fstream;
using std::map;
using std::unordered_map;
using std::pair;
// ����� ������� ���� ��������.
class CTag {
public:
    CTag() {};
    // ������� ����������� ������� � ��������� ��������� � output. IDA Star.
    void solveTag( CBoard& startVertex, fstream& output );
    // ������� �������� ������������� ������� �� ������ ������.
    bool CheckPossibility(const vector<char>& numbers ) const;
    // ������� ������������ ������ �������. 2� �������� true, ���� �� ����������� � �������� �� ���������� �������.
    pair<int,bool> _search( CBoard& current, int gamut, int bound, std::vector<char>& answer );
private:
    const static int infinity = 10000000;
};

