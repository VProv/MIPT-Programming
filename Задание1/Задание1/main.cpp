#include <iostream>
#include "Point.h"
#include "Circle.h"
#include "Square.h"

int main() {
    setlocale(LC_CTYPE, "Russian");
    int k = 0;
    std::cout << "введите кол-во команд" << std::endl;
    std::cin >> k;

    std::cout << " 1 - New point, 2 - move" << std::endl;
    std::cout << " 4 - New circle, 5 - move 6 - scale" << std::endl;
    std::cout << " 7 - New square, 8 - move 9 - scale" << std::endl;

    Point p;
    Circle c;
    Square s;

    for (int i = 0; i < k; i++) {
        int l = 0;
        std::cin >> l;
        if (l == 1) {          
            std::cout << "¬ведите х и у" << std::endl;
            double x = 0, y = 0;
            std::cin >> x >> y;
            p.setPoint(x, y);
            p.getCurrentVal();
            std::cout << "OK";
        }
        else if (l == 4) {
            std::cout << "¬ведите х и у  и R" << std::endl;
            double x = 0, y = 0, R = 0;
            std::cin >> x >> y >> R;
            c.setCircle(x, y, R);
            c.getCurrentVal();
            std::cout << "OK";
        }
        else if (l == 7) {
            std::cout << "¬ведите х и у и side" << std::endl;
            double x = 0, y = 0, side = 0;
            std::cin >> x >> y >> side;
            s.setSquare(x, y, side);
            s.getCurrentVal();
            std::cout << "OK";
        }
        else if (l == 2) {
            std::cout << "¬ведите х и у" << std::endl;
            double x = 0, y = 0;
            std::cin >> x >> y;
            p.move(x, y);
            p.getCurrentVal();
        }
        else if (l == 5) {
            std::cout << "¬ведите х и у" << std::endl;
            double x = 0, y = 0;
            std::cin >> x >> y;
            c.move(x, y);
            c.getCurrentVal();
        }
        else if (l == 8) {
            std::cout << "¬ведите х и у" << std::endl;
            double x = 0, y = 0;
            std::cin >> x >> y;
            s.move(x, y);
            s.getCurrentVal();
        }
        else if (l == 6) {
            std::cout << "¬ведите k" << std::endl;
            double k = 0;
            std::cin >> k;
            c.scale(k);
            c.getCurrentVal();
        }
        else if (l == 9) {
            std::cout << "¬ведите k" << std::endl;
            double k = 0;
            std::cin >> k;
            s.scale(k);
            s.getCurrentVal();
        }
    }
    
    return 0;
}