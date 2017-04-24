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
    // ����������� ����������.
    treeBuild( 0, 0, mul );
}

// ���� 2� ���������� ����������, ��� ������� RMQ, ������ �������� 2 �������� � ��������.
int CSegmentsTree::RMQUp( int l, int r )
{
    node answer( infinity, infinity );
    int n = tree.size() / 2;
    l += n - 1;
    r += n - 1;
    while( l <= r ) {
        // ���� l - ������ ��� ������ ��������, ��������� ���.
        if( l == 0 && r == 0 )
            return answer.min2;
        if( l % 2 == 0 )
            answer = myMin( answer, tree[l] );
        // ���� r - ����� ��� ������ ��������, ��������� ���.
        if( r % 2 == 1 ) {
            answer = myMin( answer, tree[r] );
        }
        // �������� ��������� �� ������� ����.
        l = l / 2;
        r = ( r - 2 ) / 2;
    }
    return answer.min2;
}

// ������ ������ ������ ����, ���������� �������� �� ����� ������.
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