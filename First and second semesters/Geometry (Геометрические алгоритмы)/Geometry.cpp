#include "Geometry.h"

void Point::setX(const t a) {
    x = a;
}
void Point::setY(const t a) {
    y = a;
}

int max(int a, int b) {
    if (a >= b)
        return a;
    else
        return b;
}

int min(int a, int b) {
    if (a <= b)
        return a;
    else
        return b;
}
void swap(int& a, int& b) {
    int t = b;
    b = a;
    a = t;

}

bool isintersect_1(int a,int b, int c, int d) {
    if (a > b)  swap(a, b);
    if (c > d)  swap(c, d);
    return max(a, c) <= min(b, d);
}

bool isintersect(const Point a, const Point b, const Point c, const Point d) {
    return isintersect_1(a.x, b.x, c.x, d.x)
        && isintersect_1(a.y, b.y, c.y, d.y)
        && get_orient_area(a, b, c) * get_orient_area(a, b, d) <= 0 && get_orient_area(c, d, a) * get_orient_area(c, d, b) <= 0;
}

bool isintersect(const Segment& a, const Segment& b) {
    return isintersect(a.P1, a.P2, b.P1, b.P2);
}

base::t base::min(const t a, const t b)const {
    if (a <= b)
        return a;
    else
        return b;
}
base::t base::max(const t a, const t b)const {
    if (a >= b)
        return a;
    else return b;
}

Point::Point(t ix, t iy) {
    x = ix;
    y = iy;
}

Point::t Point::getX()const {
    return x;
}
Point::t Point::getY()const {
    return y;
}

Point& Point::move(const t vectX, const t vectY) {
    x += vectX;
    y += vectY;
    return (*this);
}

bool Point::isPoint(const t poiX, const t poiY)const {
    if (x == poiX && y == poiY)
        return true;
    else
        return false;
}


/*DynArray<Point> Point::isSegment(const Segment&)const {

}*/


Circle::Circle(const t ix, const t iy, const t iR) {
    x = ix;
    y = iy;
    R = iR;
}

Segment::t Segment::getX1()const {
    return P1.getX();
}
Segment::t Segment::getX2()const {
    return P2.getX();
}
Segment::t Segment::getY1()const {
    return P1.getY();
}
Segment::t Segment::getY2()const {
    return P2.getY();
}

Segment::Segment(const t ix1, const  t iy1, const  t ix2, const  t iy2) {
    P1.setX(ix1);
    P2.setX(ix2);
    P1.setY(iy1);
    P2.setY(iy2);
}

Segment::Segment(const Point& a, const Point& b) {
    P1.setX(a.getX());
    P1.setY(a.getY());
    P2.setX(b.getX());
    P2.setY(b.getY());
}

Segment& Segment::move(t x, t y) {
    P1.x += x;
    P2.x += x;
    P1.y += y;
    P2.y += y;
    return (*this);
}

bool Segment::isPoint(const t x, const t y)const {
    t x1 = P1.x;
    t x2 = P2.x;
    t y1 = P1.y;
    t y2 = P2.y;

    if (x >= min(x1, x2) && x <= max(x1, x2) && y >= min(y1, y2) && y <= max(y1, y2)) {
        if (y == (y2 - y1) / (x2 - x1) * x)
            return true;
        else
            return false;
    }
    else
        return false;
}

bool rotation(const Segment& a, const Segment& b) {

    if (((a.getX2() - a.getX1()) * (b.getY2() - b.getY1()) - (a.getY2() - a.getY1()) * (b.getX2() - b.getX1())) >= 0)
        return true;
    else
        return false;
}

Segment::t det(const Segment& a, const Segment& b) {
    return (a.getX2() - a.getX1()) * (b.getY2() - b.getY1()) - (a.getY2() - a.getY1()) * (b.getX2() - b.getX1());
}

bool operator == (const Segment& a, const Segment& b) {
    if (a.getX1() == b.getX1() && a.getX2() == b.getX2() && a.getY1() == b.getY1() && a.getY2() == b.getY2())
        return true;
    else return false;
}

Point::t get_orient_area(const Point&  a, const Point&  b, const Point&  c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

Line::Line(const Point& P, const Line& L) {
    if (L.a != 0 && L.b != 0) {
        this->a = L.b;
        this->b = -L.a;
        this->c = 0 - P.getY() * this->b - this->a * P.getX();
    }
    else
        if (L.b == 0 && L.a != 0) {
            this->a = 0;
            this->b = 1;
            this->c = 0 - P.getY();
        }
        else
            if (L.a == 0 && L.b != 0) {
                this->b = 0;
                this->a = 1;
                this->c = 0 - P.getX();
            }
}


Point Line::inters(const Line& L) {
    Point p;
    if (L.a != 0 && L.b != 0 && this->a != 0 && this->b != 0)
    {
        p.setX((L.c / L.b - this->c / this->b) / (this->a / this->b - L.a / L.b));
        p.setY((-L.a / L.b) * p.getX() - L.c / L.b);
    }
    else
        if (L.a == 0 && L.b != 0 && this->a != 0 && this->b == 0)
        {
            p.setX(-this->c);
            p.setY(-L.c);
        }
        else
            if (L.a != 0 && L.b == 0 && this->a == 0 && this->b != 0)
            {
                p.setX(-L.c);
                p.setY(-this->c);
            }
    return p;
}

Line::Line(const Segment& A) {
    if (A.getX1() == 0 && A.getY1() == 0) {
        a = A.getY2();
        b = -A.getX2();
        c = 0;
    }
    else {
        a = A.getY1() - A.getY2();
        b = -A.getX1() + A.getX2();
        c = -A.getX2() * this->a - A.getY2() * this->b;
    }
}

bool Point::is_Point_in_Angle(const Point& pA, const Point& pO, const Point& pB, const Point& pP)const {
    Segment A(pO.x, pO.y, pA.x, pA.y);
    Segment B(pO.x, pO.y, pB.x, pB.y);
    Segment P(pO.x, pO.y, pP.x, pP.y);
    bool k = rotation(B, A);
    if (A == P || B == P || (pP.x == pO.x && pP.y == pO.y) || ((det(B, P) == 0 && rotation(A, B) == rotation(A, P)) || det(A, P) == 0 && rotation(B, P) == rotation(B, A)))
       return true;
    else if (rotation(B, P) == k && (rotation(A, P) == !k))
        return true;
    else
        return true;
}

bool  Point::belongsTo(const Segment& A)const
{
    if (A.getX1() != A.getX2())
        if (A.getX1() < A.getX2())
            if (x <= A.getX2() && x >= A.getX1())
                return 1;
            else
                return 0;
        else
            if (x >= A.getX2() && x <= A.getX1())
                return 1;
            else
                return 0;
    else
        if (A.getY1() <= A.getY2())
            if (y >= A.getY1() && y <= A.getY2())
                return 1;
            else
                return 0;
        else
            if (y <= A.getY1() && y >= A.getY2())
                return 1;
            else
                return 0;
}

double distancee(const Point& P, const Segment& A, const Line& L) {
    double result;
    double r1, r2;
    r1 = sqrt((P.getX() - A.getX1()) * (P.getX() - A.getX1()) + (P.getY() - A.getY1()) * (P.getY() - A.getY1())),
        r2 = sqrt((P.getX() - A.getX2()) * (P.getX() - A.getX2()) + (P.getY() - A.getY2()) * (P.getY() - A.getY2()));
    if (L.getA() * L.getA() + L.getB() * L.getB() == 0)
        result = r1;
    else {
        double r;
        r = fabs(L.getA() * P.getX() + L.getB() * P.getY() + L.getC()) / sqrt(L.getA() * L.getA() + L.getB() * L.getB());
        if (r == 0)
            if (P.belongsTo(A))
                result = 0;
            else
                if (r1 < r2)
                    result = r1;
                else
                    result = r2;
        else {
            Line L1(P, L);
            if ((L1.inters(L)).belongsTo(A))
                result = r;
            else
                if (r1 < r2)
                    result = r1;
                else
                    result = r2;
        }
    }
    return result;
}

void CircleLineInter(double x1, double y1, double r, double a, double b, double c) {
    c = c + a * x1 + b * y1;

    double EPS = 0.01;
    double x0 = -a*c / (a*a + b*b), y0 = -b*c / (a*a + b*b);
    if (c*c > r*r*(a*a + b*b) + EPS)
        std::cout << 0;
    else if (abs(c*c - r*r*(a*a + b*b)) < EPS) {
        std::cout << 1 << std::endl;
        x0 = x0 + x1;
        y0 = y0 + y1;
        std::cout << x0 << ' ' << y0 << std::endl;
    }
    else {
        double d = r*r - c*c / (a*a + b*b);
        double mult = sqrt(d / (a*a + b*b));
        double ax, ay, bx, by;
        ax = x0 + b * mult + x1;
        bx = x0 - b * mult + x1;
        ay = y0 - a * mult + y1;
        by = y0 + a * mult + y1;
        std::cout << 2 << std::endl;
        std::cout << ax << ' ' << ay << std::endl;
        std::cout << bx << ' ' << by << std::endl;
    }
}

void Circle::setX(const t& a) {
    x = a;
}
void Circle::setY(const t& a) {
    y = a;
}
void Circle::setR(const t& a) {
    R = a;
}

Circle::t Circle::getX()const {
    return x;
}
Circle::t Circle::getY()const {
    return y;
}
Circle::t Circle::getR()const {
    return R;
}

bool Circle::isPoint(const t a, const t b)const {
    double EPS = 0.00001;
    if (sqrt((x - a)* (x - a) + (y - b) * (y - b)) < (R + EPS) && sqrt((x - a)* (x - a) + (y - b) * (y - b)) > (R - EPS))
        return true;
    else
        return false;
}

DynArray<Point> Point::intersection_Segment(const Segment& a)const {
    Point P(x, y);
    Segment A(a.getX1(), a.getY1(), a.getX2(), a.getY2());
    Line L(A);
    DynArray<Point> p;
    double result;
    result = distancee(P, A, L);
    if (result == 0) {
        p.push_back(P);
        return p;
    }
    else 
        return p;
}

Point::Point(const Point& a) {
    x = a.x;
    y = a.y;
}

Circle::Circle(const Circle& a) {
    x = a.x;
    y = a.y;
    R = a.R;
}


Circle& Circle::move(const t ix,const  t iy) {
    x += ix;
    y += iy;
    return (*this);
}

double Line::getA() const {
    return a;
}
double Line::getB() const {
    return b;
}
double Line::getC() const {
    return c;
}

/*
DynArray<Point>& Circle::isSegment(const Line& Li) {
    t c = Li.getC();
    t a = Li.getA();
    t b = Li.getB(),r = R;
    t x1 = x;
    t y1 = y;
    c = c + a * x1 + b * y1;
    DynArray<Point> dp;
    double EPS = 0.01;
    double x0 = -a*c / (a*a + b*b), y0 = -b*c / (a*a + b*b);
    if (c*c > r*r*(a*a + b*b) + EPS) {
        Point p(0, 0);
    }
    else if (abs(c*c - r*r*(a*a + b*b)) < EPS) {
        x0 = x0 + x1;
        y0 = y0 + y1;
        Point p(x0, y0);
        dp.push_back(p);
    }
    else {
        double d = r*r - c*c / (a*a + b*b);
        double mult = sqrt(d / (a*a + b*b));
        double ax, ay, bx, by;
        ax = x0 + b * mult + x1;
        bx = x0 - b * mult + x1;
        ay = y0 - a * mult + y1;
        by = y0 + a * mult + y1;
        Point p(ax, ay);
        Point p2(bx, by);
        dp.push_back(p);
        dp.push_back(p2);
    }
    return dp;
}
*/


Vector::Vector(const t ix, const t iy) {
    x = ix;
    y = iy;
}
Vector::Vector(const Vector& a) {
    x = a.x;
    y = a.y;
}

void Vector::setX(const t a) {
    x = a;
}
void Vector::setY(const t a) {

}
Vector::t Vector::getX()const {
    return x;
}
Vector::t Vector::getY()const {
    return y;
}

Segment::Segment(const Segment& a) {
    P1.setX(a.getX1());
    P2.setX(a.getX2());
    P1.setY(a.getY1());
    P2.setY(a.getY2());
}

Line::Line(const Line& d) {
    a = d.a;
    b = d.b;
    c = d.c;
}


double Point::get_distance(const Point & p)const {
    return sqrt((this->x - p.x)*(this->x - p.x) + (this->y - p.y)*(this->y - p.y));
}

bool operator == (const Point & a, const Point & b) {
    return (a.x == b.x && a.y == b.y);
}

DynArray<Point> Circle::two_circles_intersection(const Circle & q) const {
    Point c(x, y);
    Point qc(q.x, q.y);
    if (c == qc) {
        if (this->R == q.R) {
            DynArray<Point> K;
            Point J1(0, 0);
            Point J2(0, 1);
            Point J3(1, 0);
            K.push_back(J1);
            K.push_back(J2);
            K.push_back(J3);
            return K;
        }
        else {
            DynArray<Point> K;
            return K;
        }
            
    }
    else {
        Circle _c2(qc.getX() - c.getX(), qc.getY() - c.getY(), q.R);
        Point _c2c(_c2.x, _c2.y);
        double A = -2 * _c2c.getX(),
            B = -2 * _c2c.getY(),
            C = _c2c.getX() * _c2c.getX() + _c2c.getY() * _c2c.getY() + R * R - _c2.R * _c2.R;
        double x0 = -A * C / (A * A + B * B),
            y0 = -B * C / (A * A + B * B);
        if (C * C > R * R * (A * A + B * B) + 0.0001) {
            DynArray<Point> K;
            return K;
        }
        else {
            if (abs(C * C - R * R * (A * A + B * B)) < 0.0001) {
                DynArray<Point> K;
                Point P(x0 + c.getX(), y0 + c.getY());
                K.push_back(P);
                return K;
            }
            else {
                double d = R * R - C * C / (A * A + B * B);
                double mult = sqrt(d / (A * A + B * B));
                double ax, ay, bx, by;
                ax = x0 + B * mult;
                bx = x0 - B * mult;
                ay = y0 - A * mult;
                by = y0 + A * mult;
                DynArray<Point> K;
                Point P1(ax + c.getX(), ay + c.getY());
                Point P2(bx + c.getX(), by + c.getY());
                K.push_back(P1);
                K.push_back(P2);
                return K;
            }
        }
    }
}


double Segment::distance(const Point & p) const {
    Point p1(P1);
    Point p2(P2);
    Point copy_1(p2.getX() - p1.getX(), p2.getY() - p1.getY());
    Vector v1(copy_1);
    Point copy_2(p.getX() - p1.getX(), p.getY() - p1.getY());
    Vector v2(copy_2);
    double alfa = v1.angle(v2), dist = 0;
    double c = p1.get_distance(p2),
        a = p1.get_distance(p),
        b = p2.get_distance(p);
    if ((a * a + c * c - b * b) * (b * b + c * c - a * a) > 0) {
        dist = abs(a * sqrt(1 - cos(alfa)*cos(alfa)));
        if (dist < 0.000001)
            dist = 0;
    }
    else {
        Point p1(P1);
        Point p2(P2);
        dist = min(p1.get_distance(p), p2.get_distance(p));
    }
    return dist;
}

bool Segment::belongs_point(const Point & p) const {
    Point p1(P1);
    Point p2(P2);
    Vector a(p1.getX() - p.getX(), p1.getY() - p.getY()),
        b(p2.getX() - p.getX(), p2.getY() - p.getY());
    if (a * b == 0 && a.Scal(b) <= 0)
        return true;
    else
        return false;
}

Vector::Vector(const Point& obj) {
    this->x = obj.getX();
    this->y = obj.getY();
}

Vector::Vector(const Point & p1, const Point & p2) {
    this->x = p2.getX() - p1.getX();
    this->y = p2.getY() - p1.getY();
}

void Vector::set_values(double x, double y) {
    this->x = x;
    this->y = y;
}

bool Vector::isPoint(const Point & p) const {
    return ((this->y / this->x == p.getX() / p.getY()) && this->x >= p.getX() && this->y >= p.getY());
}

double Vector::distance(const Point & obj) const {
    Vector v(obj);
    double l = v.length();
    double alfa = this->angle(v);
    return l * sin(alfa);
}

double Vector::length() const {
    return sqrt(this->x * this->x + this->y * this->y);
}

double Vector::angle(const Vector & v) const {
    double c;
    if (length() == 0 || v.length() == 0)
        return 0;
    c = (this->x * v.x + this->y * v.y) / (this->length() * v.length());
    return acos(c);
}

double Vector::operator * (const Vector & v) {
    return (this->x * v.y - this->y * v.x);
}

double Vector::Scal(const Vector & v) {
    return (this->x * v.x + this->y * v.y);
}

Vector& Vector::operator = (const Vector & p) {
    this->x = p.x;
    this->y = p.y;
    return *this;
}

double Vector::get_x() const {
    return this->x;
}

double Vector::get_y() const {
    return this->y;
}

void Vector::set_x(const double x) {
    this->x = x;
}

void Vector::set_y(const double y) {
    this->y = y;
}

Polygon::Polygon() {
    this->n = 0;
}
Polygon::Polygon(int n, Point *a): p(a,n) {
    this->n = n;
    for (int i = 0; i < n; i++)
        this->p[i] = a[i];
}

Polygon::Polygon(const Polygon &m): p(m.p) {
    this->n = m.n;
    for (int i = 0; i < m.n; ++i)
        this->p[i] = m.p[i];
}

Polygon::~Polygon() {
    
}


double Polygon::distance(const Point & p1) const {
    double *dist = new double[n];
    for (int i = 0; i < n; i++) {
        Point p1(p[i].getX(), p[i].getY()),
            p2(p[(i + 1) % n].getX(), p[(i + 1) % n].getY());
        Segment s(p1, p2);
        dist[i] = s.distance(p1);
    }
    double min = dist[0];
    for (int i = 1; i < n; i++)
        if (dist[i] < min)
            min = dist[i];
    delete[]dist;
    return min;
}

bool Polygon::convexity() {
    if (n == 3)
        return true;
    bool res = true;
    for (int i = 0; i < n && res; i++) {
        Point p1(p[(i + 1) % n].getX() - p[i].getX(), p[(i + 1) % n].getY() - p[i].getY());
        Point p2(p[(i + 2) % n].getX() - p[i].getX(), p[(i + 2) % n].getY() - p[i].getY());
        Vector v1(p1), v2(p2);
        double v2_v1 = v2 * v1;
        for (int j = (i + 3) % n;; j++) {
            Point p3(p[j % n].getX() - p[i].getX(), p[j % n].getY() - p[i].getY());
            Vector v3(p3);
            double v3_v1 = v3 * v1;
            if (v2_v1 * v3_v1 <= 0)
                res = false;
            if ((j + 1) % n == i)
                break;
        }
    }
    return res;
}


Segment Polygon::getSide(int i) const {
    int j;
    if (i != n - 1)
        j = i + 1;
    else
        j = 0;
    Segment side(p[i], p[j]);
    return side;
}

Polygon Polygon::operator = (const Polygon & m) {
    if (this != &m) {
        //
        Polygon c(m);
        return c;
    }
    return *this;
}


bool Polygon::include_point(const Point & q) const {
    if (include_point(q))
        return true;
    else {
        double p_angle = 0;
        for (int i = 0; i < n; i++) {
            Point p1(q.getX() - p[i].getX(), q.getY() - p[i].getY());
            Point p2(q.getX() - p[(i + 1) % n].getX(), q.getY() - p[(i + 1) % n].getY());
            Vector v1(p1), v2(p2);
            double angle = v1.angle(v2);
            double sign;
            if (v1 * v2 >= 0)
                sign = 1;
            else
                sign = -1;
            p_angle += angle * sign;
        }

        if (abs(p_angle) < 0.0001)
            return false;
        else
            return true;
    }
}

double Segment::length() const {
    return sqrt((P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y));
}

double Polygon::perimeter()const {
    double P = 0;
    for (int i = 0; i < n; ++i)
        P += getSide(i).length();
    return P;
}

double Polygon::square() const {
    for (int i = 1; i < n; i++) {
        p[i].setX(p[i].getX() - p[0].getX());
        p[i].setY(p[i].getY() - p[0].getY());
    }
    p[0].setX(0);
    p[0].setY(0);
    Vector s1(p[1]), s2(p[2]);
    double S = 0.5 * (s1.length() * s2.length() * (sin(s1.angle(s2))));
    for (int i = 3; i < n; ++i) {
        s1 = s2;
        s2.set_x(p[i].getX());
        s2.set_y(p[i].getY());
        S += 0.5 * (s1.length() * s2.length() * (sin(s1.angle(s2))));
    }
    return S;
}

class Cmp {
public:
    bool operator () (Point a, Point b) {
        return a.getX() < b.getX() || a.getX() == b.getX() && a.getY() < b.getY();
    }
};


bool cmp(Point a, Point b) {
    return a.getX() < b.getX() || a.getX() == b.getX() && a.getY() < b.getY();
}


bool cw(const Point& a, const Point& b, const Point& c) {
    return a.getX()*(b.getY() - c.getY()) + b.getX()*(c.getY() - a.getY()) + c.getX()*(a.getY() - b.getY()) < 0;
}

bool ccw(const Point& a, const Point& b, const Point& c) {
    return a.getX()*(b.getY() - c.getY()) + b.getX()*(c.getY() - a.getY()) + c.getX()*(a.getY() - b.getY()) > 0;
}

#include <algorithm>

void Polygon::convex_hull(std::vector<Point>& a) {
    if (a.size() == 1)  return;

    sort(a.begin(), a.end(), Cmp());
    Point p1 = a[0], p2 = a.back();
    std::vector<Point> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (size_t i = 1; i < a.size(); ++i) {
        if (i == a.size() - 1 || cw(p1, a[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
            while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }
    a.clear();
    for (size_t i = 0; i < up.size(); ++i)
        a.push_back(up[i]);
    for (size_t i = down.size() - 2; i > 0; --i)
        a.push_back(down[i]);
}



bool between(double a, double b, double c) {
    double EPS = 0.0001;
    return min(a, b) <= c + EPS && c <= max(a, b) + EPS;
}

Segment::t det(const Segment::t a, const Segment::t b, const Segment::t c, const Segment::t d) {
    return a * d - b * c;
}

DynArray<Point> Segment::intersection_Segment(const Segment& at)const {
    Point a(P1), b(P2), c(at.P1), d(at.P2);
    t A1 = a.y - b.y, B1 = b.x - a.x, C1 = -A1*a.x - B1*a.y;
    t A2 = c.y - d.y, B2 = d.x - c.x, C2 = -A2*c.x - B2*c.y;
    t zn = det(A1, B1, A2, B2);
    if (zn != 0) {
        double x = -det(C1, B1, C2, B2) * 1. / zn;
        double y = -det(A1, C1, A2, C2) * 1. / zn;
        DynArray<Point> K;
        if (between(a.x, b.x, x) && between(a.y, b.y, y) && between(c.x, d.x, x) && between(c.y, d.y, y) == true) {
            Point Ki(x, y);
            K.push_back(Ki);
            return K;
        }
        else {
            return K;
        }
    }
    else {
        if (det(A1, C1, A2, C2) == 0 && det(B1, C1, B2, C2) == 0
            && isintersect_1(a.x, b.x, c.x, d.x) && isintersect_1(a.y, b.y, c.y, d.y) == true) {
            Point J1(0, 0);
            Point J2(0, 1);
            Point J3(1, 0);
            DynArray<Point> K;
            K.push_back(J1);
            K.push_back(J2);
            K.push_back(J3);
            return K;
        }
        else {
            DynArray<Point> K;
            return K;
        }
    }
}

DynArray<Point> Circle::line_intersection(const Line& L)const {
    double a, b, c;
    a = L.a;
    b = L.b;
    c = L.c;
    //transfer circle mid to (0,0)
    c = c + a * x + b * y;

    double EPS = 0.01;
    double x0 = -a*c / (a*a + b*b), y0 = -b*c / (a*a + b*b);
    if (c*c > R*R*(a*a + b*b) + EPS) {
        DynArray<Point> K;
        return K;
    }
        
    else if (abs(c*c - R*R*(a*a + b*b)) < EPS) {
        x0 = x0 + x;
        y0 = y0 + y;
        Point P(x0, y0);
        DynArray<Point> K;
        K.push_back(P);
        return K;
    }
    else {
        double d = R*R - c*c / (a*a + b*b);
        double mult = sqrt(d / (a*a + b*b));
        double ax, ay, bx, by;
        ax = x0 + b * mult + x;
        bx = x0 - b * mult + x;
        ay = y0 - a * mult + y;
        by = y0 + a * mult + y;
        Point P1(ax, ay);
        Point P2(bx, by);
        DynArray<Point> K;
        K.push_back(P1);
        K.push_back(P2);
        return K;
    }
}

DynArray<Point> Circle::intersection_Segment(const Segment& S)const {
    Line L(S);
    double a, b, c;
    a = L.a;
    b = L.b;
    c = L.c;
    //transfer circle mid to (0,0)
    c = c + a * x + b * y;

    double EPS = 0.01;
    double x0 = -a*c / (a*a + b*b), y0 = -b*c / (a*a + b*b);
    if (c*c > R*R*(a*a + b*b) + EPS) {
        DynArray<Point> K;
        return K;
    }

    else if (abs(c*c - R*R*(a*a + b*b)) < EPS) {
        x0 = x0 + x;
        y0 = y0 + y;
        Point P(x0, y0);
        DynArray<Point> K;
        if (S.isPoint(P.getX(),P.getY()))
            K.push_back(P);
        return K;
    }
    else {
        double d = R*R - c*c / (a*a + b*b);
        double mult = sqrt(d / (a*a + b*b));
        double ax, ay, bx, by;
        ax = x0 + b * mult + x;
        bx = x0 - b * mult + x;
        ay = y0 - a * mult + y;
        by = y0 + a * mult + y;
        Point P1(ax, ay);
        Point P2(bx, by);
        DynArray<Point> K;
        if (S.isPoint(P1.getX(), P1.getY()))
            K.push_back(P1);
        if (S.isPoint(P2.getX(), P2.getY()))
            K.push_back(P2);
        return K;
    }
}


Point Segment::getP1() const {
    return P1;
}
Point Segment::getP2() const {
    return P2;
}

Line& Line::move(const t x, const t y) {
    c = c - y + x;
    return (*this);
}

bool Line::isPoint(const t x, const t y)const {
    if (a * x + b * y + c == 0)
        return true;
    else
        return false;
}

DynArray<Point> Line::intersection_Segment(const Segment& Se)const {
    Point P1 = Se.getP1();
    Point P2 = Se.getP2();
    double x1 = P1.getX();
    double y1 = (-c - a * x1) / b;
    double x2 = P2.getX();
    double y2 = (-c - a * x2) / b;
    Point P3(x1, y1);
    Point P4(x2, y2);
    Segment A(P3, P4);
    return Se.intersection_Segment(A);
}

Polygon& Polygon::move(const t xi, const t yi) {
    for (int i = 0; i < p.getsize(); i++) {
        p[i].x += xi;
        p[i].y += yi;
    }
    return (*this);
}

bool Polygon::isPoint(const t x, const t y)const {
    Point p(x, y);
    return include_point(p);
}

DynArray<Point> Polygon::intersection_Segment(const Segment& a)const {
    Point P1(a.getP1()), P2(a.getP2());
    DynArray<Point> K;
    Segment s;
    if (include_point(P1) && include_point(P2)) {
        Point J1(0, 0);
        Point J2(0, 1);
        Point J3(1, 0);
        K.push_back(J1);
        K.push_back(J2);
        K.push_back(J2);
        return K;
    }
    else if (include_point(P1) == true && include_point(P2) == false) {
        for (int i = 0; i < p.getsize(); i++) {
            s = getSide(i);
            if (s.isPoint(P1.getX(), P1.getY()) == true) {
                K.push_back(P1);
                return K;
            }
        }
        Point J1(0, 0);
        Point J2(0, 1);
        Point J3(1, 0);
        K.push_back(J1);
        K.push_back(J2);
        K.push_back(J2);
        return K;
    }
    else if (include_point(P2) == true && include_point(P1) == false) {
        for (int i = 0; i < p.getsize(); i++) {
            s = getSide(i);
            if (s.isPoint(P2.getX(), P2.getY()) == true) {
                K.push_back(P2);
                return K;
            }
        }
        Point J1(0, 0);
        Point J2(0, 1);
        Point J3(1, 0);
        K.push_back(J1);
        K.push_back(J2);
        K.push_back(J2);
        return K;
    }
    return K;
}