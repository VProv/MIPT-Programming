#include <iostream>
#include <string>
#include "Tag8.h"

using namespace std;

int main() 
{
    int n = 0;
    for( int i = 0; i < 9; ++i ) {
        int k;
        cin >> k;
        n = n * 10 + k;
    }
    CTag8 Tag( n );
    string result = Tag.solveTag();
    if( result == "0" )
        cout << -1;
    else {
        cout << result.size() << endl;
        cout << result;
    }
    cin >> n;

    return 0;
}