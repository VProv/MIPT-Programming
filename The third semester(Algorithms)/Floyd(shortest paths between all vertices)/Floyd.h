#pragma once
// Алгоритм Флойда-Уоршела, нахождение кратчайших расстояний между всеми вершинами ориентированного взвешенного графа.
// Граф без отрицательных циклов.
#include <vector>
#include "OrGraph.h"

using std::vector;
// Класс решения.
class CFloyd {
public:
    CFloyd( const COrGraph& _Graph ) :
        Shortcuts( _Graph.GetVerticesCount(), vector<double>( _Graph.GetVerticesCount(), 0 ) ), OrGraph( _Graph ) {};
    // Исполняет алгоритм.Возвращает расстояние от каждой вершины до каждой.
    const vector<vector<double> >& performFloyd();

private:
    // Ссылка на граф.
    const COrGraph& OrGraph;
    // Кратчайшие пути.
    vector<vector<double> > Shortcuts;
};