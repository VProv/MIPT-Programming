#pragma once

namespace static_stack {

    typedef int stype;

    class Stack {
        stype* array;
    public:
        unsigned int sTop; //stack top
        Stack(stype i = 0, int n = 1000);
        void push(stype);
        stype pop();
        stype top();
        bool empty();
        void clear();
        int size();
    };
}