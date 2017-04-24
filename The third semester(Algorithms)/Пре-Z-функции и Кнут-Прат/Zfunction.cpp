#include "PreFunction.h"
#include "Zfunction.h"

void CZfunction::createZst() {
    CPrefunction temp( *this );
    temp.createPreSt();
    Zst = temp.getPreSt();
}

void CZfunction::UpDateZF() {
    // ���� �������� �������� Z ������� �� 0 �� i-1, �� ���� i > right(��� right � left ������� ��������� ������������
    // � i � ������ Z[i]). ���� ������ ���������� �� ������,Z[i] = ������� j:S[i +j] = S[j].
    // ���� i<=right ���������� (Z[i - left] + i � right) : right <, ������ �����������, ����� Z[i - left]
    ZArray.assign( st->size(), 0 );
    int left = 0;
    int right = 0;
    int n = st->size();
    for( int i = 1; i < n; ++i ) {
        ZArray[i] = std::max( 0, std::min( right - i, ZArray[i - left] ) );
        while( i + ZArray[i] < n && ( *st )[ZArray[i]] == ( *st )[i + ZArray[i]] )
            ZArray[i]++;
        if( i + ZArray[i] >= right ) {
            left = i;
            right = i + ZArray[i];
        }
    }
}