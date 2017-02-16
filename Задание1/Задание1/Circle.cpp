#include "Circle.h"
#include <iostream>

Circle::Circle() {
    this->xmid = 0;
    this->ymid = 0;
    this->R = 0;
}

void Circle::getCurrentVal() {
    std::cout << " xmid: " << this->xmid << std::endl;
    std::cout << " ymid: " << this->ymid << std::endl;
    std::cout << " R: " << this->R << std::endl;
    
}
void Circle::setCircle(double x, double y, double R) {
    this->xmid = x;
    this->ymid = y;
    this->R = R;

    if ((-10000 > xmid - R))
        this->xmid = -10000 + R;        
    if (xmid + R > 10000)
        xmid = 10000 - R;        
    if (-10000 > ymid - R)
        ymid = -10000 + R;
    if (ymid + R > 10000)
        ymid = 10000 - R;
}

void Circle::move(double x, double y) {
    this->xmid += x;
    this->ymid += y;
    if ((-10000 > xmid - R))
        this->xmid = -10000 + R;
    if (xmid + R > 10000)
        xmid = 10000 - R;
    if (-10000 > ymid - R)
        ymid = -10000 + R;
    if (ymid + R > 10000)
        ymid = 10000 - R;
}

void  Circle::scale(double k) {
    if ((-10000 <= this->xmid + R * k) && (this->xmid + R * k <= 10000) && (-10000 <= this->ymid + R * k) && (this->ymid + R * k <= 10000)) {
        this->R = R * k;
    }
    else {
        double min = 0;
            min = 10000 - xmid;
        if (10000 - ymid < min)
            min = 10000 - min;
        if (xmid + 10000 < min)
            min = xmid + 10000;
        if (ymid + 10000 < min)
            min = 10000 + ymid;
        R = min;
    }
}