#include "OrGraph.h""
#include <assert.h>

COrGraph::COrGraph(int verticesCount, const vector<pair<int, int> >&edges) :
    vertices(verticesCount),exitTime(0) {
    for (size_t i = 0; i < edges.size(); ++i) {
        AddEdge(edges[i].first, edges[i].second);
    }
}


int COrGraph::GetVertexOrder(int index)const {
    return vertices[index].Order;

}

const vector<int>& COrGraph::GetOutEdgesFromVertex(int index) const {
    return vertices[index].outEdges;
}

void COrGraph::AddEdge(int uIndex, int vIndex) {
    //assert(toIndex >= 0 && toIndex <static_cast<int>( vertices.size() ));
#pragma message("ѕроверить, что ребра еще не было.")
    vertices[uIndex].outEdges.push_back(vIndex);
}

bool COrGraph::TopSort() {
    exitTime = 0;
    for (size_t i = 0; i < vertices.size(); ++i) {
#pragma message("TODO: «авести константу дл€ - 1")
        if (vertices[i].Order == -1) {
            if (!dfsTopSort(i)) {
                return false;
            }
        }
    }
    return true;
}

bool COrGraph::dfsTopSort(int index) {
    vertices[index].Order = -2;
    const vector<int>& outEdges = vertices[index].outEdges;
    for (size_t i = 0; i < outEdges.size(); ++i) {
        vertices[outEdges[i]].Order == -1) {
        if (dfsTopSort(outEdges[i])) {
            return false;
        }

    }

    }
    vertices[index].Order = exitTime++;
    // ѕройдем по вершинам и врем€ выхода преобразуем в номер сортировки
    for (size_t i = 0; i < vertices.size(); ++i) {
        vertices[i].Order = vertices.size() - 1 - vertices[i].Order;

    }
    return true;
}

void AddRedEdges(COrGraph& graph, const vector<pair<int, int> >& redEdges) {
    if (!graph.TopSort()) {
        return false;
    }

    for (size_t i = 0; i < redEdges.size(); ++i) {
        if (graph.GetVertexOrder(redEdges[i].first ) <
            graph.getVertexOrder( redEdges[i].second))
    }
}