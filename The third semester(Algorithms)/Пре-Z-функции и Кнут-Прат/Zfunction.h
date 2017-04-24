#pragma once
// Класс Z функции.
// Провилков Иван. гр. 593.
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

// Класс Z-функции.
class CZfunction {

public:
    CZfunction( string* _st ) :st( _st ) {}
    CZfunction( const vector<int>& _ZArray ) : ZArray( _ZArray ) {};
    // Обновляет значение Z функции в зависимости от текущего значения st.
    void UpDateZF();
    // Строит строку минимального лексикографического порядка по Z функции. Через преобразование в префикс функцию.
    void createZst();
    const string& getZst()const { return Zst; }
    const vector<int>& getZF()const { return ZArray; }

private:
    // Указатель на исходную строку.
    string* st;
    // Массив с Z функцией.
    vector<int> ZArray;
    // Строка построенная по Z функции.
    string Zst;
};