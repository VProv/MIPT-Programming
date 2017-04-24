#pragma once

namespace dynamic_stack {

    typedef int stype;

    class Stack {
        struct Node {
            Node* prev;
            stype s;
        };
        int Ssize;
    public:
        Node* sTop; //stack top
        Stack(stype i = 0, Node* prev = nullptr);
        void push(stype);
        stype pop();
        stype top();
        bool empty();
        void clear();
        int size();
    };

}