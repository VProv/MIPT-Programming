#include "Phone_book.h"
#include <iostream>

using namespace std;

int main() {
    Phone_book pb;
    string st;
    string st1;
    string st2,st3;
    while (cin >> st) {
        if (st == "add") {
            cin >> st1; // name
            cin >> st2; //phone
            cin >> st3;
            pb.add_user(st1, st2, st3);
        }
        else if (st == "nadd") {
            cin >> st1; // name
            cin >> st2; // phone
            pb.add_phone(st1, st2);
        }
        else if (st == "delete") {
            cin >> st1;// name
            pb.delete_user(st1);
        }
        else if (st == "get_phones") {
            cin >> st1; // name
            try {
                const set<string>& s1 = pb.get_phones(st1);
                for (set<string>::const_iterator it = s1.begin(); it != s1.end(); it++)
                    cout << *it << endl;
            }
            catch (invalid_argument& e) {
                cout << e.what() << endl;
            }
        }
        else if (st == "get_ph_em") {
            cin >> st1;//name
            try {
                const User& us = pb.get_phone_mail(st1);
                set<string> s1 = us.get_phones();
                for (set<string>::const_iterator it = s1.begin(); it != s1.end(); it++)
                    cout << *it << endl;
                cout << us.get_email() << endl;
            }
            catch (invalid_argument& e) {
                cout << e.what() << endl;
            }
        }
        else if (st == "get_name") {
            cin >> st1;//phone
            cout << pb.get_user(st1) << endl;
        }
        else if (st == "get_all") {
            const map<string, string>& ma = pb.get_all_phone_map_for_reading();
            for (map<string,string>::const_iterator it = ma.begin(); it != ma.end(); it++)
                cout << it->second << ' ' << it->first << endl;
        }
    }
    
    return 0;
}