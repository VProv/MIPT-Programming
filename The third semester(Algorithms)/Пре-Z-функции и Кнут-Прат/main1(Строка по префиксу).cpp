#include <iostream>
#include <vector>
#include "PreFunction.h"
// Восстановление строки по префикс функции.
using namespace std;

int main() {
   
    vector<int> problem;
    int a = 0;
    while( cin >> a ) {
        problem.push_back( a );
    }
    
    string tempst;
    CPrefunction solveClass( problem);
    solveClass.createPreSt();
    const string& PreSt = solveClass.getPreSt();
    
    cout << PreSt;

    return 0;
}
