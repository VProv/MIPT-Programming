
class CBSTree
{
public:
    struct CNode
    {
        int data;
        CNode *parent, *left, *right;
    };
private:
    CNode* Root;
public:
    CBSTree() : Root( nullptr ) {}
    void InsertCNode( int n )
    {
        CNode* z = new CNode;
        CNode* y = nullptr;
        CNode* x = Root;
        z->data = n;
        while( x != nullptr ) {
            y = x;
            if( ( z->data ) < ( x->data ) )
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if( y == nullptr )
            Root = z;
        else
        {
            if( ( z->data ) < ( y->data ) )
                y->left = z;
            else
                y->right = z;
        }
        z->left = nullptr;
        z->right = nullptr;
    }
    CBSTree( int n )
    {
        InsertCNode( n );
    }
    //Итеративный поиск
    CNode* FindCNode( int n )
    {
        CNode* x = Root;
        while( ( x != nullptr ) && ( x->data != n ) ) {
            if( n < ( x->data ) )
                x = x->left;
            else
                x = x->right;
        }
        return x;
    }

    CNode* GetRoot()
    {
        return Root;
    }
    void DeleteCNode( int n )
    {
        CNode* pointer = Root;
        CNode* parent = nullptr;

        while( ( pointer != nullptr ) && ( pointer->data != n ) ) {
            parent = pointer;
            if( n < ( pointer->data ) ) {
                pointer = pointer->left;
            }
            else {
                pointer = pointer->right;
            }
        }

        if( pointer != nullptr )
        {
            CNode* removed = nullptr;

            if( ( pointer->left == nullptr ) || ( pointer->right == nullptr ) )
            {
                CNode* child = nullptr;
                removed = pointer;

                if( ( pointer->left ) != nullptr )
                    child = pointer->left;
                else
                    if( ( pointer->right ) != nullptr )
                        child = pointer->right;

                if( parent == nullptr )
                    Root = child;
                else
                {
                    if( ( parent->left ) == pointer )
                        parent->left = child;
                    else
                        parent->right = child;
                }
            }
            else
            {
                CNode* lefter = pointer->right;
                CNode* lefterParent = pointer;

                while( ( lefter->left ) != nullptr )
                {
                    lefterParent = lefter;
                    lefter = lefter->left;
                }

                pointer->data = lefter->data;
                removed = lefter;

                if( ( lefterParent->left ) == lefter )
                    lefterParent->left = nullptr;
                else
                    lefterParent->right = lefter->right;
            }
            delete removed;
        }
    }
    // Определение высоты дерева.
    int height( CNode* start ) {
        int result = 0;
        if( start != nullptr ) {
            int l = height( start->left );
            int r = height( start->right );
            if( l > r ) {
                result = l + 1;
            }
            else {
                result = r + 1;
            }
        }
        return result;
    }
    void DeleteTree( CNode* x )
    {
        if( x == nullptr )
            return;
        DeleteTree( x->left );
        DeleteCNode( x->data );
        DeleteTree( x->right );
    }

};

#include <memory>
#include <algorithm>

class CNode {
public:
    // Ключ.
    // Приоритет.
    int x;
    int y;
    CNode* left;
    CNode* right;
    CNode( int _x, int _y, CNode* _left = 0, CNode* _right = 0 ) {
        x = _x;
        y = _y;
        left = _left;
        right = _right;
    }
    ~CNode() {
        if( left != nullptr ) {
            delete left;
        }
        if( right != nullptr ) {
            delete right;
        }
    }
};

class CTreap {

public:
    CNode* root;
    CTreap( int _x, int _y, CNode* _left = 0, CNode*  _right = 0 ) {
        root = new CNode( _x, _y, _left, _right );
    };
    ~CTreap() {
        root->~CNode();
    }
    CNode* getRoot()const {
        return root;
    }
    // Сливает 2 декартовых дерева в одно. Ключи в дереве Lt должны быть меньше чем ключи в Rt.
    CNode* Merge( CNode* left, CNode* right )
    {
        if( left == nullptr || right == nullptr ) {
            return left == nullptr ? right : left;
        }
        if( left->y > right->y ) {
            left->right = Merge( left->right, right );
            return left;
        }
        right->left = Merge( left, right->left );
        return right;
    }
    // Разрезает заданное декартово дерево по ключу.
    void Split( CNode* currentNode, int key, CNode*& left, CNode*& right )
    {
        if( currentNode == nullptr ) {
            left = nullptr;
            right = nullptr;
        }
        else if( currentNode->x <= key ) {
            Split( currentNode->right, key, currentNode->right, right );
            left = currentNode;
        }
        else {
            Split( currentNode->left, key, left, currentNode->left );
            right = currentNode;
        }
    }
    // Вставляет элемент.
    CNode* insert( int key, int priority ) {
        CNode* curNode = this->root;
        CNode* curLeft = this->root->left;
        CNode* curRight = this->root->right;
        CNode* curParent = nullptr;
        bool l = false;
        bool r = false;
        while( curNode != nullptr && curNode->y >= priority ) {
            curParent = curNode;
            l = false;
            r = false;
            if( key < curNode->x ) {
                l = true;
                curNode = curNode->left;
            }
            else {
                r = true;
                curNode = curNode->right;
            }
        }
        Split( curNode, key, curLeft, curRight );
        CNode* newTreap = new CNode( key, priority, curLeft, curRight );
        if( l == true ) {
            curParent->left = newTreap;
        }
        else if( r == true ) {
            curParent->right = newTreap;
        }
        else {
            this->root = newTreap;
        }
        return newTreap;
    }

    int height( CNode* start ) {
        int result = 0;
        if( start != nullptr ) {
            int l = height( start->left );
            int r = height( start->right );
            if( l > r ) {
                result = l + 1;
            }
            else {
                result = r + 1;
            }
        }
        return result;
    }
private:
};

#include <iostream>
using namespace std;

int main() {
    int aaa = 0;
    int bbb = 0;
    int n = 0;
    cin >> n;
    CBSTree bstree;
    if( n == 0 ) {
        cout << 0;
        return 0;
    }
    cin >> aaa;
    bstree.InsertCNode( aaa );
    cin >> bbb;
    CTreap treap( aaa, bbb );
    for( int i = 0; i < n - 1; ++i ) {
        cin >> aaa;
        cin >> bbb;
        bstree.InsertCNode( aaa );
        treap.insert( aaa, bbb );
    }
    //cout << bstree.height(bstree.GetRoot()) << endl;
    //cout << treap.height( treap.getRoot() ) << endl;
    cout << bstree.height( bstree.GetRoot() ) - treap.height( treap.getRoot() ) << endl;
    cin >> n;
    return 0;
}