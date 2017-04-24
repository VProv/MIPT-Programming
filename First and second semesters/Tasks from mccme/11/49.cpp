#include<iostream>
#include<vector>
#include <string>

using namespace std;

int main() {
    vector<string> v9;
    vector<string> v10;
    vector<string> v11;
    int n = 0;
    char p[51];
    while (cin >> n >> p) {
        if (n == 9)
            v9.push_back(p);
        else if (n == 10)
            v10.push_back(p);
        else if (n == 11)
            v11.push_back(p);
        else if (n == 0)
            break;
    }
    for (vector<string>::iterator i = v9.begin(); i != v9.end(); i++)
        cout << 9 << ' ' << *(i) << endl;
    for (vector<string>::iterator i = v10.begin(); i != v10.end(); i++)
        cout << 10 << ' '<< *(i) << endl;
    for (vector<string>::iterator i = v11.begin(); i != v11.end(); i++)
        cout << 11 << ' '<< *(i) << endl;

    return 0;
}