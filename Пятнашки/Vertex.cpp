#include "Vertåx.h"

using std::array;

std::array<std::array<int, 3>, 3 > CVertex::GetArrangement( )const {
    array<array<int, 3>, 3> tempArray;
    int tempArrangement = arrangement;
    for( int i = 0; i < 3; i++ )
        for( int j = 0; j < 3; j++ ) {
            tempArray[2 - i][2 - j] = tempArrangement % 10;
            tempArrangement /= 10;
        }
    return tempArray;
}

void CVertex::setDistance( int _distance ) {
    distance = _distance;
}
void CVertex::setParent( CVertex* _parent ) {
    parent = _parent;
}
void CVertex::setHeuristic( int _heuristic ) {
    heuristic = _heuristic;
}