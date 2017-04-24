#include <iostream>
#include "String.h"

using namespace std;

int main() {

    std::cout << "Capacity, size, array" << std::endl;
    String str("Vania");
    str.setString("Masha");
    std::cout << "Constructor and setter 1(str)" << std::endl;
    std::cout << str.getCapacity() << ' ' << str.getSize() << ' ' << str << std::endl;

    String strch('k');
    strch.setString('m');
    std::cout << "Constructor and setter 2(strch)" << std::endl;
    std::cout << strch.getCapacity() << ' ' << strch.getSize() << ' ' << strch << std::endl;

    String strs;
    strs.setString(str);
    std::cout << "Constructor and setter 3(strs)" << std::endl;
    std::cout << strs.getCapacity() << ' ' << strs.getSize() << ' ' << strs << std::endl;

    std::cout << "st1 = String + String" << std::endl;
    String st1 = str + strs;
    std::cout << st1;
    std::cout << st1.getCapacity() << ' ' << st1.getSize() << ' ' << st1 << std::endl;
    
    cout << "set number of iterations" << endl;
    int n = 0;
    cin >> n;
    cout << "1: st1(string) = Str + ch" << endl;
    cout << "2: st1 = String + st" << endl;
    cout << "3: st1 = String1 + String2" << endl;
    cout << "4: st1 = String1 * t" << endl;
    cout << "5: string1[i]" << endl;
    cout << "6: st1 *= t" << endl;
    cout << "7: st1 += st" << endl;
    for (int i = 0; i < n; i++) {
        int k = 0;
        cin >> k;
        if (k == 1) {
            char ch;
            cout << "set ch";
            cin >> ch;
            std::cout << "st1 = String + ch = " << ch << std::endl;
            st1 = str + ch;
            std::cout << st1.getCapacity() << ' ' << st1.getSize() << ' ' << st1 << std::endl;
        }
        if (k == 2) {
            char st[100];
            cout << "set st";
            cin >> st;
            std::cout << "(String)st1 = String + char* = " << st << std::endl;
            st1 = str + st;
            std::cout << st1.getCapacity() << ' ' << st1.getSize() << ' ' << st1 << std::endl;
        }        
        if (k == 3) {
            cout << "set string1:";
            cin >> str;
            cout << "set string2:";
            cin >> strs;
            st1 = str + strs;
            std::cout << st1.getCapacity() << ' ' << st1.getSize() << ' ' << st1 << std::endl;
        }
        if (k == 4) {
            cout << "set string1:";
            cin >> str;
            cout << "set factor ";
            unsigned int g = 0;
            cin >> g;
            st1 = str * g;
            std::cout << st1.getCapacity() << ' ' << st1.getSize() << ' ' << st1 << std::endl;
        }
        if (k == 5) {
            cout << "set string1:";
            cin >> str;
            cout << "set i ";
            unsigned int g = 0;
            cin >> g;
            cout << str[g];
        }
        if (k == 6) {
            cout << "set string1:";
            cin >> str;
            cout << "set factor ";
            unsigned int g = 0;
            cin >> g;
            str *= g;
            std::cout << str.getCapacity() << ' ' << str.getSize() << ' ' << str << std::endl;
        }
        if (k == 7) {
            cout << "set string1:";
            cin >> str;
            cout << "set st";
            char st[1000];
            cin >> st;
            str += st;
            std::cout << str.getCapacity() << ' ' << str.getSize() << ' ' << str << std::endl;
        }
    }

    return 0;
}