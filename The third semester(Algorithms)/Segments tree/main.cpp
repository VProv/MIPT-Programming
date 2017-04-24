// Ищем 2ю порядковую статистику на m отрезках, в массиве ar, которые задаются по очереди.
#include <iostream>
#include <vector>
#include "SegmentsTree.h"

using namespace std;

int main() {
    int n = 0;
    cin >> n;
    int m = 0;
    cin >> m;
    vector<int> ar;
    for( int i = 0; i < n; ++i ) {
        int k;
        cin >> k;
        ar.push_back( k );
    }
    CSegmentsTree ST( ar );
    int l = 0;
    int r = 0;
    for( int i = 0; i < m; ++i ) {
        cin >> l;
        cin >> r;
        cout << ST.RMQUp( l - 1, r - 1) << endl;
    }
    cin >> n;

    return 0;
}