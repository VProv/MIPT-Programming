#include <iostream>
#include <map>
#include <deque>
using namespace std;

int main() {
    int n;
    int k;
    cin >> n;
    cin >> k;
    deque<int> dq;
    map<int, int> m;
    unsigned int a = 0;
    for (int i = 0; i < k; i++) {
        cin >> a;
        dq.push_back(a);
        if (m.find(a) == m.end())
            m[a] = 0;
        m[a]++;
    }

    int min;
    unsigned int last;
    for (int i = 0; i < n - k; i++) {
        min = m.begin()->first;
        last = *dq.begin();
        dq.pop_front();
        m[last]--;
        if (m[last] == 0)
            m.erase(last);
        cin >> a;
        dq.push_back(a);
        if (m.find(a) == m.end())
            m[a] = 0;
        m[a]++;
        cout << min << endl;
    }
    cout << m.begin()->first << endl;
    return 0;
}