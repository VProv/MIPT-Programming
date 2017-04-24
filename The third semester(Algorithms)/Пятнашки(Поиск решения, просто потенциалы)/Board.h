#pragma once
// ����� ��������� ����� � ���� � ��������. ������ ���������� A Star.
// ��������� ���� ��.593
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

// ����� ��������� �����.
class CBoard
{
public:
    CBoard(vector<char> state_, char _way = 0, int nullPosition_ = 0, int _distanceStart = 0 ) 
    {
        way = _way; state = state_; nullPosition = nullPosition_; distanceStart = _distanceStart;
    }
    // ������ ���������� �� �����.
    vector<shared_ptr<CBoard> > Children;
    // ��������� �� ��������.
    weak_ptr<CBoard> Parent;
    // ���������� ���� �� ��������.
    char GetWay() const { return way; }
    // �������� �������������� �� ��� �������.
    bool isEnd() const
    {
        if( state == End ) return true;
        return false;
    }
    // ������� �������� �����.
    void CreateChildren();
    // ������� ������� ���������.
    void setHeuristic( int _heur ) { heuristic = _heur; }
    // �������� ������ �����.
    static int GetBoardX() { return BoardX; }
    // �������� ����� �����.
    static int GetBoardY() { return BoardY; }
    // �������� ������� �����.
    static int GetBoardSquare() { return BoardSquare; }
    // �������� ��������� �� ������.
    int getDistanceStart()const { return distanceStart; }
    // �������� ������� ���������.
    int getHeuristic()const { return heuristic; }
    // �������� ��������� � �������. ����� ��������� �� ������ � ���������.
    int getPriority()const { return heuristic; }
    // �������� ��������� ��������� ����� ������������ �� ����������.
    bool operator < ( const CBoard& right )const { return getPriority() < right.getPriority(); }
    // �������� ��������� ����� ��� ������.
    vector<char> getStateVector()const { return state; }
    // �������� ��������� ����� ��� ����.
    unsigned long long getStateLong()const;
    // ������ ���������� �������������� ���������.
    const static vector<char> End;
    // ������� �������� �������.
    static unsigned long long pow( long long a, int _pow ) {
        if( _pow == 0 )
            return 1;
        return ( a * pow( a, _pow - 1 ) );
    }
private:
    // ��������� �� ��������� �������.
    int distanceStart;
    // ��������� �� �������� �������.
    int heuristic;
    // ����� �� �����.
    vector<char> state;
    // ���� �� ��������.
    char way;
    // ������� �������� ���������.
    int CountHeuristic();
    // ������� ����.
    int nullPosition;
    // ������ ����.
    const static int BoardX = 4;
    // ����� ����.
    const static int BoardY = 4;
    // ������� ����.
    const static int BoardSquare = 16;
    // ������ �������� 16.
    static unsigned long long pow16[16];
};
