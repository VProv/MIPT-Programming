#pragma once
// Класс Алгоритма поиска решения игры в "Восьминашки", используя обход в ширину по состояниям.
// Провилков Иван. гр. 593.
#include <set>
#include"Board.h"

using std::set;
using std::queue;
using std::shared_ptr;
using std::fstream;
using std::weak_ptr;
using std::vector;

class CTag8 {
public:
    CTag8() : nodes(), result(), passedNodes() {};
    // Функция выполняющая решения и выводящая результат в output.
    void solveTag( shared_ptr<CBoard> startVertex, fstream& output );
    // Функция проверки существования решения на данном наборе.
    bool CheckPossibility(const vector<int>& numbers ) const;
private:
    // Очередь, в которой хранятся указатели на вершины, которые надо проверить.
    queue<shared_ptr<CBoard>> nodes;
    // Указатель на вершину от которой считается результат.
    weak_ptr<CBoard> result;
    // Множество уже пройденных вершин.
    set<int> passedNodes;
};