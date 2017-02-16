#pragma once
#include <cstdio>

class Date {
    int dd,
        mm,
        yyyy;
    Date getNextDay();

public:
    Date(int dd, int mm, int yyyy);
};

