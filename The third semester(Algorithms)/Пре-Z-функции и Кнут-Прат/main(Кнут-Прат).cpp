/*#include <iostream>
#include <string>
#include "KnutPrat.h"

// Поиск вхождений шаблона в строку.
using namespace std;

int main() {
    string templ;
    string st;
    cin >> templ;
    cin >> st;
    CKnutPrat solvingClass( templ, st );
    solvingClass.solveKP();
    const vector<int>& answer = solvingClass.getAnswer();
    int t = answer.size();
    for( int i = 0; i < t; ++i ) {
        cout << answer[i] << ' ';
    }
    cin >> st;
    return 0;
}*/