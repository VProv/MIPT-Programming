#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <set>
#include "Tag.h"
#include "Board.h"
using namespace std;

int main()
{

    fstream input( "puzzle.in", fstream::in );
    fstream output( "puzzle.out", fstream::out );
    int state = 0;
    int sum = 0;
    int nullPosition = -1;
    int current = 0;
    // ¬ектор дл€ записи начального положени€.
    vector<char> numbers(16,0);

    for( int i = 0; i < 16; ++i )
    {
        input >> current;
        numbers[i] = current;
        if( current == 0 ) nullPosition = i;
    }

    bool result = true;
    for( int i = 0; i < 16; ++i )
        if( numbers[i] != CBoard::End[i] )
            result = false;
    if( result == true ) {
        output << 0;
        return 0;
    }
    CTag SolvingClass;
    if( SolvingClass.CheckPossibility( numbers ) ) {
        shared_ptr<CBoard> startVertex( new CBoard(numbers,'\0',nullPosition) );
        SolvingClass.solveTag( startVertex, output );
    }
    else output << -1;

    input.close();
    output.close();
    return 0;
}