// Класс обертки для представления расстановки на доске в восьминажках в виде int.
#include <vector>
#include <cassert>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <fstream>
#include <iostream>

using std::vector;
using std::string;
// Обертка для состояния доски в игре "восьминашки".
class CBoard {
public:
    CBoard( int _state = 0, string _way = "", int _null = 0 ) : way() { state = _state; way = _way; nullPosition = _null; }
    CBoard( const vector<vector<int> >& _state, string _way );
    CBoard( const vector<int>& _state, string way );
    // Возвращает расстановку на доске как вектор.
    vector<vector<int> > getBoardVector()const;
    int getBoardInt()const { return state; }
    vector<int> getBoardOneVector()const;
    bool operator == ( const CBoard& right ) { return state == right.state; }

    CBoard generateLeft()const;
    CBoard generateRight()const;
    CBoard generateDown()const;
    CBoard generateUp()const;
    int getNullPosition()const { return nullPosition; }
    string getWay()const { return way; }
    int getBoardLength()const { return boardLength; }
private:
    // Состояние доски, числа записаны с конца, 0 - пустая клетка.
    int state;
    //Длина стороны доски
    const static int boardLength = 3;
    string way;
    int nullPosition;
    static int powTen( int n )
    {
        static int pow10[10] = {
            1, 10, 100, 1000, 10000,
            100000, 1000000, 10000000, 100000000, 1000000000
        };

        return pow10[n];
    }
    int GetByIndex( int ind )const { return ( state % powTen( 9 - ind ) - state % powTen( 8 - ind ) ) / powTen( 8 - ind ); }
};


using std::vector;
using std::swap;
CBoard::CBoard( const vector<vector<int> >& _state, string _way ) : way()
{
    way = _way;
    state = 0;
    int k = _state.size();
    for( int i = 0; i < k; ++i )
        for( int j = 0; j < k; ++j ) {
            state = state * 10 + _state[i][j];
            if( _state[i][j] == 0 )
                nullPosition = i * boardLength + j;
        }
}

vector<vector<int> > CBoard::getBoardVector()const
{
    int tempState = state;
    vector<vector<int> > result( boardLength, vector<int>( boardLength ) );
    for( vector < vector<int> >::reverse_iterator it = result.rbegin(); it != result.rend(); ++it )
        for( vector <int>::reverse_iterator it1 = it->rbegin(); it1 != it->rend(); ++it1 ) {
            *it1 = tempState % 10;
            tempState /= 10;
        }
    return result;
}

vector<int> CBoard::getBoardOneVector()const
{
    int tempState = state;
    vector<int> result( boardLength * boardLength );
    for( int i = boardLength * boardLength - 1; i >= 0; --i ) {
        result[i] = tempState % 10;
        tempState /= 10;
    }
    return result;
}

CBoard::CBoard( const vector<int>& _state, string _way ) :
    way()
{
    nullPosition = 0;
    state = 0;
    for( int i = 0; i < boardLength *boardLength; ++i ) {
        if( _state[i] == 0 )
            nullPosition = i;
        state = state * 10 + _state[i];
    }
    way = _way;
}

CBoard CBoard::generateDown() const
{
    int temp = this->state;
    int exchange = GetByIndex( nullPosition + 3 );
    temp = temp - ( temp % powTen( 9 - ( nullPosition + 3 ) ) - state % powTen( 8 - ( nullPosition + 3 ) ) ) +
        exchange * powTen( 8 - nullPosition );
    CBoard result( temp, way + 'D', nullPosition + 3 );
    return result;
}

CBoard CBoard::generateUp()const
{
    int temp = this->state;
    int exchange = GetByIndex( nullPosition - 3 );
    temp = temp - ( temp % powTen( 9 - ( nullPosition - 3 ) ) - state % powTen( 8 - ( nullPosition - 3 ) ) ) +
        exchange * powTen( 8 - nullPosition );
    CBoard result( temp, way + 'U', nullPosition - 3 );
    return result;
}

CBoard CBoard::generateLeft()const
{
    int temp = this->state;
    int exchange = GetByIndex( nullPosition - 1 );
    temp = temp - ( temp % powTen( 9 - ( nullPosition - 1 ) ) - state % powTen( 8 - ( nullPosition - 1 ) ) ) +
        exchange * powTen( 8 - nullPosition );
    CBoard result( temp, way + 'L', nullPosition - 1 );
    return result;
}

CBoard CBoard::generateRight()const
{
    int temp = this->state;
    int exchange = GetByIndex( nullPosition + 1 );
    temp = temp - ( temp % powTen( 9 - ( nullPosition + 1 ) ) - state % powTen( 8 - ( nullPosition + 1 ) ) ) +
        exchange * powTen( 8 - nullPosition );
    CBoard result( temp, way + 'R', nullPosition + 1 );
    return result;
}



using std::queue;
using std::set;
class CTag8 {
public:
    CTag8( int _node ) :
        nodes(), passedTops()
    {
        CBoard tempBoard( _node );
        nodes.push( tempBoard );
    }
    string solveTag();
private:
    // Очередь узлов в нашем поиске.
    queue<CBoard> nodes;
    // Множство пройденных вершин, необходимо для поиска пути.
    set<int> passedTops;
};



using std::swap;
string CTag8::solveTag()
{
    CBoard Current = nodes.front();
    passedTops.insert( Current.getBoardInt() );
    // Целевое состояние.
    CBoard Target( 123456780 );
    // Вектор для проверки существования решения.
    vector<int> tempForExisting = Current.getBoardOneVector();
    int inversionsSum = 0;
    // Длина доски.
    int boardLength = Current.getBoardLength();
    // Решение будет существовать, только когда сумма инверсий в итоге четна.
    for( int i = 0; i < boardLength * boardLength; ++i )
        if( tempForExisting[i] == 0 )
            tempForExisting[i] = 9;
    for( int i = 0; i < 9; ++i ) {
        for( int j = 0; j < i; ++j ) {
            if( tempForExisting[j] < tempForExisting[i] )
                ++inversionsSum;
        }
    }
    if( inversionsSum % 2 ) {
        string solution( "0" );
        return solution;
    }
    // Основная часть решения.
    while( !nodes.empty() ) {
        Current = nodes.front();
        nodes.pop();
        if( Current == Target ) {
            // Возвращаем ответ.
            return Current.getWay();
        }
        passedTops.insert( Current.getBoardInt() );
        // Позиция нуля на доске
        int x = 0, y = 0;
        vector<int> tempState = Current.getBoardOneVector();
        x = Current.getNullPosition() / boardLength;
        y = Current.getNullPosition() - x * boardLength;
        if( x - 1 >= 0 ) {
            CBoard newItem = Current.generateUp();
            if( passedTops.find( newItem.getBoardInt() ) == passedTops.end() )
                nodes.push( newItem );
        }
        if( x + 1 <= ( boardLength - 1 ) ) {
            CBoard newItem = Current.generateDown();
            if( passedTops.find( newItem.getBoardInt() ) == passedTops.end() )
                nodes.push( newItem );
        }
        if( ( y + 1 ) <= ( boardLength - 1 ) ) {
            CBoard newItem = Current.generateRight();
            if( passedTops.find( newItem.getBoardInt() ) == passedTops.end() )
                nodes.push( newItem );
        }
        if( y - 1 >= 0 ) {
            CBoard newItem = Current.generateLeft();
            if( passedTops.find( newItem.getBoardInt() ) == passedTops.end() )
                nodes.push( newItem );
        }
    }
}



using namespace std;

int main()
{
    // Окрываем файл для считывания.
    ifstream InFile( "puzzle.in" );
    // Открываем файл для записи.
    ofstream OutFile( "puzzle.out" );
    int n = 0;
    for( int i = 0; i < 9; ++i ) {
        int k;
        InFile >> k;
        n = n * 10 + k;
    }
    CTag8 Tag( n );
    string result = Tag.solveTag();
    if( result == "0" ) {
        OutFile << -1;
    }
    else {
        OutFile << result.size() << endl;
        OutFile << result;
    }
    return 0;
}