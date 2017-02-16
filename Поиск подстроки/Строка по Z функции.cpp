/*#include <iostream>
#include <string>
#include "Zfunction.h"
// Восстановление строки по Z функции.
using namespace std;

int main() {

    vector<int> problem;
    int a = 0;
    while( cin >> a ) {
        problem.push_back( a );
    }
    
    CZfunction solver( problem );
    solver.createZst();
    string answer;
    answer = solver.getZst();
    cout << answer;

    return 0;
}*/