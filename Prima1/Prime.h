#pragma once
// Класс поиска минимального остовного дерева на графе без кратных ребер с помощью алгоритма Прима.
// Провилков Иван гр.593.
#include <set>
#include <vector>
#include <algorithm>
#include <set>

using std::set;
using std::vector;
using std::pair;

// Класс решения.
class CPrime {
public:
    // Инициализируем массив расстояний бесконечностью, массив предков -1.
    CPrime( vector < vector < pair<int, int> > > _graph, int _verticesCount ) :
        minWeight( _verticesCount, infinity ), minEnding( verticesCount, -1 ), graph( _graph ), verticesCount( _verticesCount ) {};
    // Функция, производящая поиск минимального остовного дерева.
    void solveMST();
    int getAnswer()const { return answer; }
private:
    // Количество вершин.
    const int verticesCount;
    // Граф, без повторения ребер. Пары (второй конец ребра, вес ребра).
    vector < vector < pair<int, int> > > graph;
    // Ответ, длина минимальнго остовного дерева.
    int answer;
    // Вектор, содержащий минимальные расстояния от каждой вершины до части графа, уже входящей в MST.
    vector<int> minWeight;
    // Вектор, содержащий номера вершин, на которых достигается minWeight.
    vector<int> minEnding;
    const static int infinity = 1000000000;
};