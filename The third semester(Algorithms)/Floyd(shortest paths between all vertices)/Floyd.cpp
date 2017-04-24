#include <cassert>
#include <algorithm>
#include "Floyd.h"

using std::vector;

const vector<vector<double> >& CFloyd::performFloyd() {
    int n = Shortcuts.size();
    // Инициализация матрицы кратчайших путей.
    for( int i = 0; i < n; ++i )
        for( int j = 0; j < n; ++j ) {
            Shortcuts[i][j] = OrGraph.GetOutEdgesFromVertex( i )[j];
        }
    // Сам алгоритм.
    for( int i = 0; i < n; ++i )
        for( int j = 0; j < n; ++j )
            for( int k = 0; k < n; ++k ) {
                Shortcuts[j][k] = std::min( Shortcuts[j][k], Shortcuts[j][i] + Shortcuts[i][k] );
            }
    return Shortcuts;
}