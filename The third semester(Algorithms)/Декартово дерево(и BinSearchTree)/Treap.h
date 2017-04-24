#pragma once
// Декартовов дерево по явному ключу.
// Провилков Иван. гр.593.
#include <memory>
#include <algorithm>

// Вершина нашего дерева.
class CNode {
public:
    // Ключ.
    int x;
    // Приоритет.
    int y;
    CNode* left;
    CNode* right;
    CNode( int _x, int _y, CNode* _left = 0, CNode* _right = 0) {
        x = _x;
        y = _y;
        left = _left;
        right = _right;
    }
    // Рекурсивно удаляем все вершины.
    ~CNode() {
        if( left != nullptr ) {
            delete left;
        }
        if( right != nullptr ) {
            delete right;
        }
    }
};

// Класс декартова дерева по явному ключу.
class CTreap {

public:
    // Корень.
    CNode* root;
    CTreap( int _x, int _y, CNode* _left = 0, CNode*  _right = 0 ) {
        root = new CNode( _x, _y, _left, _right );
    };
    // Запускает рекурсивное удаление всех вершин.
    ~CTreap() {
        delete root;
    }
    CNode* getRoot()const {
        return root;
    }
    // Сливает 2 декартовых дерева в одно. Ключи в дереве left должны быть меньше чем ключи в right.
    CNode* Merge( CNode* left, CNode* right );
    // Разрезает заданное декартово дерево по ключу. Записывает получившееся дерево с меньшим ключем в left, с большим в right.
    void Split( CNode* currentNode, int key, CNode*& left, CNode*& right );
    // Вставляет элемент.
    // Спуск по ключу до узла P с меньшим приоритетом.Затем разбеваем найденное поддерево по ключу x так, 
    // чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x.
    // Получившиеся два дерева делаем дочерними для нового узла( x, y ). Новый узел вставляем на место P.
    CNode* insert( int key, int priority );

    // Рекурсивный подсчет высоты дерева.
    int height( CNode* start );
private:
};