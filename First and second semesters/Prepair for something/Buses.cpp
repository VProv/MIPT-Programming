#include <iostream>
#include <map>
#include <string>
using namespace std;

class bus {
    string name;
    int route;
public:
    bus() {}
    bus(string n, int r):name(n),route(r) {}
    string get_name()const {
        return name;
    }
    int get_route()const {
        return route;
    }
};

int main() {
    map<string,bus> m1,m2;

    int m;
    cin >> m;
    string st;
    string num, name;
    int rou;
    for (int i = 0; i < m; i++) {
        cin >> st;
        if (st == "add") {
            cin >> num;
            cin >> name;
            cin >> rou;
            bus a(name, rou);
            m2[num] = a;
        }
        else if (st == "departure") {
            cin >> num;
            bus a = m2[num];
            m2.erase(num);
            m1[num] = a;
        }
        else if (st == "arrival") {
            cin >> num;
            bus a = m1[num];
            m1.erase(num);
            m2[num] = a;
        }
        else if (st == "print") {
            cin >> st;
            if (st == "route") {
                for (map<string, bus>::iterator it = m1.begin(); it != m1.end(); ++it) {
                    cout << it->first << ' ' << it->second.get_name() << ' ' << it->second.get_route() << endl;
                }
            }
            else if (st == "park") {
                for (map<string, bus>::iterator it = m2.begin(); it != m2.end(); ++it) {
                    cout << it->first << ' ' << it->second.get_name() << ' ' << it->second.get_route() << endl;
                }
            }
        }
    }
    return 0;
}