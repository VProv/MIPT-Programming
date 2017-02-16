#include <algorithm>
#include "Tag8.h"

void CTag8::solveTag( shared_ptr<CBoard> startVertex, fstream& output )
{
    nodes.push( startVertex );
    while( !nodes.empty() )
    {
        // Вытаскиваем вершину из очереди.
        shared_ptr<CBoard> current = nodes.front();
        nodes.pop();
        // Создаем ее детей.
        current->CreateChildren();
        if( current->isEnd() ) {
            result = current;
            break;
        }
        for( auto it = current->Children.begin(); it != current->Children.end(); ++it )
        {
            ( *it )->Parent = current;

            if( passedNodes.find( ( *it )->getStateInt() ) == passedNodes.end() ) {
                passedNodes.insert( ( *it )->getStateInt() );
                nodes.push( *it );
            }
        }
    }

    std::string resultString = "";
    // Идем по родителям, восстанавливая путь.
    while( result.lock()->GetWay() != '\0' ) {
        resultString += result.lock()->GetWay();
        result = result.lock()->Parent;
    }

    output << resultString.size() << std::endl;
    reverse( resultString.begin(), resultString.end() );
    output << resultString;
}

bool CTag8::CheckPossibility(const vector<int>& tempForExisting )const
{
    // Сумма количества инверсий.
    int sum = 0;
    for( int i = 0; i < 9; ++i )
    {
        if( tempForExisting[i] != 0 ) {
            for( int j = i + 1; j < 9; ++j )
            {
                if( tempForExisting[j] < tempForExisting[i] && tempForExisting[j] != 0 ) ++sum;
            }
        }
    }

    if( sum % 2 == 0 ) return true;

    return false;
}