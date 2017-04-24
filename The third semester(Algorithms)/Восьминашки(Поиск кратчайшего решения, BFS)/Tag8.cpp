#include <algorithm>
#include "Tag8.h"

using std::swap;
string CTag8::solveTag() 
{
    CBoard Current = nodes.front();
    passedTops.insert( Current.getBoardInt() );
    // ������� ���������.
    CBoard Target( 123456780 );
    // ������ ��� �������� ������������� �������.
    vector<int> tempForExisting = Current.getBoardOneVector();
    int inversionsSum = 0;
    // ����� �����.
    int boardLength = 3;
    // ������� ����� ������������, ������ ����� ����� �������� � ����� �����.
    for( int i = 0; i < boardLength * boardLength; ++i )
        if( tempForExisting[i] == 0 )
            tempForExisting[i] = 9;
    for( int i = 0; i < 9; ++i ) {
        for( int j = 0; j < i; ++j ) {
            if( tempForExisting[j] < tempForExisting[i] )
                ++inversionsSum;
        }
    }
    if( inversionsSum % 2 ) {
        string solution("0");
        return solution;
    }
    // �������� ����� �������.
    while( !nodes.empty() ) {
        Current = nodes.front();
        nodes.pop();
        if( Current == Target ) {
            // ���������� �����.
            return Current.getWay();
        }
        passedTops.insert( Current.getBoardInt() );
        // ������� ���� �� �����
        int x = 0, y = 0;
        //vector<int> tempState = Current.getBoardOneVector();
        x = Current.getNullPosition() / boardLength;
        y = Current.getNullPosition() - x * boardLength;
        if( x - 1 >= 0 ) {
            CBoard newItem = Current.generateUp();
            if( passedTops.find( newItem.getBoardInt() ) == passedTops.end() )
                nodes.push( newItem );
        }
        if( x + 1 <= (boardLength - 1) ) {
            CBoard newItem = Current.generateDown();
            if( passedTops.find( newItem.getBoardInt() ) == passedTops.end() )
                nodes.push( newItem );
        }
        if( (y + 1) <= (boardLength - 1) ) {
            CBoard newItem = Current.generateRight();
            if( passedTops.find( newItem.getBoardInt() ) == passedTops.end() )
                nodes.push( newItem );
        }
        if( y - 1 >= 0) {
            CBoard newItem = Current.generateLeft();
            if( passedTops.find( newItem.getBoardInt() ) == passedTops.end() )
                nodes.push( newItem );
        }                
    }
}