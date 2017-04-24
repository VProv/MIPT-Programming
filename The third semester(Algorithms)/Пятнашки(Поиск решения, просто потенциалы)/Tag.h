#pragma once
// ����� ������ ������� � ���� ��������, ��������� �������� A Star 
// ��������� ����. ��. 593.
#include <set>
#include <queue>
#include <map>
#include <unordered_map>
#include"Board.h"

using std::set;
using std::queue;
using std::priority_queue;
using std::shared_ptr;
using std::fstream;
using std::weak_ptr;
using std::map;
using std::unordered_map;
// ����� ��� ��������� ���������� �� ��������� ����� � ������� � �����������.
class Functor {
public:
    bool operator () ( shared_ptr<CBoard> a, shared_ptr<CBoard> b ) {
        return (*b) < (*a);
    }
};

// ����� ������� ��������.
class CTag {
public:
    CTag() : nodes(), result(), passedNodes() {};
    // ������� ����������� ������� � ��������� ��������� � output.
    void solveTag( shared_ptr<CBoard> startVertex, fstream& output );
    // ������� �������� ������������� ������� �� ������ ������.
    bool CheckPossibility( vector<char> numbers ) const;
private:
    // ������� � ����������� � ���������.
    priority_queue<shared_ptr<CBoard>,std::vector<shared_ptr<CBoard>>,Functor > nodes;
    // ��������� �� �������������� �������.
    weak_ptr<CBoard> result;
    // ���������� �������, �������������� �������, ���������� ���������� �� ���.
    unordered_map<unsigned long long, int> passedNodes;
};

