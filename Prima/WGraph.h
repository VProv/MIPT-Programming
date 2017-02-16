#pragma once
#include <algorithm>
#include <vector>
#include <unordered_set>

using std::pair;
using std::unordered_multiset;
using std::vector;

class CVertex {
public:
    int to;
    int cost;
    CVertex( int _to, int _cost ) :to( _to ), cost( _cost ) {};
};

class CWGraph {
public:
    CWGraph() :WGraph(100) {};
    CWGraph(int n) : WGraph(n) {};
    void addEdge( int _from, int _to, int _cost ) {
        WGraph[_from].push_back( CVertex( _to, _cost ));
        WGraph[_to].push_back( CVertex( _from, _cost ) );
        return;
    }
    CWGraph( vector<vector<CVertex> > _WGraph ) : WGraph( _WGraph ) {};
    const int getEdgeLength( int i, int j ) {
        return WGraph[i][j].cost;
    }
    const vector < vector < CVertex > >& getWGraph() {
        return WGraph;
    }
    vector<CVertex>& getEdges( int i ) {
        return WGraph[i];
    }
private:
    // Наш граф.
    vector < vector < CVertex > > WGraph;
};


