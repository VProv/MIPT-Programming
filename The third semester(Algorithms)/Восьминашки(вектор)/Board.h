#pragma once
// Класс обертки доски для игры в восьминашки, с поддержкой указателей на детей и их созданием.
#include <memory>
#include <vector>
#include <math.h>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>

using std::vector;
using std::queue;
using std::shared_ptr;
using std::weak_ptr;
using std::fstream;
using std::string;

// Класс, хранящий состояние доски.
class CBoard {
public:
    CBoard( char _way, int state_, int nullPosition_ ) { way = _way; state = state_; nullPosition = nullPosition_; }

    // Вектор указателей на детей.
    vector<shared_ptr<CBoard> > Children;
    // Указатель на родителя.
    weak_ptr<CBoard> Parent;
    // Возвращает путь от родителя.
    char GetWay() const { return way; }
    // Проверка, является ли состояние конечным.
    bool isEnd() const
    {
        if( state == 123456780 ) return true;
        return false;
    }
    // Функция создания детей.
    void CreateChildren();
    int GetBoardSize()const { return BoardSize; }
    int getStateInt()const { return state; }

private:
    // Состояние доски.
    int state;
    // Путь от родителя.
    char way;
    // Позиция нуля на доске.
    int nullPosition;
    // Размер стороны доски.
    const static int BoardSize = 3;
    // Площадь доски.
    const static int BoardSquare = 9;
    // Массив степеней 10-ки.
    const static vector<int> pow10;
    // Возвращает число в int по его индексу.
    int ReturnByIndex( int _index ) { 
        return ( state % pow10[ BoardSquare - _index] - state % pow10[ BoardSquare - 1 - _index ] )
            / pow10[ BoardSquare - 1 - _index ]; 
    }
};