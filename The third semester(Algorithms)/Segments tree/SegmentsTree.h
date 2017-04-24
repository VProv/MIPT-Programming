#pragma once
// ����� �������� ������ ���������� 2� ���������� ���������� �� �������, � ������� ������ ��������.
// ��������� ����. ��.593.
#include <vector>
#include <cmath>
#include <algorithm>
using std::vector;

// ����� ������ ��������.
class CSegmentsTree {
public:
    // ��������� ������ ������ ����� ��������� � ����� ���������� �� �������.
    // min1 <= min2.
    struct node {
        int min1;
        int min2;
        node( int _min1, int _min2 ) :min1(_min1),min2(_min2) {};
    };
    // �����������, ������ ������ �������� �� ��������� ������� a.
    CSegmentsTree( vector<int>& a );
    // ��������� 2� ���������� ���������� �� ������� �� l �� r.
    int RMQUp( int l, int r );
    
private:
    // ������� ������������ ���������� ������ ��������.
    void treeBuild( int i, int l, int r );
    // ���������� node � ���������� min1 � min2, �� 2� node.
    node myMin( const node& l, const node& r )const;
    // ������ �� ������� ������ � ������� �� ��������.
    vector<int>& arr;
    // ������, ���������� ���� ������.
    vector<node> tree;
    const static int infinity = 100000000;
};