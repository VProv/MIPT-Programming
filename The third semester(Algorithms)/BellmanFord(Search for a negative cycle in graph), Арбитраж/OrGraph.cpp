#include <assert.h>
#include "OrGraph.h"

COrGraph::COrGraph( int verticesCount, const vector< vector <double> >& edges ) :
    vertices( verticesCount )
{
    for( int i = 0; i < verticesCount; ++i ) {
        vertices[i].OutEdges.resize( verticesCount );
        for( int j = 0; j < verticesCount; ++j ) {
            vertices[i].OutEdges[j] = edges[i][j];
        }
    }
}

const vector<double>& COrGraph::GetOutEdgesFromVertex( int index ) const
{
    return vertices[index].OutEdges;
}