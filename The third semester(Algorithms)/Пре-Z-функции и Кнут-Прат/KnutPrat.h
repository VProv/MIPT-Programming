#pragma once
// �������� �����-�����.
// ��������� ����. ��. 593.
#include<string>
#include"PreFunction.h"

// ����� ��������� �����-����� ������ ��������� �������� ������(�������) � ��������� ������.
// �� �� ������� ����� ������ � #.
class CKnutPrat {

public:
    CKnutPrat( const string& _templ, const string& _st ) : templ( _templ ), st( _st ) {};

    void solveKP() 
    {
        const_cast<string&>(templ) += '#';
        int templLen = templ.size() - 1;
        int stLen = st.size();
        CPrefunction preF( &st, &templ );
        const vector<int>& preArray = preF.getPreArray();
        for( int i = 0; i < stLen; ++i ) {
            if( preArray[templLen + i + 1] == templLen ) {
                answer.push_back( i - templLen + 1 );
            }
        }
    }
    const vector<int>& getAnswer()const { return answer; }
private:
    // ������.
    const string& templ;
    // �������� ������.
    const string& st;
    // ������ ���������� ������ + # + ������.
    string sumSt;
    // ������ � �������� ��������� ������� � ������.
    vector<int> answer;
};