#include <iostream>
#include "Prima.h"

using namespace std;

int main() {

    int VerticesCount = 0;
    int EdgesCount = 0;
    cin >> VerticesCount;
    cin >> EdgesCount;
    CWGraph graph( VerticesCount );
    for( int i = 0; i < EdgesCount; ++i ) {
        int to = 0, from = 0, cost = 0;
        cin >> from >> to >> cost;
        to -= 1;
        from -= 1;
        graph.addEdge( from, to, cost );  
    }
    CPrima prima( graph, VerticesCount );
    prima.findMST();
    cout << prima.getAnswer() << endl;
    int n;
    cin >> n;
    return 0;
}