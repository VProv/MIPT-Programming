#pragma once
// Класс префикс функции.
// Провилков Иван. гр.593.
#include<string>
#include<vector>
#include<algorithm>
#include<memory>

using std::vector;
using std::string;
class CZfunction;

// Класс префикс функции.
class CPrefunction {

public:
    // Инициализирует строку, по которой потом можно построить префикс функцию.
    CPrefunction( const string* _st ) : st( _st ), PreArray( ( *_st ).size() ) {};
    // Инициализирует префикс функцию по массиву.
    CPrefunction( const vector<int>& _PreArray ) : PreArray( _PreArray ) {};
    // Строит префикс функцию по Z функции.
    CPrefunction( const CZfunction& );
    // Конструктор для алгоритма Морриса Пратта. Принимает строку и шаблон.
    // К шаблону должен быть прибавлен символ меньший любого из алфавита.
    CPrefunction( const string* _st, const string* p );
    // Функция обновляющая значения префикс функции, исходя из строки st.
    void UpDatePF();
    // Создает строку по текущей префикс функции, в минимальном лексикографическом порядке.
    void createPreSt();

    const vector<int>& getPreArray()const { return PreArray; }
    const string& getPreSt()const { return PreSt; }
private:
    const string* st;
    vector<int> PreArray;
    // Строка строящаяся по префикс функции.
    string PreSt;
};