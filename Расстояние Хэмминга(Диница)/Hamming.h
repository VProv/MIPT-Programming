#pragma once
// ����� ������� ������ �������� � ������� ��������� ������.
// ��������� ����. ��.593.
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

// ����� � �����. ������������ ������ ����� ���� �����.
struct CEdge {

    CEdge( int from, int to, int value, int flow = 0 ) :
        From( from ), To( to ), value( value ), Flow( flow ){}
    // ����� ������� ������ ���� �����.
    int From;
    // ����� ������� ���� ���� �����.
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
    const static int Infinity;
private:
    int source;
    int target;
    int numberOfVertices;
    // �������� � ���� �������.
    int conflicts;
    std::vector<CEdge> edges;
    std::vector<bool> visited;
    // ��������� �� ��������� �����.
    std::vector<int> pointerToNextEdge;
    // � [i][j] �������� ������ ����� � ������� �����, � ��� ����� j-e �� i-� �������, j-������ ����� � �������.
    // ������������ ���������� ������ ����� �����������.
    std::vector<std::vector<int>> relationsToEdges;
    std::vector<int> distanceFromSource;
    // ����� ������ �����.
    std::vector<int> nullVertices;
    // ����� ������ �����.
    std::vector<int> singleVertices;

    // ������� ���������� �� ������ �� ���� ������.
    void countDistancesFromSource();
    void getRelations();
    void transVector( std::vector<int>& vector );
    void printVector( const std::vector<int>& vector ) const;
    void markVertices( int vertex );
};


