#pragma once
#include <cstring>
#include <list>
#include <vector>

using namespace std;

list<char> string_algorithm(const vector<char>& a) {
    char p = '0';
    int n = a.size();
    std::list<char> l;
    list<char>::iterator iter1 = l.begin();
    for (int i = 0; i < n; i++) {
        p = a[i];
        if (p == '^')
            iter1 = l.begin();
        else if (p == '$')
            iter1 = l.end();
        else if (p == '>') {
            if (iter1 != l.end())
                iter1++;
        }
        else if (p == '<') {
            if (iter1 != l.begin())
                iter1--;
        }
        else {
            l.insert(iter1, p);
        }
    }

    return l;
}