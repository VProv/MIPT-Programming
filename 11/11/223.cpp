#include <iostream>
#include <vector>

using namespace std;
int main() {
    int n = 0;
    vector<int> t(1001);
    cin >> n;
    int l = 0;
    for (int i = 0; i < n; i++) {
        cin >> l;
        t.push_back(l);
    }
    int simb = 0;
    cin >> simb;
    int counter = 0;
    for (vector<int>::iterator i = t.begin(); i != t.end(); i++) {
        if (*i == simb)
            counter++;
    }
    cout << counter;

    return 0;
}