#pragma once
// Приближенное решение задачи коммивояжера с помощью MST.
// Провилков Иван. гр.593.
#include <vector>
#include <algorithm>

using std::vector;
using std::pair;

class CHamiltonianCycleApproximationMST {
public:
    CHamiltonianCycleApproximationMST(int _verticesCount, const vector<vector<double> >& _graph, const vector<vector<int> >& _MST ) :
        graph( _graph ), MST( _MST ), visited(_verticesCount, false),answerCycle() {
        verticesCount = _verticesCount;
    }
    void dfs( int u ) 
    {
        // Помечаем вершину как пройденную.
        visited[u] = true;
        answerCycle.push_back( u );
        // Проходим по смежным с u вершинам.
        for( int i = 0; i < MST[u].size(); ++i ) {   
            // Проверяем, не находились ли мы ранее в выбранной вершине
            if( !visited[MST[u][i]] )                    
                dfs( MST[u][i] );
        }
    }

    vector<int> findAnswerCycle() 
    {
        dfs( 0 );
        answerCycle.push_back( 0 );
        answerCycleLen = 0;
        for( int i = 0; i < answerCycle.size() - 1; ++i )
            answerCycleLen += graph[answerCycle[i]][answerCycle[i + 1]];
        return answerCycle;
    }
    double getAnswerCycleLen()const { return answerCycleLen; }

private:
    int verticesCount;
    const vector<vector<double> >& graph;
    const vector<vector<int> >& MST;
    vector<int> answerCycle;
    vector<bool> visited;
    double answerCycleLen;
};