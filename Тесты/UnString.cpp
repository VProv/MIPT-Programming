/*
// ����� ����������� �������.
// ��������� ����. ��. 593.
#include <algorithm>
#include <vector>
#include <string>

using std::vector;
using std::string;
// ����� ����������� �������.
// ���������� �� O(nlogn), ������� ���������� ����������� �������. ���������� ��������� ���������� � 0.
class CSuffArray {

public:
    CSuffArray( const string& _st ) : st( _st ) { createSuffArray(); };

    // ���������� ����������� �������.
    void sortingCycleShifts( vector<int>& answer ) {
        int size = st.size();
        answer.assign( size, 0 );
        vector<int> newPermutation( size ), classes( size ), newClasses( size ), h( size );
        int alphSize = 256;

        h.assign( alphSize, 0 );
        for( int i = 0; i < size; ++i ) {
            classes[i] = st[i];
            h[st[i]]++;
        }
        for( int i = 1; i < h.size(); ++i ) {
            h[i] += h[i - 1];
        }
        for( int i = size - 1; i >= 0; --i ) {
            newPermutation[--h[classes[i]]] = i;
        }

        answer.swap( newPermutation );

        for( int l = 1; l <= size; l += l ) {
            h.assign( alphSize, 0 );
            for( int j = 0; j < size; ++j ) {
                h[classes[j]]++;
            }
            for( int j = 1; j < alphSize; ++j ) {
                h[j] += h[j - 1];
            }
            for( int i = size - 1; i >= 0; --i ) {
                int v = ( answer[i] - l + size ) % size;
                newPermutation[--h[classes[v]]] = v;
            }
            answer.swap( newPermutation );
            alphSize = 1;
            newClasses[answer[0]] = 0;
            for( int i = 1; i < size; ++i ) {
                if( ( classes[answer[i]] == classes[answer[i - 1]] ) && ( classes[( answer[i] + l ) % size] == classes[( answer[i - 1] + l ) % size] ) ) {
                    newClasses[answer[i]] = alphSize - 1;
                }
                else {
                    newClasses[answer[i]] = alphSize++;
                }
            }
            classes.swap( newClasses );
        }
        return;
    };
    // ��������� ���������� ������.
    void createSuffArray() {
        const_cast< string& > ( st ) += '$';
        sortingCycleShifts( SuffArray );
        SuffArray.erase( SuffArray.begin() );
        const_cast< string& > ( st ).pop_back();
    };

    // ���������� LCP. �������� �����( �������� ���������� ����� ��������� 
    // ���� �������� ���������, ��������������� � ������������������ ������� ).
    vector<int> buildLCP( const string& str, const vector<int>& suffArr ) {
        int len = str.length();
        vector<int> lcp( len );
        // ������ �������� ������� ���������.
        vector<int> convSuff( len );
        for( int i = 0; i < len; ++i ) {
            convSuff[suffArr[i]] = i;
        }
        int k = 0;
        for( int i = 0; i < len; ++i ) {
            if( k > 0 ) {
                k--;
            }
            if( convSuff[i] == len - 1 ) {
                lcp[len - 1] = -1;
                k = 0;
            }
            else {
                int j = suffArr[convSuff[i] + 1];
                while( std::max( i + k, j + k ) < len && str[i + k] == str[j + k] ) {
                    k++;
                }
                lcp[convSuff[i]] = k;
            }
        }
        return lcp;
    }

    const string& getSt()const { return st; }
    const vector<int>& getSuffArray()const {
        return SuffArray;
    }
private:
    const string& st;
    vector<int> SuffArray;
};

#include <iostream>
#include <string>

using namespace std;

int main() {
    int n = 0;
    string st;
    cin >> st;
    int nsum = 0;
    CSuffArray solver( st );
    const vector<int> answer = solver.getSuffArray();
    for( int i = 0; i < answer.size(); ++i ) {
        //cout << answer[i] << ' ';
        nsum += st.size() - answer[i];
    }
    //cout << endl;
    int LCPsum = 0;
    vector<int> LCP = solver.buildLCP( solver.getSt(), solver.getSuffArray() );
    for( int i = 0; i < LCP.size() - 1; ++i ) {
        //cout << LCP[i] << ' ';
        LCPsum += LCP[i];
    }
    //cout << endl;
    cout << nsum - LCPsum;
    cin >> n;

    return 0;
}
*/

