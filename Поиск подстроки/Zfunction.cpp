#include "PreFunction.h"
#include "Zfunction.h"

void CZfunction::createZst() {
    CPrefunction temp( *this );
    temp.createPreSt();
    Zst = temp.getPreSt();
}

void CZfunction::UpDateZF() {
    // Если известны значения Z функции от 0 до i-1, то если i > right(где right и left границы подстроки начинающейся
    // в i и длиной Z[i]). Ищем наивно пробегаясь по строке,Z[i] = первому j:S[i +j] = S[j].
    // Если i<=right сравниваем (Z[i - left] + i и right) : right <, наивно пробегаемся, иначе Z[i - left]
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