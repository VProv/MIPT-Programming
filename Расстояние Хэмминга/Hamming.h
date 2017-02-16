#pragma once
#include <vector>
#include <string>
#include <queue>
#include "RaiseBegin.h"

using std::vector;
using std::string;
using std::pair;
using std::queue;

class CHamming {

public:
    CHamming( string& _st, string& _temp ) :
        st( _st ), temp( _temp ) {}

    void solveHamming() {
        int questionNum = 0;
        int stSize = st.size();
        int tempSize = temp.size();
        // Изначально все элементы массива индексов -1.
        stIndex.assign( stSize, -1 );
        tempIndex.assign( tempSize, -1 );
        index.push_back( std::make_pair( 0, -1 ) );
        // Считаем количество вопросиков.
        for( int i = 0; i < stSize; ++i ) {
            if( st[i] == '?' ) {
                index.push_back( std::make_pair( 0, i ) );
                stIndex[i] = questionNum + 1;
                questionNum++;
            }
        }
        for( int i = 0; i < tempSize; ++i ) {
            if( temp[i] == '?' ) {
                index.push_back( std::make_pair( 1, i ) );
                tempIndex[i] = questionNum + 1;
                questionNum++;
            }
        }
        index.push_back( std::make_pair( 0, -2 ) );
        graph.assign( questionNum + 2, vector<int>( questionNum + 2, 0 ) );
        int start = 0;
        int destination = questionNum + 1;
        int conflicts = 0;

        for( int i = 0; i < stSize - tempSize + 1; ++i ) {
            for( int j = 0; j < tempSize; ++j ) {
                if( ( st[j + i] == '1' && temp[j] == '0' ) || ( st[j + i] == '0' && temp[j] == '1' ) ) {
                    conflicts++;
                }
                else if( st[j + i] == '?' && temp[j] == '0' ) {
                    graph[stIndex[j + i]][0] += 1;
                    graph[0][stIndex[j + i]] += 1;
                }
                else if( st[j + i] == '?' && temp[j] == '1' ) {
                    graph[stIndex[j + i]][questionNum + 1] += 1;
                    graph[questionNum + 1][stIndex[j + i]] += 1;
                }
            }
        }

        for( int i = 0; i < index.size(); ++i ) {
            if( index[i].first == 1 ) {
                // Индекс текущего вопроса в строке temp.
                int curIndex = index[i].second;
                for( int j = 0; j < stSize - tempSize + 1; ++j ) {
                    if( st[curIndex + j] == '?' ) {
                        graph[i][stIndex[curIndex + j]] = 1;
                        graph[stIndex[curIndex + j]][i] = 1;
                    }
                    else if( st[curIndex + j] == '0' ) {
                        graph[0][i] += 1; 
                        graph[i][0] += 1;
                    }
                    else if( st[curIndex + j] == '1' ) {
                        graph[questionNum + 1][i] += 1;
                        graph[i][questionNum + 1] += 1;
                    }
                }
            }
        }
        answerSize = 0;
        
        CRaiseBegin solver( questionNum + 2, 0, questionNum + 1, graph );
        answerSize = solver.raiseToBegin();
        answerSize += conflicts;
        vector<vector<int>>& flow = solver.getFlow();
        vector<bool> visited( questionNum + 2, false );
        bfs( flow, questionNum + 2, visited );
        
        for( int i = 1; i < questionNum + 1; ++i ) {
            if( visited[i] == true ) {
                if( index[i].first == 0 ) {
                    st[index[i].second] = '0';
                }
                else if( index[i].first == 1 ) {
                    temp[index[i].second] = '0';
                }
            }
            else {
                if( index[i].first == 0 ) {
                    st[index[i].second] = '1';
                }
                else if( index[i].first == 1 ) {
                    temp[index[i].second] = '1';
                }
            }
        }
    }

    void bfs( vector<vector<int>> flow, int num, vector<bool>& used ) {
        queue<int> q;
        q.push( 0 );
        used[0] = true;
        while( !q.empty() ) {
            int v = q.front();
            q.pop();
            for( int i = 0; i < graph[v].size(); ++i ) {
                int to = i;
                if( !used[to] && graph[v][to] != flow[v][to] ) {
                    used[to] = true;
                    q.push( to );
                }
            }
        }
    }
    
    int getAnswerSize()const {
        return answerSize;
    }

private:
    // Номера вопросиков в графе, пара из номера строки в индекс в этой строке.
    // По номеру получаем индекс в строке.
    vector<pair<bool, int> > index;
    
    // Вектор длины строк, если на этом месте стоит ?, то в нем записан его номер в графе.
    // По индексу получаем номер.
    vector<int> stIndex;
    vector<int> tempIndex;
    int answerSize;
    string& st;
    string& temp;
    vector<vector<int> > graph;
};