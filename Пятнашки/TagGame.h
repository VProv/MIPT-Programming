#pragma once
#include "Vertеx.h"
#include <set>
#include <queue>

using std::set;
using std::priority_queue;

//игра в пятнашки
class CTagGame {
public:
    CTagGame( );


private:
    set<CVertex,CVertexCompare()> passedVertices;
    priority_queue<CVertex,CVertexPriority()> verticesQueue;
};