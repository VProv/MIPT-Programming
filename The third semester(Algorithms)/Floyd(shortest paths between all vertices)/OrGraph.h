#pragma once
// Ориентированный граф, храним как вектор вершин, состоящих из векторов ребер.
#include <vector>
using std::vector;
using std::pair;

// Ориентированный граф.
class COrGraph {
public:
    // Конструктор, в аргументах количество вершин и двумерный вектор исходящих, входящих ребер.
    COrGraph( int verticesCount, const vector< vector<double> >& edges );

    // Информация о вершине.(Вектор исходящих ребер, без права изменения).
    const vector<double>& GetOutEdgesFromVertex( int index ) const;
    //Возвращает вектор исходящих ребер, с правом изменения.
    vector<double>& operator [] ( const int a );
    // Количество вершин.
    int GetVerticesCount() const { return vertices.size( ); }
private:
    // Вершина.
    struct CVertex {
        vector<double> OutEdges; // Исходящие ребра.
    };
    
    // Множество вершин.
    vector<CVertex> vertices;
};