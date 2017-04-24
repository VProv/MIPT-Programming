#include "PreZConverter.h"
#include "PreFunction.h"

// Этот конструктор строит префикс функцию для строк из алгоритма Кнута-Прата.
CPrefunction::CPrefunction( const string* _st, const string* p ) : st( _st ), PreArray( _st->size() + p->size() ) 
{
    PreArray[0] = 0;
    int n = st->size() + p->size();
    int step = 0;
    for( int i = 1; i < p->size(); ++i ) {
        // Для поиска бордера наибольшей длины.
        step = PreArray[i - 1];
        while( step > 0 && ( *p )[i] != ( *p )[step] ) {
            step = PreArray[step - 1];
        }
        if( ( *p )[i] == ( *p )[step] )
            ++step;
        PreArray[i] = step;
    }
    for( int i = p->size(); i < n; ++i ) {
        // Для поиска бордера наибольшей длины.
        step = PreArray[i - 1];
        while( step > 0 && ( *st )[i - p->size()] != ( *p )[step] ) {
            step = PreArray[step - 1];
        }
        if( ( *st )[i - p->size()] == ( *p )[step] )
            ++step;
        PreArray[i] = step;
    }
    return;
}

CPrefunction::CPrefunction( const CZfunction& z) 
{
    CPreZConverter conv;
    *this = conv.convertToPre( z );
}

void CPrefunction::UpDatePF()
{
    // Стараемся избавиться от явного сравнения символов строки и сравниваем элементы префиксного массива.
    // Если s[i + 1] = s[p[i] + 1], то просто добавляем p[i] + 1, если это не так то переходим к K такому, что
    // k = p[i] - 1.
    PreArray[0] = 0;
    int n = st->size();
    for( int i = 1; i < n; ++i ) {
        // Для поиска бордера наибольшей длины.
        int step = PreArray[i - 1];
        while( step > 0 && ( *st )[i] != ( *st )[step] ) {
            step = PreArray[step - 1];
        }
        if( ( *st )[i] == ( *st )[step] )
            ++step;
        PreArray[i] = step;
    }
    return;
}
void CPrefunction::createPreSt() 
{
    PreSt = 'a';
    int PreLen = PreArray.size();
    for( int i = 1; i < PreLen; ++i ) {
        for( char c = 'a'; c <= 'z'; ++c ) {
            // Предок, стоящий перед текущим символом. 
            int curParent = PreArray[i - 1];
            // Идем по предкам в нашей строке, чтобы в дальнейшем избежать наложений префиксов.
            while( curParent > 0 && c != PreSt[curParent] ) {
                curParent = PreArray[curParent - 1];
            }
            // Если символ удовлетворяет отсутствию наложений(если 0), или продолжает текущий префикс, мы его ставим.
            if ((c == PreSt[curParent] && PreArray[i] == curParent + 1 )
                || ( PreArray[i] == curParent &&  c != PreSt[curParent] )) {
                PreSt += c;
                break;
            }
        }
    }
}
