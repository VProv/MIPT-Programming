#pragma once
#include "DynArray.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

class Point;
class Vector;
class Line;
class Segment;
class Polygon;
class Circle;
class base {
public:
    typedef double t;
    virtual base& move(const t x, const t y) = 0;
    //check is this Point in our figure or not
    virtual bool isPoint(const t, const t)const = 0;
    //intersection with Segment, returning depending of common Points: empty if 0, Points if there number <= 2,Array length 3 if infinity
    virtual DynArray<Point> intersection_Segment(const Segment&)const = 0;
    virtual t min(const t a, const t b)const;
    virtual t max(const t a, const t b)const;
};


class Point :public base {
    t x;
    t y;
public:
    Point(t x = 0, t y = 0);
    Point(const Point&);
    t getX()const;
    t getY()const;
    void setX(const t);
    void setY(const t);
    Point& move(const t, const t);
    bool isPoint(const t, const t)const;
    DynArray<Point> intersection_Segment(const Segment& a)const;

    friend t get_orient_area(const Point& a, const Point& b, const Point& c); //returns oriented area of parallelogram on vectors ba and ca    
    friend bool isintersect(const Point a, const Point b, const Point c, const Point d); // is intersect of Segments ab and cd
    friend bool isintersect_1(int a, int b, int c, int d); //supporting function to previous isintersect
    bool belongsTo(const Segment& A)const;

    double get_distance(const Point & p)const; //return distance between two Points
    bool is_Point_in_Angle(const Point&, const Point&, const Point&, const Point&)const;
    friend bool operator == (const Point & a, const Point & b);
    friend class Segment;
    friend class Polygon;
};

class Circle :public base {
    t x;
    t y;
    t R;
public:
    Circle(const t x = 0, const t y = 0, const t R = 0);
    Circle(const Circle&);
    Circle& move(const t x,const  t y);
    bool isPoint(const t, const t)const;
    DynArray<Point> intersection_Segment(const Segment& a)const;// empty if 0, Points if they are, length 3 if circles match
    void setX(const t&);
    void setY(const t&);
    void setR(const t&);
    t getX()const;
    t getY()const;
    t getR()const;

    DynArray<Point> line_intersection(const Line& a)const; // empty if 0, Point if it is, length 3 if march
    DynArray<Point> two_circles_intersection(const Circle & q) const; // empty if 0, Points if they are, length 3 if circles match

};


class Vector {
    typedef double t;
    t x;
    t y;
public:
    Vector(const t x = 0,const t y = 0);
    Vector(const Vector&);
    void setX(const t);
    void setY(const t);
    t getX()const;
    t getY()const;

    Vector(const Point& obj);
    Vector(const Point & p1, const Point & p2);
    void set_values(double x, double y);
    bool isPoint(const Point & p) const;
    double distance(const Point & obj) const; //vector as Segment
    double length() const; // vector length as Segment
    double angle(const Vector & v) const; // angle between vectors
    double operator * (const Vector & v); //as determinant
    double Scal(const Vector & v); // Scalar of two vectors
    Vector& operator = (const Vector & p);
    double get_x() const;
    double get_y() const;
    void set_x(const double x);
    void set_y(const double y);
};

class Segment : public base {
    Point P1;
    Point P2;
public:
    Segment(const t x1 = 0, const  t y1 = 0, const  t x2 = 0, const  t y2 = 0);
    Segment(const Point&, const Point&);
    Segment(const Segment&);

    Segment& move(const t, const t);
    bool isPoint(const t, const t)const;
    DynArray<Point> intersection_Segment(const Segment&)const;
    double length() const;
    Point getP1() const;
    Point getP2() const;
    t getX1() const;
    t getX2() const;
    t getY1() const;
    t getY2() const;
    friend bool operator == (const Segment& a, const Segment& b);
    friend bool rotation(const Segment& a, const Segment& b); //returns oriented area of parallelogram on Segments a,b
    friend t det(const Segment& a, const Segment& b); // determinant
    friend t det(const t a, const t b, const t c, const t d); // determinant ba and dc
    double distance(const Point & p) const;
    friend bool isintersect(const Segment& a, const Segment& b);

    bool belongs_point(const Point & p) const;
};


class Line: public base {
    double a, b, c;
public:
    Line(const Segment& A);
    Line(const Point& P, const Line& L);
    Line(const Line&);
    Line& move(const t, const t);
    bool isPoint(const t, const t)const;
    DynArray<Point> intersection_Segment(const Segment& a)const;
    Point inters(const Line& L); // intersection of two Lines
    double getA() const;
    double getB() const;
    double getC() const;
    friend class Circle;
};

class Polygon: public base {
protected:
    int n;
    DynArray<Point> p;
public:
    Polygon();
    Polygon(int n, Point *a);
    Polygon(const Polygon &m);
    ~Polygon();
    
    Polygon& move(const t, const t);
    bool isPoint(const t, const t)const;
    DynArray<Point> intersection_Segment(const Segment&)const;

    //
    double distance(const Point & p1) const;
    bool include_point(const Point & q) const; // include point or not
    bool convexity();

    Segment getSide(int i) const; // get i Segment of Polygon
    Polygon operator = (const Polygon & m);
    double perimeter()const;
    double square() const; //as area
    void Polygon::convex_hull(std::vector<Point>& a);
};