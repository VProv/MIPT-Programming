#pragma once
#include <deque>
#include "Position.h"
#include "Text.h"

class Action {
protected:
    char symb; 
    Position Cursor;
public:
    virtual void undo(Text& t, Position& p) = 0;
    virtual void redo(Text& t, Position& p) = 0;
    Action() : Cursor() { symb = '0'; }
};

class Insertion :public Action {
public:
    Insertion(const Position& c,const char s) {
        Cursor = c;
        symb = s;
    }
    virtual void undo(Text& t, Position& p);
    virtual void redo(Text& t, Position& p);
};

class Deletion :public Action {
public:
    Deletion(const Position& p, const char si) {
        Cursor = p; 
        symb = si;
    }
    virtual void undo(Text& t, Position& p);
    virtual void redo(Text& t, Position& p);
};


class Undo {
    const static int memory_number = 20;
    deque<Action*> d;
public:
    Undo() :d(memory_number + 2) {}
    ~Undo();
    void push(Action* a);
    Action* pop();
};

class Redo {
    const static int memory_number = 20;
    deque<Action*> d;
public:
    Redo() :d(memory_number + 2) {}
    ~Redo();
    void push(Action* a);
    Action* pop();
};