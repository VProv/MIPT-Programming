#pragma once
// Класс решения задачи Хэмминга с помощью алгоритма Диница.
// Провилков Иван. гр.593.
#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::deque;
using std::pair;
using std::max;
using std::min;
using std::string;

// Считывает и хранит входные данные.
class CReader {

public:
    // Вход.
    void ReadTest()
    {
        std::cin >> str >> templ;
    }
    // Входная строка.
    string str;
    // Входной двигающийся шаблон.
    string templ;
};

// Ребро в графе. Поддерживает идущий через него поток.
struct CEdge {

    CEdge( int from, int to, int value, int flow = 0 ) :
        From( from ), To( to ), value( value ), Flow( flow ){}
    // Номер вершины откуда идет ребро.
    int From;
    // Номер вершины куда идет ребро.
    int To;
    int value;
    int Flow;
};

// Класс сети с поиском максимального потока.
// Используем алгоритм Диница.
class CNetwork {
public:
    // Конструктор сети по входным данным.
    CNetwork( const CReader& test );

    int GetMaxFlow();
    // Вывод в cout наших ссылок.
    void PrintRelations();
    // Добавление ребра
    void addEdge( int from, int to, int value, int reversevalue = 0 );
    // Логическая инверсия индекса.
    int inverseIndex( int index ) const;
    // Проверка существования пути до стока.
    int isPathToTarget() const;
    int getPushFlow( int vertex, int flow );
    const static int Infinity;
private:
    int source;
    int target;
    int numberOfVertices;
    // Прибавка к весу разреза.
    int conflicts;
    std::vector<CEdge> edges;
    std::vector<bool> visited;
    // Указатель на следующее ребро.
    std::vector<int> pointerToNextEdge;
    // В [i][j] хранится индекс ребра в массиве ребер, а это ребро j-e из i-й вершины, j-индекс ребра в массиве.
    // Соответствие локального номера ребра глобальному.
    std::vector<std::vector<int>> relationsToEdges;
    std::vector<int> distanceFromSource;
    // Метки первой части.
    std::vector<int> nullVertices;
    // Метки второй части.
    std::vector<int> singleVertices;

    // Подсчет расстояний от истока до всех вершин.
    void countDistancesFromSource();
    void getRelations();
    void transVector( std::vector<int>& vector );
    void printVector( const std::vector<int>& vector ) const;
    void markVertices( int vertex );
};


