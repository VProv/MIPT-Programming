// Нахождение всех различных подстрок в заданной строке.
#include <iostream>
#include <string>
#include "SuffArray.h"

using namespace std;

int main() {
    int n = 0;
    string st;
    cin >> st;
    int nsum = 0;
    CSuffArray solver( st );
    const vector<int> answer = solver.getSuffArray();
    for( int i = 0; i < answer.size(); ++i ) {
        nsum += st.size() - answer[i];
    }
    int LCPsum = 0;
    vector<int> LCP = solver.buildLCP( solver.getSt(), solver.getSuffArray() );
    for( int i = 0; i < LCP.size() - 1; ++i ) {
        LCPsum += LCP[i];
    }
    cout << nsum - LCPsum;
    cin >> n;

    return 0;
}
