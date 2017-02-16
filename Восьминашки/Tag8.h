#pragma once
// Класс Алгоритма поиска решения игры в "Восьминшки", используя обход в ширину по состояниям.
// Провилков Иван. гр. 593.
#include <queue>
#include <set>
#include"Board.h"

using std::queue;
using std::set;
class CTag8 {
public:
    CTag8(int _node) : 
        nodes(), passedTops()
    {
        CBoard tempBoard( _node );
        nodes.push( tempBoard );
    }
    string solveTag();
private:
    // Очередь узлов в нашем поиске.
    queue<CBoard> nodes;
    // Множство пройденных вершин, необходимо для поиска пути.
    set<int> passedTops;
};