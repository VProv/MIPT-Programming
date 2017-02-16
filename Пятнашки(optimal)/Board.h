#pragma once
// Класс состояния доски в игре в пятнашки.Все необходимое для алгоритма ID A Star.
// Провилков Иван гр.593
#include <vector>
#include <cmath>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>

using std::vector;
using std::queue;
using std::fstream;
using std::string;

// Класс состояния доски.
class CBoard
{
public:
    CBoard() :state() { way = 0; nullPosition = -1; distanceStart = 0; }
    CBoard(const vector<char>& state_, char _way = 0, int nullPosition_ = 0, int _distanceStart = 0 ) : state()
    {
        way = _way; state = state_; nullPosition = nullPosition_; distanceStart = _distanceStart;
    }
    // Возвращает путь от родителя.
    char GetWay() const { return way; }
    // Проверка результирующая ли эта вершина.
    bool isEnd() const
    {
        if( state == End ) return true;
        return false;
    }
    vector <CBoard> CreateChildrenVector();
    // Функция задания эвристики.
    void setHeuristic( int _heur ) { heuristic = _heur; }
    // Получить высоту доски.
    static int GetBoardX() { return BoardX; }
    // Получить длину доски.
    static int GetBoardY() { return BoardY; }
    // Получить площадь доски.
    static int GetBoardSquare() { return BoardSquare; }
    // Получить дистанцию от старта.
    int getDistanceStart()const { return distanceStart; }
    // Получить текущую эвристику.
    int getHeuristic()const { return heuristic; }
    // Получить приоритет в очереди. Сумма дистанции от начала и эвристики.
    int getPriority()const { return heuristic + distanceStart; }
    // Оператор сравнения положений доски относительно их приоритета.
    bool operator < ( const CBoard& right )const { return getPriority() < right.getPriority(); }
    // Получить состояние доски как вектор.
    vector<char> getStateVector()const { return state; }
    // Получить состояние доски как лонг.
    unsigned long long getStateLong()const;
    // Вектор содержащий результирующее состояние.
    const static vector<char> End;
    // Функция подсчета степени.
    static unsigned long long pow( long long a, int _pow ) {
        if( _pow == 0 )
            return 1;
        return ( a * pow( a, _pow - 1 ) );
    }
    // Функция подсчета эвристики.
    int CountHeuristic();
private:
    // Дистанция от стартовой вершины.
    int distanceStart;
    // Эвристика до конечной вершины.
    int heuristic;
    // Числа на доске.
    vector<char> state;
    // Путь от родителя.
    char way;
    // Позиция нуля.
    int nullPosition;
    // Высота поля.
    const static int BoardX = 4;
    // Длина поля.
    const static int BoardY = 4;
    // Площадь поля.
    const static int BoardSquare = 16;
    // Массив степеней 16.
    static unsigned long long pow16[16];
};