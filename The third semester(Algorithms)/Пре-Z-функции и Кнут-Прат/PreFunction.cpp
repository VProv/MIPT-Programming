#include "PreZConverter.h"
#include "PreFunction.h"

// ���� ����������� ������ ������� ������� ��� ����� �� ��������� �����-�����.
CPrefunction::CPrefunction( const string* _st, const string* p ) : st( _st ), PreArray( _st->size() + p->size() ) 
{
    PreArray[0] = 0;
    int n = st->size() + p->size();
    int step = 0;
    for( int i = 1; i < p->size(); ++i ) {
        // ��� ������ ������� ���������� �����.
        step = PreArray[i - 1];
        while( step > 0 && ( *p )[i] != ( *p )[step] ) {
            step = PreArray[step - 1];
        }
        if( ( *p )[i] == ( *p )[step] )
            ++step;
        PreArray[i] = step;
    }
    for( int i = p->size(); i < n; ++i ) {
        // ��� ������ ������� ���������� �����.
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
    // ��������� ���������� �� ������ ��������� �������� ������ � ���������� �������� ����������� �������.
    // ���� s[i + 1] = s[p[i] + 1], �� ������ ��������� p[i] + 1, ���� ��� �� ��� �� ��������� � K ������, ���
    // k = p[i] - 1.
    PreArray[0] = 0;
    int n = st->size();
    for( int i = 1; i < n; ++i ) {
        // ��� ������ ������� ���������� �����.
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
            // ������, ������� ����� ������� ��������. 
            int curParent = PreArray[i - 1];
            // ���� �� ������� � ����� ������, ����� � ���������� �������� ��������� ���������.
            while( curParent > 0 && c != PreSt[curParent] ) {
                curParent = PreArray[curParent - 1];
            }
            // ���� ������ ������������� ���������� ���������(���� 0), ��� ���������� ������� �������, �� ��� ������.
            if ((c == PreSt[curParent] && PreArray[i] == curParent + 1 )
                || ( PreArray[i] == curParent &&  c != PreSt[curParent] )) {
                PreSt += c;
                break;
            }
        }
    }
}
