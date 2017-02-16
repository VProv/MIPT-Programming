#pragma once

class Circle {
    double xmid;
    double ymid;
    double R;
    
public:
    Circle();
    void getCurrentVal();
    void setCircle(double x, double y, double R);
    void move(double x, double y);
    void scale(double k);
};
