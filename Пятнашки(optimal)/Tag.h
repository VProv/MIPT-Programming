#pragma once
// Класс Алгоритма поиска решения игры в пятнашки. Используем алгоритм IDA Star.
// Провилков Иван. гр. 593.
#include <set>
#include <queue>
#include <map>
#include <unordered_map>
#include <algorithm>
#include"Board.h"

using std::set;
using std::queue;
using std::priority_queue;
using std::fstream;
using std::map;
using std::unordered_map;
using std::pair;
// Класс решения игры пятнашки.
class CTag {
public:
    CTag() {};
    // Функция выполняющая решения и выводящая результат в output. IDA Star.
    void solveTag( CBoard& startVertex, fstream& output );
    // Функция проверки существования решения на данном наборе.
    bool CheckPossibility(const vector<char>& numbers ) const;
    // Функция рекурсивного поиска решения. 2й аргумент true, если мы поднимаемся в рекурсии из найденного решения.
    pair<int,bool> _search( CBoard& current, int gamut, int bound, std::vector<char>& answer );
private:
    const static int infinity = 10000000;
};

