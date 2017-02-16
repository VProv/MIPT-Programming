/*#include <cassert>
template<typename T>
class DynArray {
    T* buf;
    int size, capacity;
    static const double grow_factor;
    static const unsigned int  startcapacity = 100;
public:
    DynArray();
    DynArray(const DynArray&);
    DynArray(const T* arr, const int length);
    ~DynArray();
    void SetDynArray(const DynArray&);
    void SetDynArray(const T* arr, const int length);
    unsigned int getcapacity() const;
    unsigned int getsize() const;
    void push_back(const T&);
    void clear();
    void eclear();//do not delet buf
    T pop_back();
    T& operator [](const unsigned int)const;
};


template<typename T>
const double DynArray<T>::grow_factor = 2;

template<typename T>
T DynArray<T>::pop_back() {
    if (size > 0) {
        T a = (*this)[size - 1];
        size--;
        return a;
    }
}

template<typename T>
DynArray<T>::DynArray() {
    buf = new T[startcapacity];
    capacity = startcapacity;
    size = 0;
}

template<typename T>
void DynArray<T>::SetDynArray(const DynArray& a) {
    if (a.capacity <= this->capacity) {
        this->size = a.size;
        for (int i = 0; i < size; i++)
            buf[i] = a[i];
    }
    else {
        clear();
        capacity = a.capacity;
        size = a.size;
        buf = new T[capacity];
        for (int i = 0; i < size; i++)
            buf[i] = a.buf[i];
    }
    return;
}

template<typename T>
DynArray<T>::DynArray(const DynArray& a) {
    SetDynArray(a);
}

template<typename T>
void DynArray<T>::clear() {
    delete[] buf;
    capacity = 0;
    size = 0;
}

template<typename T>
void DynArray<T>::eclear() {
    size = 0;
}

template<typename T>
DynArray<T>::DynArray(const T* array, const int length) {
    buf = new T[length + 1];
    size = length;
    capacity = length + 1;
    for (int i = 0; i < length; i++) {
        buf[i] = array[i];
    }
}

template<typename T>
void DynArray<T>::SetDynArray(const T* ar, const int length) {
    if (length <= capacity) {
        this->size = length;
        for (int i = 0; i < size; i++)
            buf[i] = ar[i];
    }
    else {
        clear();
        if (length < DynArray<T>::startcapacity)
            capacity = DynArray<T>::startcapacity;
        else
            capacity = length + 1;
        size = length;
        buf = new T[capacity];
        for (int i = 0; i < size; i++)
            buf[i] = ar[i];
    }
    return;
}

template<typename T>
DynArray<T>::~DynArray() {
    clear();
}

template<typename T>
void DynArray<T>::push_back(const T& a) {
    if (capacity == 0) {
        DynArray<T> H;
        (*this) = H;
        buf[0] = a;
        size++;
    }
    else if (size + 1 > capacity) {
        T* temp = buf;
        buf = new T[static_cast<int>(capacity * grow_factor)];
        capacity = static_cast<int>(capacity * grow_factor);
        for (int i = 0; i < size; i++) {
            buf[i] = temp[i];
        }
        delete[] temp;
        buf[size] = a;
        size++;
    }
    else {
        buf[size] = a;
        size++;
    }
}

template<typename T>
T& DynArray<T>::operator [](const unsigned int a)const {
    if (a < size)
        return buf[a];
    else
        throw 1;
}

template<typename T>
unsigned int DynArray<T>::getcapacity()const {
    return capacity;
}

template<typename T>
unsigned int DynArray<T>::getsize()const {
    return size;
}*/
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;
class Point;
class Vector;
class Segment;
class Polygon;
class Circle;
class base {
public:
    typedef double t;
    /*virtual base& move(const t, const t);
    virtual bool isPoint(const t, const t)const;
    virtual DynArray<Point> isSegment(const Segment)const;*/

    virtual t min(const t a, const t b)const;
    virtual t max(const t a, const t b)const;
};

class Point:public base {
    t x;
    t y;
public:
    Point(t x = 0, t y = 0);
    t getX()const;
    t getY()const;
    void setX(const t);
    void setY(const t);
    virtual Point& move(const t, const t);
    virtual bool isPoint(const t, const t)const;
    
    friend t area(const Point a, const Point b, const Point  c);
    friend bool intersect_1(int a, int b, int c, int d);
    friend bool intersect(const Point a, const Point  b, const Point c, const Point d);
    bool belongsTo(Segment A)const;

    double distance(const Point & p)const {
        return sqrt((this->x - p.x)*(this->x - p.x) + (this->y - p.y)*(this->y - p.y));
    }
    Point& operator = (const Point& p) {
        x = p.x;
        y = p.y;
        return (*this);
    }
    friend bool operator == (const Point & a, const Point & b) {
        return (a.x == b.x && a.y == b.y);
    }

};


void Point:: setX(const t a) {
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

bool intersect_1(int a, int b, int c, int d) {
    if (a > b)  swap(a, b);
    if (c > d)  swap(c, d);
    return max(a, c) <= min(b, d);
}

bool intersect(const Point a, const Point b, const Point c, const Point d) {
    return intersect_1(a.x, b.x, c.x, d.x)
        && intersect_1(a.y, b.y, c.y, d.y)
        && area(a, b, c) * area(a, b, d) <= 0
        && area(c, d, a) * area(c, d, b) <= 0;
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

class Circle :public base {
    t x;
    t y;
    t R;
public:
    Circle(const t x = 0, const t y = 0, const t R = 0);
    void setX(const t&);
    void setY(const t&);
    void setR(const t&);
    t getX()const;
    t getY()const;
    t getR()const;

    void two_circles(const Circle & q) const {
        Point c(x, y);
        Point qc(q.x, q.y);
        if (c == qc) {
            if (this->R == q.R)
                cout << 3;
            else
                cout << 0;
        }
        else {
            Circle _c2(qc.getX() - c.getX(), qc.getY() - c.getY(), q.R);
            Point _c2c(_c2.x, _c2.y);
            double A = -2 * _c2c.getX(),
                B = -2 * _c2c.getY(),
                C = _c2c.getX() * _c2c.getX() + _c2c.getY() * _c2c.getY() + R * R - _c2.R * _c2.R;
            double x0 = -A * C / (A * A + B * B),
                y0 = -B * C / (A * A + B * B);
            if (C * C > R * R * (A * A + B * B) + 0.0001)
                cout << 0;
            else {
                if (abs(C * C - R * R * (A * A + B * B)) < 0.0001) {
                    cout << 1 << endl << x0 + c.getX() << ' ' << y0 + c.getY();
                }
                else {
                    double d = R * R - C * C / (A * A + B * B);
                    double mult = sqrt(d / (A * A + B * B));
                    double ax, ay, bx, by;
                    ax = x0 + B * mult;
                    bx = x0 - B * mult;
                    ay = y0 - A * mult;
                    by = y0 + A * mult;
                    cout << 2 << endl << setprecision(10) << ax + c.getX() << ' ' << ay + c.getY() << endl << bx + c.getX() << ' ' << by + c.getY();
                }
            }
        }
    }

};

Circle::Circle(const t ix, const t iy, const t iR) {
    x = ix;
    y = iy;
    R = iR;
}

class Vector {
    typedef double t;
    t x;
    t y;
public:
    Vector() {
        this->x = 0;
        this->y = 0;
    }
    Vector(double x, double y) {
        this->x = x;
        this->y = y;
    }
    Vector(const Point & obj) {
        this->x = obj.getX();
        this->y = obj.getY();
    }
    Vector(const Point & p1, const Point & p2) {
        this->x = p2.getX() - p1.getX();
        this->y = p2.getY() - p1.getY();
    }
    ~Vector() {}
    void set_values(double x, double y) {
        this->x = x;
        this->y = y;
    }
    bool belongs_point(const Point & p) const {
        return ((this->y / this->x == p.getX() / p.getY()) && this->x >= p.getX() && this->y >= p.getY());
    }
    double distance(const Point & obj) const {
        Vector v(obj);
        double l = v.dlina();
        double alfa = this->angle(v);
        return l * sin(alfa);
    }
    double dlina() const {
        return sqrt(this->x * this->x + this->y * this->y);
    }
    double angle(const Vector & v) const {
        double c;
        if (dlina() == 0 || v.dlina() == 0)
            return 0;
        c = (this->x * v.x + this->y * v.y) / (this->dlina() * v.dlina());
        return acos(c);
    }
    double operator * (const Vector & v) {
        return (this->x * v.y - this->y * v.x);
    }
    double Scal(const Vector & v) {
        return (this->x * v.x + this->y * v.y);
    }
    Vector operator = (const Vector & p) {
        this->x = p.x;
        this->y = p.y;
        return *this;
    }
    double get_x() const {
        return this->x;
    }
    double get_y() const {
        return this->y;
    }
    void set_x(double x) {
        this->x = x;
    }
    void set_y(double y) {
        this->y = y;
    }
};

class Segment : public base {
    t x1, x2;
    t y1, y2;
public:
    Segment(const t x1 = 0, const  t y1 = 0, const  t x2 = 0, const  t y2 = 0);
    Segment(const Point&, const Point&);
    virtual Segment& move(const t, const t);
    virtual bool isPoint(const t, const t)const;
    //virtual DynArray<Point> isSegment(const Segment&)const;

    t getX1() const;
    t getX2() const;
    t getY1() const;
    t getY2() const;
    friend bool operator == (const Segment& a, const Segment& b);
    friend bool rotation(const Segment& a, const Segment& b);
    friend t det(const Segment& a, const Segment& b);
    double distance(const Point & p) const {
        Point p1(x1, y1);
        Point p2(x2, y2);
        Point copy_1(p2.getX() - p1.getX(), p2.getY() - p1.getY());
        Vector v1(copy_1);
        Point copy_2(p.getX() - p1.getX(), p.getY() - p1.getY());
        Vector v2(copy_2);
        double alfa = v1.angle(v2), dist = 0;
        double c = p1.distance(p2),
            a = p1.distance(p),
            b = p2.distance(p);
        if ((a * a + c * c - b * b) * (b * b + c * c - a * a) > 0) {
            dist = abs(a * sqrt(1 - cos(alfa)*cos(alfa)));
            if (dist < 0.000001)
                dist = 0;
        }
        else {
            Point p1(x1, y1);
            Point p2(x2, y2);
            dist = min(p1.distance(p), p2.distance(p));
        }
        return dist;
    }

    double dlina() const {
        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }
    
    bool belongs_point(const Point & p) const {
        Point p1(x1, y1);
        Point p2(x2, y2);
        Vector a(p1.getX() - p.getX(), p1.getY() - p.getY()),
            b(p2.getX() - p.getX(), p2.getY() - p.getY());
        if (a * b == 0 && a.Scal(b) <= 0)
            return true;
        else
            return false;
    }

};

Segment::t Segment::getX1()const {
    return x1;
}
Segment::t Segment::getX2()const {
    return x2;
}
Segment::t Segment::getY1()const {
    return y1;
}
Segment::t Segment::getY2()const {
    return y2;
}


Segment::Segment(const t ix1, const  t iy1, const  t ix2, const  t iy2) {
    x1 = ix1;
    x2 = ix2;
    y1 = iy1;
    y2 = iy2;
}

Segment::Segment(const Point& a, const Point& b) {
    x1 = a.getX();
    y1 = a.getY();
    x2 = b.getX();
    y2 = b.getY();
}

Segment& Segment::move(t x, t y) {
    x1 += x;
    x2 += x;
    y1 += y;
    y2 += y;
    return (*this);
}

bool Segment::isPoint(const t x, const t y)const {
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
    if (((a.x2 - a.x1) * (b.y2 - b.y1) - (a.y2 - a.y1) * (b.x2 - b.x1)) >= 0)
        return true;
    else
        return false;
}

Segment::t det(const Segment& a, const Segment& b) {
    return (a.x2 - a.x1) * (b.y2 - b.y1) - (a.y2 - a.y1) * (b.x2 - b.x1);
}

bool operator == (const Segment& a, const Segment& b) {
    if (a.x1 == b.x1 && a.x2 == b.x2 && a.y1 == b.y1 && a.y2 == b.y2)
        return true;
    else return false;
}

Point::t area(const Point  a, const Point  b, const Point  c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

class Line: public base{
    double a, b, c;
public:
    Line(Segment A); 
    Line(const Point& P, const Line& L);
    Point inters(const Line& L);
    double getA() const{
        return a;
    }
    double getB() const{
        return b;
    }
    double getC() const{
        return c;
    }
};

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

Line::Line(Segment A) {
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

bool  Point::belongsTo(Segment A)const
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

double distance(const Point& P, const Segment& A, const Line& L) {
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
void CircleLineInter(double x1,double y1,double r, double a, double b, double c) {
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
        cout << 2 << endl;
        cout << ax << ' ' << ay << endl;
        cout << bx << ' ' << by << endl;
    }
}

class Polygon : public base {
protected:
    int n;
    Point *p;
public:
    Polygon() {
        this->n = 0;
    }
    Polygon(int n, Point *a) {
        this->n = n;
        this->p = new Point[n];
        for (int i = 0; i < n; i++)
            this->p[i] = a[i];
    }
    Polygon(const Polygon &m) {
        this->n = m.n;
        p = new Point[m.n];
        for (int i = 0; i < m.n; ++i)
            this->p[i] = m.p[i];
    }
    ~Polygon() {
        delete[] p;
    }
    bool belongs_point(const Point & q) const {
        for (int i = 0; i < n; i++) {
            Point p1(p[i].getX(), p[i].getY()),
                p2(p[(i + 1) % n].getX(), p[(i + 1) % n].getY());
            Segment s(p1, p2);
            if (s.belongs_point(q))
                return true;
        }
        return false;
    }
    double distance(const Point & p1) const {
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
    bool convexity() {
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

    Segment getSide(int i) const {
        int j;
        if (i != n - 1)
            j = i + 1;
        else
            j = 0;
        Segment side(p[i], p[j]);
        return side;
    }

    Polygon operator = (const Polygon & m) {
        if (this != &m) {
            delete[] p;
            Polygon c(m);
            return c;
        }
        return *this;
    }

    bool include_point(const Point & q) const {
        if (belongs_point(q))
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


    double perimeter()const {
        double P = 0;
        for (int i = 0; i < n; ++i)
            P += getSide(i).dlina();
        return P;
    }

    double square() const {
        for (int i = 1; i < n; i++) {
            p[i].setX(p[i].getX() - p[0].getX());
            p[i].setY(p[i].getY() - p[0].getY());
        }
        p[0].setX(0);
        p[0].setY(0);
        Vector s1(p[1]), s2(p[2]);
        double S = 0.5 * (s1.dlina() * s2.dlina() * (sin(s1.angle(s2))));
        for (int i = 3; i < n; ++i) {
            s1 = s2;
            s2.set_x(p[i].getX());
            s2.set_y(p[i].getY());
            S += 0.5 * (s1.dlina() * s2.dlina() * (sin(s1.angle(s2))));
        }
        return S;
    }

};
/*
class Cmp {
public:
    bool operator () (Point a, Point b) {
        return a.getX() < b.getX() || a.getX() == b.getX() && a.getY() < b.getY();
    }
};
*/

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


int mergesort(std::vector<Point>& a, int left, int right, std::vector<Point>& temp) {
    if (left == right)
        return 0;

    int mid = (left + right) / 2;
    mergesort(a, left, mid, temp);
    mergesort(a, mid + 1, right, temp);

    int i = left;
    int j = mid + 1;
    for (int step = 0; step < right - left + 1; step++) {
        if ((j > right) || (i <= mid && cmp(a[i], a[j]))) {
            temp[step] = a[i];
            i++;
        }
        else {
            temp[step] = a[j];
            j++;
        }
    }

    for (int i = 0; i < right - left + 1; i++)
        a[left + i] = temp[i];
    return 0;
}

void convex_hull(std::vector<Point>& a) {
    if (a.size() == 1)  return;
    sort(a.begin(), a.end(), &cmp);
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



#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    double x, y;
    std::vector<Point> a;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        Point po(x, y);
        a.push_back(po);
    }
    
    convex_hull(a);
    int r = a.size();
    Point *t = new Point[r];
    for (int i = 0; i < r; i++)
        t[i] = a[i];
    Polygon q(r, t);
    cout << setprecision(10) << q.perimeter() << endl; 
    cout << setprecision(10) << q.square();
    delete[] t;
    int an;
    cin >> an;
}