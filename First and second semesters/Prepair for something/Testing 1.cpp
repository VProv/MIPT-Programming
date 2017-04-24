#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    string st;
    string st1 = " ";
    while (st1[st1.size() - 1] != '"') {
        cin >> st1;
        st += st1;
        st += ' ';
    }
    cout << setw(20)<<right<<setfill(' ') << setprecision(20) << st;
    int n;
    cin >> n;

    return 0;
}