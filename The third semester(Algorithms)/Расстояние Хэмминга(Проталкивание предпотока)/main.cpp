#include <iostream>
#include <string>
#include "Hamming.h"

using namespace std;

int main() {
    string st;
    string temp;
    cin >> st;
    cin >> temp;

    CHamming sol( st, temp );
    sol.solveHamming();
    int answer = sol.getAnswerSize();
    cout << answer << endl;
    cout << st << endl;
    cout << temp << endl;
    //cin >> answer;
    return 0;
}
