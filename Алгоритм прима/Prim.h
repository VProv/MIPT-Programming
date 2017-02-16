#pragma once
// Класс нахождения минимального остовного дерева по графу без кратных ребер, используя алгоритм Прима.
// Провилков Иван гр.593.
#include <vector>
#include <set>
#include <algorithm>

using std::vector;
using std::pair;
using std::set;
using std::make_pair;
// Класс Алгоритма.
class CPrim {
public:
    CPrim( const vector < vector < pair<int, int> > >& _graph, int _vCount ) :
        minWeight( _vCount, infinity ), minEnding( _vCount, -1 ),
        graph( _graph )
    {
        verticesCount = _vCount;  answer = 0;
    }
    // Функция находящая минимальную длину MST.
    void solveMST();
    int getAnswer()const { return answer; }

private:
    int verticesCount;
    // Длина минимального остовного дерева.
    int answer;
    const static int infinity = 1000000000;
    // Пары (второй конец ребра, вес ребра), это наш граф.
    const vector < vector < pair<int, int> > >& graph;
    // Вектор длин минимальных ребер из вершин не входящих в текущее дерево, до него.
    vector<int> minWeight;
    // Вектор с вершинами, на которых достигаются минимальные значения.
    vector<int> minEnding;
    // Пары из веса в конец вершины, в порядке возрастания.
    set < pair<int, int> > q;
};