#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

class Point {
    int x;
    int y;
public:
    Point(int i, int j) {
        x = i;
        y = j;
    }
    double dist(const Point& t)const {
        return sqrt((x - t.x) * (x - t.x) + (y - t.y) * (y - t.y));
    }
};


int main() {
    int n;
    //scanf("%d", &n);
    cin >> n;
    vector<Point> v;
    int t, k;
    for (int i = 0; i < n; i++) {
        //scanf("%d", &t);
        //scanf("%d", &k);
        cin >> t;
        cin >> k;
        Point p(t, k);
        v.push_back(p);
    }
    double g = 0;
    for (vector<Point>::iterator it = v.begin(); it != v.end(); it++) {
        for (vector<Point>::iterator it1 = v.begin(); it1 != v.end(); it1++) {
            if (it->dist(*it1) > g)
                g = it->dist(*it1);
        }
    }

    //printf("%d", g);
    cout << setprecision(15) << g;
    int n;
    cin >> n;
    return 0;
}