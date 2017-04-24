#include <algorithm>
#include "Board.h"

using std::vector;
using std::swap;
CBoard::CBoard( const vector<vector<int> >& _state,string _way) : way()
{
    way = _way;
    state = 0;
    int k = _state.size();
    for( int i = 0; i < k; ++i )
        for( int j = 0; j < k; ++j ) {
            state = state * 10 + _state[i][j];
            if( _state[i][j] == 0 )
                nullPosition = i * boardLength + j;
        }
}

vector<vector<int> > CBoard::getBoardVector()const 
{
    int tempState = state;
    vector<vector<int> > result( boardLength, vector<int>( boardLength ) );
    for( vector < vector<int> >::reverse_iterator it = result.rbegin(); it != result.rend(); ++it ) 
        for( vector <int>::reverse_iterator it1 = it->rbegin(); it1 != it->rend(); ++it1 ) {
            *it1 = tempState % 10;
            tempState /= 10;
        }            
    return result;
}

vector<int> CBoard::getBoardOneVector()const 
{
    int tempState = state;
    vector<int> result(boardLength * boardLength);
    for( int i = boardLength * boardLength - 1; i >=0 ; --i ) {
        result[i] = tempState % 10;
        tempState /= 10;
    }
    return result;
}

CBoard:: CBoard( const vector<int>& _state, string _way ) : 
    way()
{
    nullPosition = 0;
    state = 0;
    for( int i = 0; i < boardLength *boardLength; ++i ) {
        if( _state[i] == 0 )
            nullPosition = i;
        state = state * 10 + _state[i];
    }
    way = _way;
}

CBoard CBoard::generateDown() const
{
    int temp = this->state;
    int exchange = GetByIndex( nullPosition + 3 );
    temp = temp - ( temp % powTen( 9 - (nullPosition + 3) ) - state % powTen( 8 - (nullPosition + 3) ) ) +
        exchange * powTen( 8 - nullPosition );
    CBoard result( temp, way + 'D', nullPosition + 3 );
    return result;
}

CBoard CBoard::generateUp()const
{
    int temp = this->state;
    int exchange = GetByIndex( nullPosition - 3 );
    temp = temp - ( temp % powTen( 9 - (nullPosition - 3) ) - state % powTen( 8 - (nullPosition - 3) ) ) +
        exchange * powTen( 8 - nullPosition );
    CBoard result( temp, way + 'U', nullPosition - 3 );
    return result;
}

CBoard CBoard::generateLeft()const
{
    int temp = this->state;
    int exchange = GetByIndex( nullPosition - 1 );
    temp = temp - ( temp % powTen( 9 - (nullPosition - 1) ) - state % powTen( 8 - (nullPosition - 1) ) ) +
        exchange * powTen( 8 - nullPosition );
    CBoard result( temp, way + 'L', nullPosition - 1 );
    return result;
}

CBoard CBoard::generateRight()const
{
    int temp = this->state;
    int exchange = GetByIndex( nullPosition + 1 );
    temp = temp - ( temp % powTen( 9 - (nullPosition + 1) ) - state % powTen( 8 - (nullPosition + 1) ) ) +
        exchange * powTen( 8 - nullPosition );
    CBoard result( temp, way + 'R', nullPosition + 1 );
    return result;
}