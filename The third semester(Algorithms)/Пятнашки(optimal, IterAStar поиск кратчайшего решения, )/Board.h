#pragma once
// ����� ��������� ����� � ���� � ��������.��� ����������� ��� ��������� ID A Star.
// ��������� ���� ��.593
#include <vector>
#include <cmath>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>

using std::vector;
using std::queue;
using std::fstream;
using std::string;

// ����� ��������� �����.
class CBoard
{
public:
    CBoard() :state() { way = 0; nullPosition = -1; distanceStart = 0; }
    CBoard(const vector<char>& state_, char _way = 0, int nullPosition_ = 0, int _distanceStart = 0 ) : state()
    {
        way = _way; state = state_; nullPosition = nullPosition_; distanceStart = _distanceStart;
    }
    // ���������� ���� �� ��������.
    char GetWay() const { return way; }
    // �������� �������������� �� ��� �������.
    bool isEnd() const
    {
        if( state == End ) return true;
        return false;
    }
    vector <CBoard> CreateChildrenVector();
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
    int getPriority()const { return heuristic + distanceStart; }
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
    // ������� �������� ���������.
    int CountHeuristic();
private:
    // ��������� �� ��������� �������.
    int distanceStart;
    // ��������� �� �������� �������.
    int heuristic;
    // ����� �� �����.
    vector<char> state;
    // ���� �� ��������.
    char way;
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