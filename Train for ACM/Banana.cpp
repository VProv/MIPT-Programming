/*
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
    string round2;
    int rSize = round.size();
    for( int i = rSize - 1; i >= 0; --i ) {
        round2.push_back( round[i] );
    }
    //round2.reserve( round.size() + 1 );
    //copy(round.rbegin(),round.rend(),round2.begin() );
    s += s;
    int sSize = s.size();
    // Динамика.
    vector< vector <int> > dyn( sSize + 1, vector<int>( rSize + 1, 0 ) );
    vector< vector <int> > dyn2( sSize + 1, vector<int>( rSize + 1, 0 ) );
    for( int i = 0; i <= sSize; ++i )
        for( int j = 0; j <= rSize; ++j ) {
            if( i == 0 || j == 0 ) {
                dyn[i][j] = 0;
                dyn2[i][j] = 0;
            }
            else if( s[i - 1] == round[j - 1] ) {
                dyn[i][j] = dyn[i - 1][j - 1] + 1;
            }
            else {
                dyn[i][j] = max( dyn[i - 1][j], dyn[i][j - 1] );
            }

            if( i != 0 && j != 0 ) {
                if( s[i - 1] == round2[j - 1] ) {
                    dyn2[i][j] = dyn2[i - 1][j - 1] + 1;
                }
                else {
                    dyn2[i][j] = max( dyn2[i - 1][j], dyn2[i][j - 1] );
                }
            }
        }


    int maximum = max( dyn[sSize][rSize], dyn2[sSize][rSize] );
    if( maximum != rSize) {
        cout << -1 << endl;
    }
    else {
        if( dyn[sSize][rSize] == maximum ) {
            int posStart = 0;
            int posEnd = 0;
            for( int i = 0; i < sSize; ++i ) {
                if( s[i] == round[0] ) {
                    posStart = i;
                    break;
                }
            }
            for( int i = posStart; i < posStart + sSize / 2; ++i ) {
                if( s[i] == round[rSize - 1] ) {
                    posEnd = i;
                }
            }


            int posStart1 = 0;
            int posEnd1 = 0;
            for( int i = 0; i < sSize; ++i ) {
                if( s[i] == round[rSize - 1] ) {
                    posStart1 = i;
                    break;
                }
            }
            for( int i = posStart1; i < posStart1 + sSize / 2; ++i ) {
                if( s[i] == round[0] ) {
                    posEnd1 = i;
                }
            }
            cout << max(posEnd1 - posStart1 + 1, posEnd - posStart + 1) << endl;

        }
        else if( dyn[sSize][rSize] == maximum ) {
            int posStart = 0;
            int posEnd = 0;
            for( int i = 0; i < sSize; ++i ) {
                if( s[i] == round[0] ) {
                    posStart = i;
                    break;
                }
            }
            for( int i = posStart; i < posStart + sSize / 2; ++i ) {
                if( s[i] == round[rSize - 1] ) {
                    posEnd = i;
                }
            }
            cout << posEnd - posStart + 1 << endl;
        }
        else if( dyn2[sSize][rSize] == maximum ) {
            int posStart = 0;
            int posEnd = 0;
            for( int i = 0; i < sSize; ++i ) {
                if( s[i] == round[rSize - 1] ) {
                    posStart = i;
                    break;
                }
            }
            for( int i = posStart; i < posStart + sSize / 2; ++i ) {
                if( s[i] == round[0] ) {
                    posEnd = i;
                }
            }
            cout << posEnd - posStart + 1 << endl;
        }
    }

    return 0;
}*/