#pragma once
#include <iostream>
#include <vector>
using namespace std;

int vector_realization() {

    vector<bool> v(1000000, 0);
    int n;
    cin >> n;
    while (n != -1) {
        v[n] = 1;
        cin >> n;
    }
    cin >> n;
    bool flag = false;
    while (n != -1) {
        if (v[n] == 1) {
            cout << n << ' ';
            v[n] = 0;
            if (flag == false)
                flag = true;
        }
        cin >> n;
    }
    if (flag == false)
        cout << "empty";
    return 0;
}

