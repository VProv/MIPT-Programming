#pragma once
// Алгоритм Кнута-Прата.
// Провилков Иван. гр. 593.
#include<string>
#include"PreFunction.h"

// Класс алгоритма Кнута-Прата поиска вхождения заданной строки(шаблона) в указанную строку.
// Мы не создаем новой строки с #.
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
    // Шаблон.
    const string& templ;
    // Заданная строка.
    const string& st;
    // Строка содержащая шаблон + # + строка.
    string sumSt;
    // Вектор с номерами вхождений шаблона в строку.
    vector<int> answer;
};