#include "Date.h"
#include "Task.h"

#ifndef __DATE__
    #define __DATE__
    struct Date {};
#endif

int main() {
    Task tasks[3] = { //сделать конструктор для класса
        { "Go to shop", Date(9,2,2016)}, 
        { "Go to shop", Date(9,2,2016)},
        { "Go to shop", Date(9,2,2016)}
    };
}