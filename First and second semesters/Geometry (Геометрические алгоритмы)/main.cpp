#include <iostream>
#include "Geometry.h"

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

    Polygon P;
    P.convex_hull(a);
    int r = a.size();
    Point *t = new Point[r];
    for (int i = 0; i < r; i++)
        t[i] = a[i];
    for (int i = 0; i < r; i++)
        cout << a[i].getX() << ' ' << a[i].getY() << endl;

    Polygon q(r, t);
    cout << setprecision(10) << q.perimeter() << endl;
    cout << setprecision(10) << q.square();
    delete[] t;
    int an;
    cin >> an;
}