#pragma once
// Класс нахождения точного решения задачи Коммивояжера(мин. гамильтонова цикла), полным рекурсивным перебором.
#include <vector>
#include <algorithm>
using std::vector;

class CHamiltonianCycleExhaustiveSearch {
public:
    CHamiltonianCycleExhaustiveSearch( const vector<vector<double> >& _graph, int _verticesCount ) : 
        graph(_graph)
    {
        answerCycleLen = infinity;
        verticesCount = _verticesCount;
    }
    void findShortestCycle() 
    {
        double currentSum = 0;
        vector<bool> _visited( verticesCount, false );
        recursiveSearch( 0, _visited, currentSum);
        return;
    }
    double recursiveSearch( int startVertex, vector<bool> _visited, double currentSum ) 
    {
        _visited[startVertex] = true;
        bool endIndex = true;
        for( int i = 0; i < verticesCount; ++i ) {
            if( !_visited[i] ) {
                endIndex = false;
                vector<bool> tempVisit( _visited );
                recursiveSearch( i, tempVisit, currentSum + graph[startVertex][i] );
            }
        }
        if( endIndex == true && currentSum + graph[0][startVertex] < answerCycleLen ) {
            answerCycleLen = currentSum + graph[0][startVertex];
        }
        return currentSum;
    }
    double getAnswerCycleLen()const 
    {
        return answerCycleLen;
    }
private:
    const static int infinity = 1000000000;
    int verticesCount;
    double answerCycleLen;
    const vector<vector<double> >& graph;
};