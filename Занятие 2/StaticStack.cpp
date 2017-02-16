#include "StaticStack.h" 

using namespace static_stack;

Stack::Stack(stype i, int n){
    array = new stype[n];
    sTop = 0;
    array[0] = i;
}

void Stack::push(stype elem) {
    sTop++;
    array[sTop] = elem;
}

stype Stack::pop() {
    if (empty() == false) {
        stype temp = array[sTop];
        sTop--;
        return temp;
    }
    else
        return 0;
}

stype Stack::top() {
    if (empty() == false)         
        return array[sTop];
    else
        return 0;
}

bool Stack::empty() {
    if (sTop == -1)
        return true;
    else return
        false;
}

void Stack::clear() {
    sTop = -1;
    delete[] array;
}

int Stack::size() {
    return sTop + 1;
}