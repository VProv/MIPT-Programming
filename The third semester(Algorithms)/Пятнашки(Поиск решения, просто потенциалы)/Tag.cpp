#include <algorithm>
#include "Tag.h"


void CTag::solveTag( shared_ptr<CBoard> startVertex, fstream& output )
{
    nodes.push( startVertex );
    bool stop = false;

    while( !stop )
    {
        // Вытаскиваем вершину из очереди.
        shared_ptr<CBoard> current = nodes.top();
        nodes.pop();
        // Создаем ее детей.
        current->CreateChildren();

        for( auto it = current->Children.begin(); it != current->Children.end(); ++it )
        {
            ( *it )->Parent = current;

            if( !( *it )->isEnd() ) {
                if( passedNodes.find( ( *it )->getStateLong() ) == passedNodes.end() ) {
                    passedNodes.insert( std::pair<unsigned long long, int>(( *it )->getStateLong(), 
                                                                           (*it)->getDistanceStart()));
                    nodes.push( *it );
                }
                else {
                    if( passedNodes[( *it )->getStateLong()] > ( *it )->getDistanceStart() )
                        passedNodes[( *it )->getStateLong()] = ( *it )->getDistanceStart();
                }
            }
            else {
                result = *it;
                stop = true;
                break;
            }
        }
    }

    std::string resultString = "";
    int resultCount = 0;

    while( result.lock()->GetWay() != '\0' ) {

        resultString += result.lock()->GetWay();
        result = result.lock()->Parent;
        ++resultCount;
    }

    output << resultCount << std::endl;
    reverse( resultString.begin(), resultString.end() );
    output << resultString;
}

bool CTag::CheckPossibility( vector<char> tempForExisting )const
{
    int inv = 0;
    for( int i = 0; i < CBoard::GetBoardSquare(); ++i )
        if( tempForExisting[i] )
            for( int j = 0; j<i; ++j )
                if( tempForExisting[j] > tempForExisting[i] )
                    ++inv;
    for( int i = 0; i < CBoard::GetBoardSquare(); ++i )
        if( tempForExisting[i] == 0 )
            inv += 1 + i / 4;

    if( inv % 2 == 0 ) return true;

    return false;
}