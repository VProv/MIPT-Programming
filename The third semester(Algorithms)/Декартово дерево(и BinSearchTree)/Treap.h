#pragma once
// ���������� ������ �� ������ �����.
// ��������� ����. ��.593.
#include <memory>
#include <algorithm>

// ������� ������ ������.
class CNode {
public:
    // ����.
    int x;
    // ���������.
    int y;
    CNode* left;
    CNode* right;
    CNode( int _x, int _y, CNode* _left = 0, CNode* _right = 0) {
        x = _x;
        y = _y;
        left = _left;
        right = _right;
    }
    // ���������� ������� ��� �������.
    ~CNode() {
        if( left != nullptr ) {
            delete left;
        }
        if( right != nullptr ) {
            delete right;
        }
    }
};

// ����� ��������� ������ �� ������ �����.
class CTreap {

public:
    // ������.
    CNode* root;
    CTreap( int _x, int _y, CNode* _left = 0, CNode*  _right = 0 ) {
        root = new CNode( _x, _y, _left, _right );
    };
    // ��������� ����������� �������� ���� ������.
    ~CTreap() {
        delete root;
    }
    CNode* getRoot()const {
        return root;
    }
    // ������� 2 ���������� ������ � ����. ����� � ������ left ������ ���� ������ ��� ����� � right.
    CNode* Merge( CNode* left, CNode* right );
    // ��������� �������� ��������� ������ �� �����. ���������� ������������ ������ � ������� ������ � left, � ������� � right.
    void Split( CNode* currentNode, int key, CNode*& left, CNode*& right );
    // ��������� �������.
    // ����� �� ����� �� ���� P � ������� �����������.����� ��������� ��������� ��������� �� ����� x ���, 
    // ����� � ������ ��������� ��� ����� ������ x, � �� ������ ������ ��� ����� x.
    // ������������ ��� ������ ������ ��������� ��� ������ ����( x, y ). ����� ���� ��������� �� ����� P.
    CNode* insert( int key, int priority );

    // ����������� ������� ������ ������.
    int height( CNode* start );
private:
};