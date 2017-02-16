#pragma once
// Класс поиска решения в игре пятнашки, Используя алгоритм A Star 
// Провилков Иван. гр. 593.
#include <set>
#include <queue>
#include <map>
#include <unordered_map>
#include"Board.h"

using std::set;
using std::queue;
using std::priority_queue;
using std::shared_ptr;
using std::fstream;
using std::weak_ptr;
using std::map;
using std::unordered_map;
// Класс для сравнения указателей на состояние доски в очереди с приоритетом.
class Functor {
public:
    bool operator () ( shared_ptr<CBoard> a, shared_ptr<CBoard> b ) {
        return (*b) < (*a);
    }
};

// Класс решения пятнашек.
class CTag {
public:
    CTag() : nodes(), result(), passedNodes() {};
    // Функция выполняющая решения и выводящая результат в output.
    void solveTag( shared_ptr<CBoard> startVertex, fstream& output );
    // Функция проверки существования решения на данном наборе.
    bool CheckPossibility( vector<char> numbers ) const;
private:
    // Очередь с приоритетом с вершинами.
    priority_queue<shared_ptr<CBoard>,std::vector<shared_ptr<CBoard>>,Functor > nodes;
    // Указатель на результирующую вершину.
    weak_ptr<CBoard> result;
    // Пройденные вершины, закодированная вершина, кратчайшее расстояние до нее.
    unordered_map<unsigned long long, int> passedNodes;
};

