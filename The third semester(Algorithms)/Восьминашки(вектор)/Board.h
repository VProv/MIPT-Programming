#pragma once
// ����� ������� ����� ��� ���� � �����������, � ���������� ���������� �� ����� � �� ���������.
#include <memory>
#include <vector>
#include <math.h>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>

using std::vector;
using std::queue;
using std::shared_ptr;
using std::weak_ptr;
using std::fstream;
using std::string;

// �����, �������� ��������� �����.
class CBoard {
public:
    CBoard( char _way, int state_, int nullPosition_ ) { way = _way; state = state_; nullPosition = nullPosition_; }

    // ������ ���������� �� �����.
    vector<shared_ptr<CBoard> > Children;
    // ��������� �� ��������.
    weak_ptr<CBoard> Parent;
    // ���������� ���� �� ��������.
    char GetWay() const { return way; }
    // ��������, �������� �� ��������� ��������.
    bool isEnd() const
    {
        if( state == 123456780 ) return true;
        return false;
    }
    // ������� �������� �����.
    void CreateChildren();
    int GetBoardSize()const { return BoardSize; }
    int getStateInt()const { return state; }

private:
    // ��������� �����.
    int state;
    // ���� �� ��������.
    char way;
    // ������� ���� �� �����.
    int nullPosition;
    // ������ ������� �����.
    const static int BoardSize = 3;
    // ������� �����.
    const static int BoardSquare = 9;
    // ������ �������� 10-��.
    const static vector<int> pow10;
    // ���������� ����� � int �� ��� �������.
    int ReturnByIndex( int _index ) { 
        return ( state % pow10[ BoardSquare - _index] - state % pow10[ BoardSquare - 1 - _index ] )
            / pow10[ BoardSquare - 1 - _index ]; 
    }
};