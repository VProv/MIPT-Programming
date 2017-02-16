#pragma once
// Класс суффиксного массива.
// Провилков Иван. гр. 593.
#include <algorithm>
#include <vector>
#include <string>

using std::vector;
using std::string;
// Класс суффиксного массива.
// Построение за O(nlogn), методом сортировки циклических сдвигов. Индексация суффиксов начинается с 0.
class CSuffArray {

public:
    CSuffArray( const string& _st ) : st( _st ) { createSuffArray(); };

    // Заполняет суффиксный массив.
    // Построение за O(nlogn) описание можно увидеть в реализации.
    void createSuffArray();

    // Построение LCP. Алгоритм Касаи (Алгоритм нахождения общих префиксов 
    // всех соседних суффиксов, отсортированных в лексикографическом порядке).
    vector<int> buildLCP( const string& str, const vector<int>& suffArr );

    const string& getSt()const { return st; }
    const vector<int>& getSuffArray()const { return SuffArray; }
private:
    // Сортировка левых циклических сдвигов в строке.
    void sortingCycleShifts( vector<int>& answer );
    const string& st;
    vector<int> SuffArray;
};