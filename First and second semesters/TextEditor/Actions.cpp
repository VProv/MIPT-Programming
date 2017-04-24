#include "Actions.h"

void Insertion::undo(Text& t, Position& p) {
    p = Cursor;
    t.erase_symb(p.get_i(), p.get_j());
}

void Insertion::redo(Text& t, Position& p) {
    p = Cursor;
    t.set_symbol(p.get_i(), p.get_j(), symb);
}

void Deletion::undo(Text& t, Position& p) {
    t.set_symbol(Cursor.get_i(), Cursor.get_j(), symb);
    p = Cursor;
    p.go_right(t);
}

void Deletion::redo(Text& t, Position& p) {
    p.go_left(t);
    t.erase_symb(p.get_i(), p.get_j());
}


//
void Undo::push(Action* a) {
    d.push_back(a);
    if (d.size() > Undo::memory_number) {
        delete d.front();
        d.pop_front();
    }
}

Action* Undo::pop() {
    Action* a = d.back();
    d.pop_back();
    return a;
}

void Redo::push(Action* a) {
    d.push_back(a);
    if (d.size() > Redo::memory_number) {
        delete d.front();
        d.pop_front();
    }
}

Action* Redo::pop() {
    Action* a = d.back();
    d.pop_back();
    return a;
}

Undo::~Undo() {
    for (deque<Action*>::iterator it = d.begin(); it != d.end(); it++)
        delete *it;
}

Redo::~Redo() {
    for (deque<Action*>::iterator it = d.begin(); it != d.end(); it++)
        delete *it;
}
