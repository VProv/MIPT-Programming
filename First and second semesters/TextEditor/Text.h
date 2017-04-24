#pragma once
#include <vector>
#include <string>
using namespace std;

class Text {
    vector<string> text;
public:
    Text():text(100) {}
    Text(const Text& t):text(t.text) {}
    Text(const vector<string> t):text(t) {}
    void set_symbol(const int i, const int j, const char c);
    void erase_symb(const int i, const int j);
    void set_text(const vector<string> t) { 
        text = t; 
    }
    vector<string> get_text()const {
        return text;
    }
    const vector<string>& get_text_for_reading()const {
        return text;
    }
    int get_rows_num()const {
        return text.size();
    }
    int get_row_length(const int i)const {
        return text[i].size();
    }
    char get_symb(const int i, const int j)const {
        if (i < text.size() && j < text[i].size())
            return text[i][j];
    }
};