#include <algorithm>
#include <cmath>
#include "Board.h"
using std::abs;
using std::swap;
unsigned long long CBoard::pow16[16] = {
    pow( 16, 0 ), pow( 16, 1 ), pow( 16, 2 ), pow( 16, 3 ), pow( 16, 4 ),
    pow( 16, 5 ), pow( 16, 6 ), pow( 16, 7 ), pow( 16, 8 ), pow( 16, 9 ), pow( 16, 10 ),
    pow( 16, 11 ), pow( 16, 12 ), pow( 16, 13 ), pow( 16, 14 ), pow( 16, 15 )
};
const vector<char> CBoard::End = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 };

void CBoard::CreateChildren()
{
    vector<char> newState;
    int nullPositionX = nullPosition / BoardY;
    int nullPositionY = nullPosition - nullPositionX * BoardY; 
    if( nullPosition + BoardY <= BoardSquare - 1 && way != 'U' ) {
        newState = state;
        swap( newState[nullPosition], newState[nullPosition + BoardY] );
        Children.push_back( shared_ptr<CBoard>( new CBoard(newState,'D', nullPosition + BoardY,distanceStart + 1 ) ) );
    }
    if( nullPosition - BoardY >= 0 && way != 'D' ) {
        newState = state;
        swap( newState[nullPosition], newState[nullPosition - BoardY] );
        Children.push_back( shared_ptr<CBoard>( new CBoard(newState,'U', nullPosition - BoardY, distanceStart + 1 ) ) );
    }
    if( nullPositionY + 1 < BoardY && way != 'L' ) {
        newState = state;
        swap( newState[nullPosition], newState[nullPosition + 1] );
        Children.push_back( shared_ptr<CBoard>( new CBoard(newState,'R', nullPosition + 1, distanceStart + 1 ) ) );
    }
    if( nullPositionY - 1 >= 0 && way != 'R' ) {
        newState = state;
        swap( newState[nullPosition], newState[nullPosition - 1] );
        Children.push_back( shared_ptr<CBoard>( new CBoard( newState,'L', nullPosition - 1, distanceStart + 1 ) ) );
    }
    for( auto it = Children.begin(); it != Children.end(); ++it ) {
        ( *it )->CountHeuristic();
    }
}

// Суммарное манхэтенское расстояние.
int CBoard::CountHeuristic( ) {
    int sum = 0;
    for( int i = 0; i < BoardSquare; ++i ) {
        char k = state[i];
        if( k ) {
            int x = (state[i] - 1 )/ BoardX;
            sum = sum + abs( i / BoardX - x )
                + abs( ( i - ( i / BoardX ) * BoardX ) - ( (state[i] - 1 ) - x * BoardX ));
        }

    }
    heuristic = sum;
    return sum;
}

unsigned long long CBoard::getStateLong()const {
    unsigned long long sum = 0;
    for( int i = 0; i < BoardSquare; ++i ) {
        sum = sum + state[i] * pow16[ i ];
    }
    return sum;
}
