#include <vector>
#include <cmath>
#include <algorithm>
using std::vector;

class CSegmentsTree {
public:
    // ¬ершинами нашего дерева будут структуры с двум€ минимумами на отрезке.
    // min1 <= min2.
    struct node {
        int min1;
        int min2;
        node( int _min1, int _min2 ) :min1( _min1 ), min2( _min2 ) {};
    };
    CSegmentsTree( vector<int>& a ) : arr( a ) {
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

    int RMQUp( int l, int r )
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

private:
    void treeBuild( int i, int l, int r )
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

    node myMin( const node& l, const node& r )const {
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

    vector<int>& arr;
    // ¬ектор, содержащий наше дерево.
    vector<node> tree;
    const static int infinity;
};

const int CSegmentsTree::infinity = 100000000;

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 0;
    cin >> n;
    int m = 0;
    cin >> m;
    vector<int> ar;
    for( int i = 0; i < n; ++i ) {
        int k;
        cin >> k;
        ar.push_back( k );
    }
    CSegmentsTree ST( ar );
    int l = 0;
    int r = 0;
    for( int i = 0; i < m; ++i ) {
        cin >> l;
        cin >> r;
        cout << ST.RMQUp( l - 1, r - 1 ) << endl;
    }
    cin >> n;

    return 0;
}