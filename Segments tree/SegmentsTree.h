#pragma once
// Класс решающий задачу нахождения 2й порядковой статистики на отрезке, с помощью дерева отрезков.
// Провилков Иван. гр.593.
#include <vector>
#include <cmath>
#include <algorithm>
using std::vector;

// Класс дерева отрезков.
class CSegmentsTree {
public:
    // Вершинами нашего дерева будут структуры с двумя минимумами на отрезке.
    // min1 <= min2.
    struct node {
        int min1;
        int min2;
        node( int _min1, int _min2 ) :min1(_min1),min2(_min2) {};
    };
    // Конструктор, строит дерево отрезков по заданному массиву a.
    CSegmentsTree( vector<int>& a );
    // Вычисляет 2ю порядковую статистику на отрезке от l до r.
    int RMQUp( int l, int r );
    
private:
    // Функция рекурсивного построения дерева отрезков.
    void treeBuild( int i, int l, int r );
    // Возвращает node с минимумами min1 и min2, из 2х node.
    node myMin( const node& l, const node& r )const;
    // Ссылка на входной массив с которым мы работаем.
    vector<int>& arr;
    // Вектор, содержащий наше дерево.
    vector<node> tree;
    const static int infinity = 100000000;
};