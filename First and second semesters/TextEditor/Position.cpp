#include "Position.h"


using namespace std;

void Position::go_left(const Text& a) {
    if (i == 0 && j == 0)
        return;
    else if (j == 0) {
        i--;
        j = a.get_row_length(i);
    }
    else {
        j--;
    }
}

void Position::go_right(const Text& a) {
    if (j == a.get_row_length(i)) {
        if (i == a.get_rows_num() - 1) {
            return;
        }
        else {
            i++;
            j = 0;
        }
    }
    else {
        j++;
    }
}

void Position::go_up(const Text& t) {
    if (i == 0)
        return;
    else {
        i--;
        if (j > t.get_row_length(i))
            j = t.get_row_length(i);
    }
}

void Position::go_down(const Text& t) {
    if (i == t.get_rows_num() - 1) {
        if (t.get_symb(i, t.get_row_length(i) - 1) == '\n') {
            i++;
            j = 0;
            return;
        }
        else
            return;
    }
    i++;
    if (j > t.get_row_length(i))
        j = t.get_row_length(i);
}


