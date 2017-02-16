#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

using std::cin;
int main() {
    // Входная строка.
    string s;
    std::cin >> s;
    // Кольцо.
    string round;
    std::cin >> round;
    round += round;
    s += s;
    int sSize = s.size();
    int rSize = round.size();
    int maxSize = rSize / 2;
    int CurMax = 0;
    // Динамика.
    vector< vector <int> > dyn( sSize + 1, vector<int>( rSize + 1, 0 ) );
    for( int i = 0; i <= sSize; ++i )
        for( int j = 0; j <= rSize; ++j ) {
            if( i == 0 || j == 0 ) {
                dyn[i][j] = 0;
            }
            else if( s[i - 1] == round[j - 1] ) {
                dyn[i][j] = dyn[i - 1][j - 1] + 1;
                if( dyn[i][j] > CurMax && dyn[i][j] < maxSize + 1 ) {
                    CurMax = dyn[i][j];
                }
            }
            else {
                dyn[i][j] = 0;
            }
        }

    int globalmax = 0;
    if( CurMax != rSize / 2 ) {
        CurMax = 0;
    }
    string substr1;
    string substr2;
    for( int i = 0; i < rSize / 2 - 1; ++i ) {
        substr1.assign( round.begin(), round.begin() + i + 1 );
        substr2.assign( round.begin() + i + 1, round.begin() + rSize / 2 );
        /*int start = s.find( substr1 );
        if( start != -1 ) {
            int k = s.find( substr2, start + 1 ) - start;
            if( k > 0 && k + 1 > CurMax )
                CurMax = k + 1;
        }*/
        // Обратный разворот.
        int start1 = s.find( substr2 );
        if( start1 != -1 ) {
            int k1 = s.find( substr1, start1 + 1 ) - start1;
            if( k1 > 0 && k1 + 1 > CurMax )
                CurMax = k1 + 1;
        }
    }
    if( CurMax == 0 )
        cout << -1 << endl;
    else 
        cout << CurMax << endl;
    int ne;
    cin >> ne;
    return 0;
}