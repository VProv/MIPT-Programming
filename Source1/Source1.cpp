// ������� ������ "���������� ��������"
// ��������� ���� ��.593.
#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::deque;
using std::pair;
using std::max;
using std::min;
using std::string;

// ��������� � ������ ������� ������.
class CReader {
public:
    // ����.
    void ReadTest()
    {
        std::cin >> str >> templ;
    }
    // ������� ������.
    string str;
    // ������� ����������� ������.
    string templ;
};

// ����� � �����.
struct CEdge {

    CEdge( int from, int to, int value, int flow = 0 ) :
        From( from ), To( to ), value( value ), Flow( flow )
    {
    }
    int From;
    int To;
    int value;
    int Flow;
};

// ����� ���� � ������� ������������� ������.
// ���������� �������� ������.
class CNetwork {
public:
    // ����������� ���� �� ������� ������.
    CNetwork( const CReader& test );

    int GetMaxFlow();
    // ����� � cout ����� ������.
    void PrintRelations();
    // ���������� �����
    void addEdge( int from, int to, int value, int reversevalue = 0 );
    // ���������� �������� �������.
    int inverseIndex( int index ) const;
    // �������� ������������� ���� �� �����.
    int isPathToTarget() const;
    int getPushFlow( int vertex, int flow );
    // ������� ���������� �� ������ �� ���� ������.
    void countDistancesFromSource();
    void getRelations();
    void transVector( std::vector<int>& vector );
    void printVector( const std::vector<int>& vector ) const;
    void markVertices( int vertex );
    const static int Infinity;
private:
    int source;
    int target;
    int numberOfVertices;
    // �������� � ���� �������.
    int conflicts;
    std::vector<CEdge> edges;
    std::vector<bool> visited;
    std::vector<int> pointerToNextEdge;
    std::vector<std::vector<int>> relationsToEdges;
    std::vector<int> distanceFromSource;
    std::vector<int> nullVertices;
    std::vector<int> singleVertices;
};
const int CNetwork::Infinity = 100000000;
// ������ ���� �� ��������� ������� ������ �� ������ CReader.
CNetwork::CNetwork( const CReader& test ) :
    numberOfVertices( test.str.length() + test.templ.length() + 2 ), source( 0 ),
     conflicts( 0 )
{
    target = numberOfVertices - 1;
    relationsToEdges.resize( numberOfVertices );
    nullVertices.assign( test.str.length(), -1 );
    for( int i = 0; i < test.str.length(); ++i ) {
        if( test.str[i] == '?' ) {
            nullVertices[i] = -1;
        }
        else {
            nullVertices[i] = test.str[i] - '0';
        }
    }
    singleVertices.assign( test.templ.length(), -1 );
    for( int i = 0; i < test.templ.length(); ++i ) {
        if( test.templ[i] == '?' ) {
            singleVertices[i] = -1;
        }
        else {
            singleVertices[i] = test.templ[i] - '0';
        }
    }
    // ������ ��� ���� �������� ����� ������������� ���� ���������:
    // ? ? -> ����� 1 ����� ����.
    // ? 0 -> +=����� ����� ?
    // ? 1 -> +=����� ���� ?
    // ���� ������ ��������� ����� � ����� ����, �� ��������� ���������.
    for( int i = 0; i < test.templ.length(); ++i ) {
        for( int j = i; j - i < test.str.length() - test.templ.length() + 1; ++j ) {
            int strVertex = j + 1;
            int templVertex = i + test.str.length() + 1;
            if( test.str[j] == '?' && test.templ[i] == '?' ) {
                addEdge( strVertex, templVertex, 1, 1 );
            }
            else if( test.str[j] == '?' && test.templ[i] == '0' ) {
                addEdge( source, strVertex, 1 );
            }
            else if( test.str[j] == '?' && test.templ[i] == '1' ) {
                addEdge( strVertex, target, 1 );
            }
            else if( test.str[j] == '0' && test.templ[i] == '?' ) {
                addEdge( source, templVertex, 1 );
            }
            else if( test.str[j] == '0' && test.templ[i] == '1' ) {
                ++conflicts;
            }
            else if( test.str[j] == '1' && test.templ[i] == '?' ) {
                addEdge( templVertex, target, 1 );
            }
            else if( test.str[j] == '1' && test.templ[i] == '0' ) {
                ++conflicts;
            }
        }
    }
}

// �������� ������������ ����� � ��������������� ���������, ������������ �������� ������.
int CNetwork::GetMaxFlow()
{
    int flow = 0;
    int pushFlow = 0;
    while( true ) {
        countDistancesFromSource();
        if( !isPathToTarget() ) {
            break;
        }
        pointerToNextEdge.assign( numberOfVertices, 0 );
        do {
            pushFlow = getPushFlow( source, Infinity );
            flow += pushFlow;
        } while( pushFlow != 0 );
    }
    // ��������� �� ��� ���� ��������� ��� �����.
    return flow + conflicts;
}

// �������� ���� �������.
void CNetwork::PrintRelations()
{
    getRelations();
    printVector( nullVertices );
    printVector( singleVertices );
}

// ��������� ���� �����.
void CNetwork::addEdge( int from, int to, int value, int reversevalue )
{
    relationsToEdges[from].push_back( edges.size() );
    edges.push_back( CEdge( from, to, value ) );
    relationsToEdges[to].push_back( edges.size() );
    edges.push_back( CEdge( to, from, reversevalue ) );
}
// ��������� �������(�����������) ������� ����� � �������.
int CNetwork::inverseIndex( int index ) const
{
    return index ^ 1;
}

// BFS. ������� ���������� �� ��������� �� ���� ��������� ������.
void CNetwork::countDistancesFromSource()
{
    deque<int> queue;

    queue.push_back( source );
    distanceFromSource.assign( numberOfVertices, Infinity );

    distanceFromSource[source] = 0;
    while( !queue.empty() ) {
        int curVertex = queue.front();
        queue.pop_front();
        for( int i = 0; i < relationsToEdges[curVertex].size(); ++i ) {
            int index = relationsToEdges[curVertex][i];
            int	to = edges[index].To;

            if( distanceFromSource[to] == Infinity && edges[index].Flow < edges[index].value ) {
                queue.push_back( to );
                distanceFromSource[to] = distanceFromSource[curVertex] + 1;
            }
        }
    }
}

// ��������, ���������� �� ������������� ���� � ����.
int CNetwork::isPathToTarget() const
{
    return (distanceFromSource[target] != Infinity);
}

// �������� ������� ����� � ����, ����������, ������� ����������.
int CNetwork::getPushFlow( int vertex, int flow )
{
    if( flow == 0 ) {
        return 0;
    }
    if( vertex == target ) {
        return flow;
    }
    while( pointerToNextEdge[vertex] < relationsToEdges[vertex].size() ) {
        int index = relationsToEdges[vertex][pointerToNextEdge[vertex]];
        int to = edges[index].To;
        if( distanceFromSource[to] != distanceFromSource[vertex] + 1 ) {
            ++pointerToNextEdge[vertex];
            continue;
        }
        int push = getPushFlow( to, min( flow, edges[index].value - edges[index].Flow ) );
        if( push != 0 ) {
            edges[index].Flow += push;
            edges[inverseIndex( index )].Flow -= push;
            return push;
        }
        ++pointerToNextEdge[vertex];
    }
    return 0;
}

// �������� ��� ������� ������, ��������� �� ������� �� ������, ���������� (����� � �������).
void CNetwork::markVertices( int vertex )
{
    visited[vertex] = true;
    for( int i = 0; i < relationsToEdges[vertex].size(); ++i ) {
        CEdge edge = edges[relationsToEdges[vertex][i]];
        if( !visited[edge.To] && edge.Flow < edge.value ) {
            if( edge.To <= nullVertices.size() ) {
                nullVertices[edge.To - 1] = max( 0, nullVertices[edge.To - 1] );
            }
            else {
                singleVertices[edge.To - 1 -  nullVertices.size() ] =
                    max( 0, singleVertices[edge.To - 1 - nullVertices.size()] );
            }
            markVertices( edge.To );
        }
    }
}

// DFS, ��������� ����������� �����.
void CNetwork::getRelations()
{
    visited.assign( numberOfVertices, false );
    markVertices( source );
    transVector( nullVertices );
    transVector( singleVertices );
}

// �������� ��� -1 � ������� �� 1.
void CNetwork::transVector( std::vector<int>& curVector ) {
    for( vector<int>::iterator i = std::begin( curVector ); i != std::end( curVector ); ++i ) {
        if( *i == -1 ) {
            *i = 1;
        }
    }
}

void CNetwork::printVector( const std::vector<int>& _vector ) const
{
    for( int i = 0; i < _vector.size(); ++i ) {
        std::cout << _vector[i];
    }
    std::cout << std::endl;
}

using namespace std;

int main()
{
    CReader test;
    test.ReadTest();
    CNetwork network( test );
    cout << network.GetMaxFlow() << std::endl;
    network.PrintRelations();
    int n;
    cin >> n;
    return 0;
}