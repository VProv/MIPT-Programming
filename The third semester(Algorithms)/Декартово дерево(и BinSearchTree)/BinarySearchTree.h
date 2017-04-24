#pragma once
// Наивное бинарное дерево поиска.
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