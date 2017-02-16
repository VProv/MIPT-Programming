#include "TextEditor.h"

//

void TextEditor::set_symbol(const char& a) {
    if (a == '<') {
        Cursor.go_left(text);
    }
    else if (a == '>') {
        Cursor.go_right(text);
    }
    else if (a == '^') {
        Cursor.go_up(text);
    }
    else if (a == '|') {
        Cursor.go_down(text);
    }
    else if (a == '#') {
        Position k = Cursor;
        k.go_left(text);
        Action* a = new Deletion(k,text.get_symb(k.get_i(),k.get_j()));
        undo.push(a);
        delete_symbol();
    }
    else if (a == '@') {
        cancel();
    }
    else if (a == '$') {
        repeat();
    }
    else if (a == '\n') {
        Action* ac = new Insertion(Cursor, '\n');
        undo.push(ac);
        text.set_symbol(Cursor.get_i(),Cursor.get_j(),a);
        Cursor.go_down(text);
    }
    else {
        Action* ac = new Insertion(Cursor, '\n');
        undo.push(ac);
        text.set_symbol(Cursor.get_i(), Cursor.get_j(), a);
        Cursor.go_right(text);
    }
}

TextEditor::TextEditor(const string& s):text(), Cursor(), undo(), redo() {
    int l = s.size();
    for (int i = 0; i < l; i++) {
        set_symbol(s[i]);
    }
}

void TextEditor::delete_symbol() {
    Cursor.go_left(text);
    text.erase_symb(Cursor.get_i(), Cursor.get_j());
}

Text TextEditor::_Editor(const string& s) {
    int l = s.size();
    for (int i = 0; i < l; i++) {
        set_symbol(s[i]);
    }
    return text;
}


void TextEditor::cancel() {
    Action* ac = undo.pop();
    redo.push(ac);
    ac->undo(text, Cursor);
}
void TextEditor::repeat() {
    Action* ac = redo.pop();
    undo.push(ac);
    ac->redo(text, Cursor);
}