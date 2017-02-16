#pragma once

class Square {
    double xmid;
    double ymid;
    double side;

public:
    Square();
    void getCurrentVal();
    void setSquare(double x, double y, double side);
    void move(double x, double y);
    void scale(double k);
};

