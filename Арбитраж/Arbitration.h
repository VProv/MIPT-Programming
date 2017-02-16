#pragma once
//Класс-Решение задачи арбитраж.(Поиск отрицательных циклов с помощью алгоритма Беллмана-Форда).
#include "OrGraph.h"//Граф для задачи, вершины-валюты, ребра-курсы обмена.

using std::vector;

//Задача арбитраж.
class CArbitration {
public:
    CArbitration( std::size_t vertixesCount = 1000 ) :
        d( vertixesCount ) {}

    // Функция возвращает true если арбитраж возможен, false иначе
    bool DoArbitration( const COrGraph& graph, std::size_t startVertex = 0 );
    
private:
    // Динамика
    vector<double> d;
};