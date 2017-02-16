#include "SuffArray.h"

/*
    ��������� ������� log(S) ��������, � ������ �� ������� ��������� ����������� ������ ����� 1,2,4,8...
    ������ �������� ��������� ������ �� ������� �������� ���������, ����� ������ �������� �������� �� ���� ������,
    ��������������� �� ������ I �������� ����������� �������, � ����� ������ ������� ��������������� ����� ���:
    �� ������������ �� ����������� ������������ ������� ����������� �������, � ���������� �� ������ I ��������
    ����������� ������ � ����� ������ ���������������, ����� � ������. ����� ������� |S|.
    �� ������ �������� ����������� ����������� �������, ��� � ��� ���� �������� ���������� �������� � ������.
    �������, ��� ������ ����� ��������� ����� 2l - ������������ 2� ��� ����������� ����� l.
    ������, ����� ��������� S[i..(i+2l-1)%|S|] ����� ���� ������������ � ���� ���� �����
    classes[i],classes[(i+l)%|S|] � ���������� ������������� ������ ��� ����.
    ���������� ������� BucketSort. ��������� ���������� ��������� ������� �� 2�� ����� ����� �� 1��
    (���������� �� ������� ���� ��������� �� ���������� �������).
*/
void CSuffArray::sortingCycleShifts( vector<int>& answer ) {
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

/* �������, ��� ��������� i � j ��������� ������, ����������� ��������� i � j ����� ����������� ������� ������ S$.
   �������� ���������� ����������� ������� ��������� ��� ��������������� �������.
*/
void CSuffArray::createSuffArray() {
    const_cast< string& > ( st ) += '$';
    sortingCycleShifts( SuffArray );
    SuffArray.erase( SuffArray.begin() );
    const_cast< string& > ( st ).pop_back();
};

vector<int> CSuffArray::buildLCP( const string& str, const vector<int>& suffArr ) {
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