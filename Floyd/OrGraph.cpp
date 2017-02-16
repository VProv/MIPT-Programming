#include <assert.h>
#include "OrGraph.h"

COrGraph::COrGraph( int verticesCount, const vector< vector<double> >& edges ) :
    vertices( verticesCount )
{
    for( int i = 0; i < verticesCount; ++i ) {
        vertices[i].OutEdges.resize( verticesCount );
        for( int j = 0; j < verticesCount; ++j ) {
            vertices[i].OutEdges[j] = edges[i][j];
        }
    }
}

vector<double>& COrGraph::operator [] ( int a ) {
    assert( !(a < 0 || a > vertices.size() + 1) );
    return vertices[a].OutEdges;
}

const vector<double>& COrGraph::GetOutEdgesFromVertex( int index ) const
{
    assert( !(index < 0 || index > vertices.size() + 1) );
    return vertices[index].OutEdges;
}
