#include "Arbitration.h"
#include <algorithm>

// Решаем задачу поиска отрицательных циклов в графе, используя алгоритм Беллмана-Форда.
bool CArbitration::DoArbitration( const COrGraph& graph, std::size_t startVertex )
{
    // Ищем кратчайший путь от каждой вершины(зануляем все), т.к. это не влияет на отрицательные циклы.
    for( vector<double>::iterator i = d.begin(); i != d.end(); ++i ) {
        *i = 0;
    }
    // true, если была проведена релаксация, false иначе.
    bool relaxed = false;
    // Количество вершин в графе.
    int graphVerticesCount = graph.GetVerticesCount();
    // В простом алгоритме Беллмана-Форда, надо было бы сделать на 1 итерацию меньше, но мы ищем отриц. цикл на последней.
    for( int i = 1; i <= graphVerticesCount; ++i ) {
        relaxed = false;
        for( int u = 0; u < graphVerticesCount; ++u ) {
            for( int v = 0; v < graph.GetOutEdgesFromVertex( u ).size( ); ++v ) {
                if( graph.GetOutEdgesFromVertex( u )[v] != -1 && d[v] > d[u] + graph.GetOutEdgesFromVertex( u )[v] ) {
                    d[v] = d[u] + graph.GetOutEdgesFromVertex( u )[v]; // Делаем релаксацию вершины.
                    relaxed = true;
                }
            }
        }
        // Если на последнем шаге была совершена релаксация, значит отрицательный цикл есть.
        if( i == graphVerticesCount && relaxed == true ) {
            return true;
        }
    }
    return false; // Отрицательных циклов нет.
}
