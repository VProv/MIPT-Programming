#pragma once
#include "Vert�x.h"
#include <set>
#include <queue>

using std::set;
using std::priority_queue;

//���� � ��������
class CTagGame {
public:
    CTagGame( );


private:
    set<CVertex,CVertexCompare()> passedVertices;
    priority_queue<CVertex,CVertexPriority()> verticesQueue;
};