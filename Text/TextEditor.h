#pragma once
#include "Text.h"
#include "Position.h"
#include "Actions.h"

using namespace std;

class TextEditor {
    Text text;
    Position Cursor;
    Undo undo;
    Redo redo;
public:
    TextEditor():text(),Cursor(),undo(),redo() {}
    TextEditor(const Text& t, const Position& p):text(t),Cursor(p),undo(),redo() {}
    TextEditor(const string& s);
    Text _Editor(const string& s);
    void set_symbol(const char& a);
    void delete_symbol();
    vector<string> get_text()const {
        return text.get_text();
    }
    const vector<string>& get_text_for_reading()const {
        return text.get_text_for_reading();
    }
    void cancel();
    void repeat();
};



