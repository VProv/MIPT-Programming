#include "Board.h"

const vector<int> CBoard::pow10 = {
    1, 10, 100, 1000, 10000,
    100000, 1000000, 10000000, 100000000, 1000000000
};

void CBoard::CreateChildren()
{
    // Создаем временную переменную где будет храниться состояние доски детей
    int newState = 0;
    int nullPositionX = nullPosition / BoardSize;
    int nullPositionY = nullPosition - nullPositionX * BoardSize;
    if( way != 'U' && nullPosition + BoardSize <= BoardSquare - 1 ) {
        newState = state + ( pow10[ BoardSquare - 1 - nullPosition ] 
            - pow10[ BoardSquare - 1 - nullPosition - BoardSize ] )* ReturnByIndex( nullPosition + BoardSize );
        Children.push_back( shared_ptr<CBoard>( new CBoard( 'D', newState, nullPosition + BoardSize ) ) );

    }
    if( way != 'D' && nullPosition - BoardSize >= 0 ) {
        newState = state + ( pow10[ BoardSquare - 1 - nullPosition ] 
            - pow10[ BoardSquare - 1 - nullPosition + BoardSize ] )* ReturnByIndex( nullPosition - BoardSize );
        Children.push_back( shared_ptr<CBoard>( new CBoard( 'U', newState, nullPosition - BoardSize ) ) );
    }
    if( way != 'L' && (nullPositionY + 1 < BoardSize)) {
        newState = state + ( pow10[ BoardSquare - 1 - nullPosition ]
            - pow10[ BoardSquare - 1 - nullPosition - 1 ] )* ReturnByIndex( nullPosition + 1 );
        Children.push_back( shared_ptr<CBoard>( new CBoard( 'R', newState, nullPosition + 1 ) ) );
    }
    if( way != 'R' && (nullPositionY - 1 >= 0) ) {
        newState = state + ( pow10[ BoardSquare - 1 - nullPosition ] 
            - pow10[ BoardSquare - 1 - nullPosition + 1 ] )* ReturnByIndex( nullPosition - 1 );
        Children.push_back( shared_ptr<CBoard>( new CBoard( 'L', newState, nullPosition - 1 ) ) );
    }
}