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
            // ��� ������ ������� ���������� �����.
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
    // ������� ������ �� ������� �������.
    void createPreSt() {
        PreSt = 'a';
        int PreLen = PreArray.size();
        for( int i = 1; i < PreLen; ++i ) {
            for( char c = 'a'; c <= 'z'; ++c ) {
                // ������, ������� ����� ������� ��������. 
                int curParent = PreArray[i - 1];
                // ���� �� ������� � ����� ������, ����� � ���������� �������� ��������� ���������.
                while( curParent > 0 && c != PreSt[curParent] ) {
                    curParent = PreArray[curParent - 1];
                }
                // ���� ������ ������������� ���������� ���������(���� 0), ��� ���������� ������� �������, �� ��� ������.
                if( ( c == PreSt[curParent] && PreArray[i] == curParent + 1 )
                    || ( PreArray[i] == curParent &&  c != PreSt[curParent] ) ) {
                    PreSt += c;
                    break;
                }
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
#include <vector>
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