#include "DynArray.h"
#include<iostream>

using namespace std;
int main() {

    int * a = new int[5];
    a[0] = 0;
    a[1] = 1;
    a[2] = 2;
    a[3] = 3;
    a[4] = 4;

    DynArray<int> b(a, 5);
    for (int i = 0; i < 5; i++)
        cout << b[i] << ' ';

    DynArray<int> c(b);

    for (int i = 0; i < 5; i++)
        cout << c[i] << ' ';
    int n;
    cin >> n;
    return 0;
}
