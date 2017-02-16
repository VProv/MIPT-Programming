#pragma once
#include <string>
#include <map>
#include <set>
#include <stdexcept>
#include "User_data.h"

using namespace std;

class Phone_book {
    map<string, User> u_map; // full name, data
    map<string, string> p_map; // phone, full name
public:
    Phone_book() :u_map(), p_map() {}
    Phone_book(map<string, User> a,map<string, string> c):u_map(a),p_map(c) {}
    Phone_book(const Phone_book& p):u_map(p.u_map), p_map(p.p_map) {}
    void add_user(const string& f_name,const string& phone,const string& email = "");
    void add_phone(const string& f_name,const string& phone);
    void delete_user(const string&);
    void delete_phone(const string& f_name, const string& phone);
    set<string> get_phones(const string& f_name)const;
    const set<string>& get_phones_for_reading(const string& f_name)const;
    User get_phone_mail(const string& f_name)const;
    const User& get_phone_mail_for_reading(const string& f_name)const;
    map<string, User> get_all_map()const {
        return u_map;
    }
    map<string, string> get_all_phone_map()const {
        return p_map;
    }
    const map<string, User>& get_all_map_for_reading()const {
        return u_map;
    }
    const map<string, string>& get_all_phone_map_for_reading()const {
        return p_map;
    }
    string get_user(const string& phone)const;
    // create one full name from three separate
    string create_full_name(const string& s1, const string& s2, const string& s3)const; 
};

