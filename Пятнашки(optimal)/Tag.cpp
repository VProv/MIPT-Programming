#include <algorithm>
#include "Tag.h"

using std::make_pair;

pair<int,bool> CTag::_search( CBoard& current, int gamut, int bound, std::vector<char>& answer ) {
    int f = gamut + current.getHeuristic();
    if( f > bound ) return std::make_pair(f,false);
    if( current.isEnd() ) {
        return std::make_pair( -1, true );
    }
    int min = infinity;
    vector<CBoard> Children = current.CreateChildrenVector();
    for( auto it = Children.begin(); it != Children.end(); ++it ) {
        pair<int, bool> temp = _search( (*it), gamut + 1, bound, answer );
        if( temp.second == true ) {
            answer.push_back( it->GetWay() );
            return std::make_pair( -1, true );
        }
        if( temp.first < min )
            min = temp.first;
    }
    return std::make_pair( min, false );
}

void CTag::solveTag( CBoard& startVertex, fstream& output )
{
    vector<char> answer;
    startVertex.CountHeuristic();
    int bound = startVertex.getHeuristic();
    bool stop = false;
    while( !stop ) {
        pair<int,bool> t = _search( startVertex, 0, bound, answer );
        if( t.second == true )
            stop = true;
        bound = t.first;
    }
    std::reverse( answer.begin(), answer.end() );
    output << answer.size() << std::endl;
    for( auto i = answer.begin(); i < answer.end(); ++i ) {
        output << (*i);
    }
}

bool CTag::CheckPossibility(const vector<char>& tempForExisting )const
{
    int inv = 0;
    for( int i = 0; i<16; ++i )
        if( tempForExisting[i] )
            for( int j = 0; j<i; ++j )
                if( tempForExisting[j] > tempForExisting[i] )
                    ++inv;
    for( int i = 0; i<16; ++i )
        if( tempForExisting[i] == 0 )
            inv += 1 + i / 4;

    if( inv % 2 == 0 ) return true;

    return false;
}