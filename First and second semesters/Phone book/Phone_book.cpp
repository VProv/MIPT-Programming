#include "Phone_book.h"

using namespace std;

void Phone_book::add_user(const string& f_name, const string& phone, const string& email) {
    User us(phone, email);
    u_map[f_name] = us;
    p_map[phone] = f_name;
}

void Phone_book::add_phone(const string& f_name, const string& phone) {
    u_map[f_name].add_phone(phone);
    p_map[phone] = f_name;
}

void Phone_book::delete_user(const string& f_name) {
    if (u_map.find(f_name) != u_map.end()) {
        set<string> st = u_map[f_name].get_phones();
        u_map.erase(f_name);
        for (set<string>::iterator it = st.begin(); it != st.end(); it++)
            p_map.erase((*it));
    }
    else
        return;
}

void Phone_book::delete_phone(const string& f_name, const string& phone) {
    u_map[f_name].delete_phone(phone);
    p_map.erase(phone);
}

set<string> Phone_book::get_phones(const string& f_name)const {
    if (u_map.find(f_name) != u_map.end())
        return (*u_map.find(f_name)).second.get_phones();
    else {
        set<string> s;
        return s;
    }        
}

const set<string>& Phone_book::get_phones_for_reading(const string& f_name)const {
    if (u_map.find(f_name) != u_map.end())
        return (*u_map.find(f_name)).second.get_phones();
    else {
        throw invalid_argument("user not found");
    }
}

User Phone_book::get_phone_mail(const string& f_name)const {
    if (u_map.find(f_name) != u_map.end())
        return (*u_map.find(f_name)).second;
    else {
        User s;
        return s;
    }
}

const User& Phone_book::get_phone_mail_for_reading(const string& f_name)const {
    if (u_map.find(f_name) != u_map.end())
        return (*u_map.find(f_name)).second;
    else {
        throw invalid_argument("user not found");
    }
}

string Phone_book::get_user(const string& phone)const {
    if (p_map.find(phone) != p_map.end())
        return p_map.find(phone)->second;
    else
        return "";
}

string Phone_book::create_full_name(const string& s1, const string& s2, const string& s3)const {
    string s;
    s += s1;
    s += ' ';
    s += s2;
    s += ' ';
    s += s3;
    return s;
}