#pragma once
#include <array>

//���� �� ������ �����, ���������� � ��������� ���� 
class CVertex {
public:
    CVertex( const CVertex& _parent, int _distance, int _heuristic ):
        parent( &const_cast< CVertex& >( _parent ) ), distance( _distance ), heuristic( _heuristic ) {};
    CVertex( ):
        parent( nullptr ), distance( 0 ), heuristic( 0 ) {};
    CVertex( const CVertex* _parent, int _distance, int _heuristic ):
        parent( const_cast< CVertex* >( _parent ) ), distance( _distance ), heuristic( _heuristic ) {};
    //���������� ����������� �� ����� ��� ��������� ������
    std::array<std::array<int, 3>, 3 > GetArrangement( )const;
    int GetIntArrangement( )const {
        return arrangement;
    }
    int getDistance( )const {
        return distance;
    }
    int getHeuristic( )const {
        return heuristic;
    }
    CVertex* getParent( ) {
        return parent;
    }
    void setDistance( int _distance);
    void setParent( CVertex* _parent);
    void setHeuristic( int _heuristic);
private:
    CVertex* parent;
    //���������� �� ������� ������� �� ���������
    int distance;
    //��������� ���������� �� ������� ������� �� �������� 
    int heuristic;
    // ����������� ����� �� �����
    int arrangement;
};

class CVertexCompare {
public:
    bool operator () ( const CVertex& a, const CVertex& b ) {
        return a.GetIntArrangement( ) < b.GetIntArrangement( );
    }
};

class CVertexPriority {
public:
    bool operator() ( const CVertex& a, const CVertex& b ) {
        return;
    }
};