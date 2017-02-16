#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int main() {
    deque<int> d;
    char st[14];
    while(true) {
        cin >> st;
        if ((strcmp(st, "pop_front") == 0 || strcmp(st, "pop_back") == 0 || strcmp(st, "front") == 0 || strcmp(st, "back") == 0) && d.size() == 0) {
            cout << "error" << endl;
            continue;
        }
        else if (strcmp(st, "push_front") == 0) {
            int a = 0;
            cin >> a;
            d.push_front(a);
            cout << "ok" << endl;
        }
        else if (strcmp(st, "push_back") == 0) {
            int a = 0;
            cin >> a;
            d.push_back(a);
            cout << "ok" << endl;
        }
        else if (strcmp(st, "pop_front") == 0) {
            cout << d.front() << endl;
            d.pop_front();
        }
        else if (strcmp(st, "pop_back") == 0) {
            cout << d.back() << endl;
            d.pop_back();
        }
        else if (strcmp(st, "front") == 0) {
            cout << d.front() << endl;
        }
        else if (strcmp(st, "back") == 0) {
            cout << d.back() << endl;
        }
        else if (strcmp(st, "size") == 0) {
            cout << d.size() << endl;
        }
        else if (strcmp(st, "clear") == 0) {
            cout << "ok" << endl;
            d.clear();
        }
        else if (strcmp(st, "exit") == 0) {
            cout << "bye" << endl;
            break;
        }
    }

    return 0;
}