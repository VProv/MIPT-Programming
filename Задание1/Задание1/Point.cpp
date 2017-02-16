#include "Point.h"
#include <iostream>
#include <cmath>


Point::Point() {
    this->x = 0;
    this->y = 0;
}

void Point::getCurrentVal() {
    std::cout << "xmid: " << this->x << std::endl;
    std::cout << "ymid: " << this->y << std::endl;
}

void Point::setPoint(double x, double y) {
    this->x = x;
    this->y = y;
    if (x > 10000)
        this->x = 10000;
    if (x < -100000)
        this->x = -10000;
    if (y > 10000)
        this->x = 10000;
    if (y < -100000)
        this->x = -10000;
}

void Point::move(double x, double y) {
        this->x += x;
        this->y += y;
        if (this->x > 10000)
            this->x = 10000;
        if (this->x < -100000)
            this->x = -10000;
        if (this->y > 10000)
            this->x = 10000;
        if (this->y < -100000)
            this->x = -10000;
}
