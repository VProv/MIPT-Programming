#pragma once
#include <vector>
#include <set>
#include <functional>
#include "WGraph.h"
// Класс алгоритма Прима поиска минимального остовного дерева в графе.
// Провилков Иван. гр.593.

class CCompare;

using std::vector;
using std::set;

class CPrima {
public:
    friend CCompare;
    CWGraph Graph;
    CPrima(CWGraph _Graph,int _VerticesCount ) : 
        key( _VerticesCount, infinity ), parentMin( _VerticesCount, -1 ), Graph( _Graph ), VerticesCount( _VerticesCount ) {
        answer = 0;
    };
    // Нахождение минимального остовного дерева.
    void findMST();
    // Оператор сравнения вершин в очереди.
    int getAnswer()const { return answer; }
private:
    const int VerticesCount;
    // Массив значений ключей(расстояний) вершин.
    vector<int> key;
    // Вершины на которых достигается min при определении ключа.
    vector<int> parentMin;
    // Длина мин остовного дерева, ответ.
    int answer;
    const static unsigned int infinity = 1000000000;
};

static CPrima* a;

class CCompare {
public:
    bool operator () (int i, int j) {
        if( a->parentMin[i] == -1 || a->parentMin[ j ] == -1 ) {
            return i < j;
        }
        return a->Graph.getEdgeLength( i, a->parentMin[i] ) < a->Graph.getEdgeLength( j, a->parentMin[j] );
    }
};
