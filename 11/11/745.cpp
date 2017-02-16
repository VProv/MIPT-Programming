#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    set<string> s;
    char f = ' ';
    string st;
    while (true) {
        cin >> f;
        if (f == '+') {
            cin >> st;
            s.insert(st);
        }
        else if (f == '-') {
            cin >> st;
            s.erase(st);
        }
        else if (f == '?') {
            cin >> st;
            if (s.find(st) != s.cend())
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
        else if (f == '#')
            break;
    }

    return 0;
}