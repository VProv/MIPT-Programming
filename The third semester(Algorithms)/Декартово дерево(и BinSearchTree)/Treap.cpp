#include "Treap.h"

CNode* CTreap::Merge( CNode* left, CNode* right )
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

void CTreap::Split( CNode* currentNode, int key, CNode*& left, CNode*& right )
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

CNode* CTreap::insert( int key, int priority ) {
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

int CTreap::height( CNode* start ) {
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