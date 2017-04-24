#pragma once
#include <vector>
#include <string>
#include <set>

using namespace std;

class User {
    set<string> phone_num;
    string email;
public:
    User() :phone_num(), email() {}
    User(const User& a): phone_num(a.phone_num), email(a.email) {}
    User(const string& t_phone_num, const string& t_email):phone_num(),email(t_email) {
        phone_num.insert(t_phone_num);
    }
    void add_phone(const string& phone);
    set<string> get_phones()const {
        return phone_num;
    }
    const set<string>& get_phones_for_reading()const {
        return phone_num;
    }
    void delete_phone(const string& phone);
    string get_email()const {
        return email;
    }
    string get_first_phone()const {
        return (*phone_num.begin());
    }
};