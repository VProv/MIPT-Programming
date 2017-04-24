#pragma once
//  ласс обертки дл€ представлени€ расстановки на доске в восьминажках в виде int.
#include <vector>
#include <cassert>
#include <string>

using std::vector;
using std::string;
// ќбертка дл€ состо€ни€ доски в игре "восьминашки".
class CBoard {
public:
    CBoard( int _state = 0, string _way = "",int _null = 0) : way() { state = _state; way = _way; nullPosition = _null; }
    CBoard( const vector<vector<int> >& _state, string _way);
    CBoard( const vector<int>& _state, string way );
    // ¬озвращает расстановку на доске как вектор.
    vector<vector<int> > getBoardVector()const;
    int getBoardInt()const { return state; }
    vector<int> getBoardOneVector()const;
    bool operator == ( const CBoard& right ) { return state == right.state; }

    CBoard generateLeft()const;
    CBoard generateRight()const;
    CBoard generateDown()const;
    CBoard generateUp()const;
    int getNullPosition()const { return nullPosition; }
    string getWay()const { return way; }
    int getBoardLength()const { return boardLength; }
private:
    // —осто€ние доски, числа записаны с конца, 0 - пуста€ клетка.
    int state;
    //ƒлина стороны доски
    const static int boardLength = 3;
    string way;
    int nullPosition;
    static int powTen( int n )
    {
        static int pow10[10] = {
            1, 10, 100, 1000, 10000,
            100000, 1000000, 10000000, 100000000, 1000000000
        };

        return pow10[n];
    }
    int GetByIndex( int ind )const { return ( state % powTen( 9 - ind ) - state % powTen( 8 - ind ) ) / powTen( 8 - ind ); }
};

