#pragma once
#include <iostream>

class Point {
    double x;
    double y;
    
public:
    Point();
    void getCurrentVal();
    void setPoint(double x, double y);
    void move(double x, double y);
};
