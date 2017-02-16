//Ориентированный граф
#pragma once

#include <vector>
using std::pair;
using std::vector;

//Ориентированный граф
class COrGraph {
public:
    COrGraph(int verticesCount, const vector<pair<int, int> >& edges);

    int GetVertexOrder(int index) const;
    const vector<int>& GetOutEdgesFromVertex(int index)const;

    bool TopSort();
    void AddEdge(int uIndex, int vIndex);

private:
    //Вершина
    struct CVertex {
 
        vector<int> outEdges;
        int Order;

        CVertex() : Order(-1) {}
    };
    vector<CVertex> vertices;
    int exitTime;
    bool dfsTopSort(int index);
};

void AddRedEdges(COrGraph& graph, const vector<pair<int, int> >& redEdges);