#include <iostream>
#include <cstdlib>
#include "DynamicStack.h" 
#include "StaticStack.h" 

using namespace dynamic_stack;

int main() {
    char st;

    int n; //counter
    std::cout << "Enter count of strings" << std::endl;
    std::cin >> n;
    std::cout << std::endl;
    std::cin.get(st);

    for (int i = 0; i < n; i++) {
        Stack sk;
        int err = 0; //error symptom (in "while")
        std::cin.get(st); // we take first element on another way to avoid mistakes

        while (st == ' ')
            std::cin.get(st);

        if (st != 0 && st != '\n') {
            if (st >= '0' && st < '10') {
                sk.pop();
                const char* st1 = &st;
                sk.push(atoi(st1));
            }
            else if (st != ' ') {
                std::cout << "error" << std::endl;
                sk.clear();
                  
                while (st != 0 && st != '\n')
                    std::cin.get(st);
                continue;
            }
        }
        else {
            std::cout << "error" << std::endl;
            sk.clear();
            
            while (st != 0 && st != '\n')
                std::cin.get(st);
            continue;
        }

        std::cin.get(st);

        while (st != 0 && st != '\n') {
            if (st >= '0' && st < '10') {
                const char* st1 = &st;
                sk.push(atoi(st1));
            }
            else if (st == '+' && sk.size() > 1) {
                int a = sk.pop();
                int b = sk.pop();
                sk.push(b + a);
            }
            else if (st == '-'  && sk.size() > 1) {
                int a = sk.pop();
                int b = sk.pop();
                sk.push(b - a);
            }
            else if (st == '*'  && sk.size() > 1) {
                int a = sk.pop();
                int b = sk.pop();
                sk.push(b * a);
            }
            else if (st == '/'  && sk.size() > 1) {
                int a = sk.pop();
                int b = sk.pop();
                sk.push(b / a);
            }
            else if (st != ' ') {
                std::cout << "error" << std::endl;
                err = 1;
                break;
            }
            std::cin.get(st);
        }

        if (sk.size() == 1 && err == 0)
            std::cout << sk.top() << std::endl;
        else if (err == 0) {
            std::cout << "error" << std::endl;
            continue;
        }

        sk.clear();
        
        while (st != 0 && st != '\n')
            std::cin.get(st);
    }
    return 0;
}
