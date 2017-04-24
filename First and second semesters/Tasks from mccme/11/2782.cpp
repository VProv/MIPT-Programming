#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s;
    char f = ' ';
    int n;
    cin >> n;
    int num;
    bool flag = 0;
    int y = 0;

    for (int i = 0; i < n; i++) {
        cin >> f;
        if (f == '+') {
            if (flag == 0) {
                cin >> num;
                s.insert(num);
            }
            else if (flag == 1) {
                cin >> num;
                s.insert((num + y) % 1000000000);
                flag = 0;
            }
        }
        else if (f == '?') {
            cin >> num;
            if (s.find(num) != s.end()) {
                y = *s.find(num);
                cout << y << endl;
                flag = 1;
            }
            else if (s.equal_range(num).second != s.end()) {
                y = *(s.equal_range(num).second);
                cout << y << endl;
                flag = 1;
            }
            else {
                cout << -1 << endl;
                flag = 1;
                y = -1;
            }
        }
    }

    return 0;
}