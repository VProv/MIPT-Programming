/*#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class CTest {

public:
    // ¬ход.
    void ReadTest()
    {
        std::cin >> str >> templ;
    }
    std::string str;
    std::string templ;
private:
};

class CNetwork {
public:
    CNetwork::CNetwork( const CTest& test ) :
        numberOfVertices( test.str.size() + test.templ.size() + 2 ), source( 0 ),
        target( numberOfVertices - 1 ), disbalance( 0 )
    {
        linksToEdges.resize( numberOfVertices );
        labelsOfFirstPart.assign( test.str.length(), -1 );
        for( int i = 0; i < test.str.length() ; ++i ) {
            labelsOfFirstPart[i] = ( test.str[i] == '?' ) ? -1 : test.str[i] - '0' ;
        }
        labelsOfSecondPart.assign( test.templ.length(), -1 );
        for( int i = 0; i < test.templ.length(); ++i ) {
            labelsOfSecondPart[i] = ( test.templ[i] == '?' ) ? -1 : test.templ[i] - '0';
        }
        for( int i = 0; i < test.templ.length(); ++i ) {
            for( int j = i; j - i < test.str.length() - test.templ.length() + 1; ++j )
            {
                int vertexFromStr = j + 1;
                int vertexFromtempl = i + test.str.length() + 1;
                if( test.str[j] == '?' && test.templ[i] == '?' ) {
                    addEdge( vertexFromStr, vertexFromtempl, 1, 1 );
                }
                else if( test.str[j] == '?' && test.templ[i] == '0' ) {
                    addEdge( source, vertexFromStr, 1 );
                }
                else if( test.str[j] == '?' && test.templ[i] == '1' ) {
                    addEdge( vertexFromStr, target, 1 );
                }
                else if( test.str[j] == '0' && test.templ[i] == '?' ) {
                    addEdge( source, vertexFromtempl, 1 );
                }
                else if( test.str[j] == '0' && test.templ[i] == '1' ) {
                    ++disbalance;
                }
                else if( test.str[j] == '1' && test.templ[i] == '?' ) {
                    addEdge( vertexFromtempl, target, 1 );
                }
                else if( test.str[j] == '1' && test.templ[i] == '0' ) {
                    ++disbalance;
                }
            }
        }
    }

    void addEdge( int from, int to, int capacity, int reverseCapacity )
    {
        linksToEdges[from].push_back( static_cast<int>( edges.size() ) );
        edges.push_back( CEdge( from, to, capacity ) );
        linksToEdges[to].push_back( static_cast<int>( edges.size() ) );
        edges.push_back( CEdge( to, from, reverseCapacity ) );
    }

private:
    int source;
    int target;
    int disbalance;
    int numberOfVertices;

    std::vector<std::vector<int>> linksToEdges;
    std::vector<int> labelsOfFirstPart;
    std::vector<int> labelsOfSecondPart;
};

using namespace std;

int main()
{
    CTest test;
    test.ReadTest();
    CNetwork network( test );
    cout << network.GetMaxFlow() << std::endl;
    network.PrintLabels();
    int n;
    cin >> n;
    return 0;
}*/