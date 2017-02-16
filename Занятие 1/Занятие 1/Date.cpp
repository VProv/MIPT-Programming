#include "Date.h"
#include <cstdio>

Date Date::getNextDay() {
    Date nextDay = *this;
    nextDay.dd++;
    return nextDay;
}

Date:: Date(int dd, int mm, int yyyy) {
        this->dd = dd;
        this->mm = mm;
        this->yyyy = yyyy;
    }