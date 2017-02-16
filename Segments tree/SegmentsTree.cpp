#include "SegmentsTree.h"

CSegmentsTree::CSegmentsTree( vector<int>& a ): arr(a) 
{
    int mul = 2;
    int n = a.size();
    while( mul < n ) {
        mul *= 2;
    }
    node t( infinity, infinity );
    tree.assign( mul * 2, t );
    a.resize( mul, infinity );
    // –екурсивное построение.
    treeBuild( 0, 0, mul );
}

// »щем 2ю пор€дковую статистику, как обычный RMQ, только хранитс€ 2 минимума в вершинах.
int CSegmentsTree::RMQUp( int l, int r )
{
    node answer( infinity, infinity );
    int n = tree.size() / 2;
    l += n - 1;
    r += n - 1;
    while( l <= r ) {
        // ≈сли l - правый сын своего родител€, учитываем его.
        if( l == 0 && r == 0 )
            return answer.min2;
        if( l % 2 == 0 )
            answer = myMin( answer, tree[l] );
        // ≈сли r - левый сын своего родител€, учитываем его.
        if( r % 2 == 1 ) {
            answer = myMin( answer, tree[r] );
        }
        // —двигаем указатели на уровень выше.
        l = l / 2;
        r = ( r - 2 ) / 2;
    }
    return answer.min2;
}

// —троим дерево сверху вниз, рекурсивно двига€сь от корн€ дерева.
void CSegmentsTree::treeBuild( int i, int l, int r )
{
    if( l == r )
        return;
    if( r - l == 1 )
        tree[i] = node( arr[l], infinity );
    else {
        int m = ( l + r ) / 2;
        treeBuild( 2 * i + 1, l, m );
        treeBuild( 2 * i + 2, m, r );
        tree[i] = myMin( tree[2 * i + 1], tree[2 * i + 2] );
    }
}

CSegmentsTree::node CSegmentsTree::myMin( const node& l, const node& r )const 
{
    int min1 = std::min( l.min1, r.min1 );
    int min2 = 0;
    if( l.min1 <= r.min1 ) {
        min2 = std::min( r.min1, l.min2 );
    }
    else {
        min2 = std::min( l.min1, r.min2 );
    }
    return node( min1, min2 );
}