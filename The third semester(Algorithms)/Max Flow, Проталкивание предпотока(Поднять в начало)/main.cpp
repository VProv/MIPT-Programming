#include <iostream>
#include <vector>
#include "RaiseBegin.h"

using namespace std;

int main()
{
    int i = 0, j = 0, edgeCount = 0;
    int n = -1, start = 0, destination = 0;
    cin >> n;
    while( n != 0 ) {
        cin >> start >> destination >> edgeCount;
        start--;
        destination--;
        vector< vector<int> > c( n, vector<int>( n, 0 ) );
        while( edgeCount-- ) {
            int val = 0;
            cin >> i >> j >> val;
            i--;
            j--;
            c[i][j] += val;
            c[j][i] += val;
        }

        // Находим максимальный поток.
        CRaiseBegin solveClass( n, start, destination, c );
        int result = solveClass.raiseToBegin();
        cout << result << endl;
        cin >> n;
    }
    return 0;
}