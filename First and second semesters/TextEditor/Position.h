#pragma once
#include "Text.h"

using namespace std;

class Position {
    int i;
    int j;
public:
    Position() { i = 0; j = 0; }
    Position(const Position& a) { i = a.i; j = a.j; }
    Position(const int x, const int y) { i = x; j = y; }
    void set_i(const int k) {
        i = k;
    }
    void set_j(const int k) {
        j = k;
    }
    int get_i()const {
        return i;
    }
    int get_j()const {
        return j;
    }
    void go_left(const Text&);
    void go_right(const Text&);
    void go_up(const Text&);
    void go_down(const Text&);
};