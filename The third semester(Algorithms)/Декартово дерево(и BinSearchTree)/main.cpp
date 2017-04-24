#include <iostream>
#include "Treap.h"
#include "BinarySearchTree.h"
using namespace std;

int main() {
    int aaa = 0;
    int bbb = 0;
    int n = 0;
    cin >> n;
    CBSTree bstree;
    if( n == 0 ) {
        cout << 0;
        return 0;
    }
    cin >> aaa;
    bstree.InsertCNode( aaa );
    cin >> bbb;
    CTreap treap( aaa, bbb );
    for( int i = 0; i < n - 1; ++i ) {
        cin >> aaa;
        cin >> bbb;
        bstree.InsertCNode( aaa );
        treap.insert( aaa, bbb );
    }
    //cout << bstree.height(bstree.GetRoot()) << endl;
    //cout << treap.height( treap.getRoot() ) << endl;
    cout << bstree.height( bstree.GetRoot() ) - treap.height( treap.getRoot() ) << endl;
    cin >> n;
    return 0;
}