#pragma once
// Класс конвертирующий Z функцию в префиксную и обратно.
#include "PreFunction.h"
#include "Zfunction.h"

// Класс конвертирующий префикс функцию в Z-функцию и обратно. Все за O(n).
class CPreZConverter {

public:
    CPrefunction convertToPre( const CZfunction& z ) 
    {
        const vector<int>& ZF = z.getZF();
        vector<int> PreF( ZF.size(), 0 );
        int size = ZF.size();
        for( int i = 1; i < size; ++i ) {
            for( int j = ZF[i] - 1; j >= 0; --j ) {
                if( PreF[i + j] > 0 )
                    break;
                else {
                    PreF[i + j] = j + 1;
                }
            }
        }
        CPrefunction temp( PreF );
        return temp;
    }

    CZfunction convertToZ( const CPrefunction& p ) 
    {
        const vector<int>& preArray = p.getPreArray();
        vector<int> ZArray(preArray.size());
        int size = preArray.size();
        // Далее разбираем 3 случая.
        for( int i = 1; i < size; ++i ) {
            if( preArray[i] > 0 ) {
                ZArray[i - preArray[i] + 1] = preArray[i];
            }
        }
        ZArray[0] = size;
        int i = 1;
        while( i < size ) {
            int t = i;
            if( ZArray[i] > 0 ) {
                for( int j = 1; j <= ZArray[i] - 1; ++j ) {
                    if( ZArray[i + j] > ZArray[j] )
                        break;
                    ZArray[i + j] = std::min( ZArray[j], ZArray[i] - j );
                    t = i + j;
                }
            }
            i = t + 1;
        }
    }
private:
};