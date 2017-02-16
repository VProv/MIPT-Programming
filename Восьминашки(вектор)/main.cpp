#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <set>
#include "Tag8.h"
#include "Board.h"
using namespace std;

int main()
{
    // Открываем файл для считывания и записи, связываем с ним поток.
    fstream input( "puzzle.in", fstream::in );
    fstream output( "puzzle.out", fstream::out );
    // Переменные для инициализации алгоритма.
    int state = 0;
    int sum = 0;
    int nullPosition = 0;
    int current = 0;
    // Вектор для записи начального положения.
    vector<int> numbers(9,0);

    for( int i = 0; i < 9; ++i )
    {
        input >> current;
        numbers[i] = current;
        if( current == 0 ) nullPosition = i;
        state = 10 * state + current;
    }

    if( state == 123456780 ) output << 0;
    CTag8 SolvingClass;
    if( SolvingClass.CheckPossibility( numbers ) ) {
        shared_ptr<CBoard> startVertex( new CBoard( '\0', state, nullPosition ) );
        SolvingClass.solveTag( startVertex, output );
    }
    else output << -1;

    input.close();
    output.close();
    return 0;
}