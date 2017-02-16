#pragma once
#include "Date.h"

struct Task {
    char descr[500];
    Date date;

};

void printTasks(Task* t, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s", t[i].descr);
        putchar('\n');
    }
}