#pragma once
#include <set>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

int set_realization(){
    set<int> s1;
    set<int> s2;
    int n;
    cin >> n;
    while (n != -1) {
        s1.insert(n);
        cin >> n;
    }
    cin >> n;
    while (n != -1) {
        s2.insert(n);
        cin >> n;
    }
    set<int> result;
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(result, result.begin()));

    if (result.empty())
        cout << "empty" << endl;
    else
    {
        copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    return 0;
}

int vala(int i) {
    int k;
    k = 0;
    return 0;
}
