#include "Text.h"

void Text::set_symbol(const int i, const int j, const char c) {
    if (i == text.capacity() - 1 || text.capacity() == 0) {
        string s;
        s += c;
        text.push_back(s);
        return;
    }
    else if (j == text[i].capacity() || text[i].capacity() == 0)
        text[i].push_back(c);
    else
        text[i].insert(j, 1, c);
}

void Text::erase_symb(const int i, const int j) {
        text[i].erase(j, 1);
}