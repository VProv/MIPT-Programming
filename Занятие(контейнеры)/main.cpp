#include <iostream>
#include <list>
#include <vector>
#include "Algorithm_String_List.h"

using namespace std;

int main() {
    vector<char> t;
    char p = ' ';
    cin.get(p);
    while (p != '\0' && p != '\n') {
        t.push_back(p);
        cin.get(p);
    }
    list<char> l = string_algorithm(t);
    for (list<char>::iterator i = l.begin(); i != l.end(); i++)
        cout << *(i);

    return 0;
}

/*
using namespace std;
int main() {
    int a[100002];
    int temp[100002];
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    mergesort(a, 0, n - 1, temp);

    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';

    int k;
    cin >> k;
    return 0;
}
*/