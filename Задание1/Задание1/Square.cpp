#include "Square.h"
#include <iostream>
#include <cmath>

Square:: Square() {
    this->xmid = 0;
    this->ymid = 0;
    this->side = 0;
}

void Square::getCurrentVal() {
    std::cout << " xmid: " << this->xmid << std::endl;
    std::cout << " ymid: " << this->ymid << std::endl;
    std::cout << " side: " << this->side << std::endl;
}

void Square::setSquare(double x, double y, double side) {
    if ((-10000 <= x - side / 2) && (x + side / 2 <= 10000) && (-10000 <= y - side / 2) && (y + side / 2 <= 10000)) {
        this->xmid = x;
        this->ymid = y;
        this->side = side;
    }
}

void Square::move(double x, double y) {
    this->xmid += x;
    this->ymid += y;
    if (this->xmid > 10000)
        this->xmid = 10000;
    if (this->xmid < -100000)
        this->xmid = -10000;
    if (this->ymid > 10000)
        this->xmid = 10000;
    if (this->ymid < -100000)
        this->xmid = -10000;
}

void  Square::scale(double k) {
    if (abs(this->xmid) + abs(this->side * k / 2) <= 10000 && abs(this->ymid) + abs(this->side * k / 2) <= 10000) {
        this->side = side * k;
    }
}