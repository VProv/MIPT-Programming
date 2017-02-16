#include<string>
#include<vector>
#include<algorithm>
#include<memory>

using std::vector;
using std::string;

class CPrefunction {

public:
    CPrefunction( const string& _st ) : st( _st ), PreArray( _st.size() ) {};
    CPrefunction( const vector<int> _PreArray, const string& _st ) : PreArray( _PreArray ), st( _st ) {};
    void UpDatePF()
    {
        PreArray[0] = 0;
        int n = st.size();
        for( int i = 1; i < n; ++i ) {
            // Для поиска бордера наибольшей длины.
            int step = PreArray[i - 1];
            while( step > 0 && st[i] != st[step] ) {
                step = PreArray[step - 1];
            }
            if( st[i] == st[step] )
                ++step;
            PreArray[i] = step;
        }
        return;
    }

    void createPreSt() {
        int t = 'a';
        int PreLen = PreArray.size();
        for( int i = 0; i < PreLen; ++i ) {
            if( PreArray[i] == 0 ) {
                PreSt += t;
                ++t;
            }
            else {
                PreSt += PreSt[PreArray[i] - 1];
            }
        }
    }

    const vector<int>& getPreArray()const { return PreArray; }
    const string& getPreSt()const { return PreSt; }
private:
    const string& st;
    vector<int> PreArray;
    string PreSt;
};

#include <iostream>

using namespace std;

int main() {

    vector<int> problem;
    int a = 0;
    while( cin >> a ) {
        problem.push_back( a );
    }

    string tempst;
    CPrefunction solveClass( problem, tempst );
    solveClass.createPreSt();
    const string& PreSt = solveClass.getPreSt();
    cout << PreSt;

    return 0;
}






/*
vector<bool> used( PreArray.size() );
PreSt.assign( PreLen, 0);
int c = 1;
PreSt[0] = 0;
for( int i = 1; i < PreLen; ++i ) {
if( PreArray[i] == 0 ) {
for( int k = 0; k < used.size(); ++k ) {
used[k] = false;
}
int k = PreArray[i - 1];
while( k > 0 ) {
used[PreSt[k]] = true;
k = PreArray[k - 1];
}
PreSt[i] = -1;
for( int j = 1; j <= c; ++j ) {
if( !used[j] ) {
PreSt[i] = j;
break;
}
}
if( PreSt[i] == -1 )
PreSt[i] = c++;
}
else {
PreSt[i] = PreSt[PreArray[i] - 1];
}
}
for( int i = 0; i < PreLen; ++i ) {
PreSt[i] = PreSt[i] + t;
}*/