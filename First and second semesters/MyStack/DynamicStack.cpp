#include "DynamicStack.h"

using namespace dynamic_stack;

Stack::Stack(stype i, Node* prev) {
    sTop = prev;
    push(i);
}

void Stack::push(stype elem) {
    if (sTop == nullptr) {
        sTop = new Node;
        sTop->prev = nullptr;
        (sTop)->s = elem;
        Ssize++;
    }
    else if ((sTop) != nullptr) {
        Node * temp = sTop;
        sTop = new Node;
        (sTop)->prev = temp;
        (sTop)->s = elem;
        Ssize++;
    }
}

stype Stack::pop() {
    Node* temp = sTop->prev;
    stype val = sTop->s;
    delete(sTop);
    sTop = temp;
    Ssize--;
    return val;
}

bool Stack::empty() {
    if (sTop->prev == nullptr)
        return true;
    else
        return false;
}

stype Stack::top() {
    stype top = sTop->s;
    return top;
}

void Stack::clear() {
    Node* temp;
    while (sTop != nullptr) {
        temp = sTop->prev;
        delete sTop;
        sTop = temp;
    }
    Ssize = 0;
}

int Stack::size() {
    return Ssize;
}