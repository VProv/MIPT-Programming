#pragma once
#include <iostream>

class String {
    char* buf;
    size_t size, capacity;
    static const unsigned int grow_factor = 3;
public:
    String(const char* = "");
    String(const char);
    String(const String&);
    ~String();
    void setString(const String&);
    void setString(const char*);
    void setString(const char);    
    const unsigned int getSize();
    const unsigned int getCapacity();
    void clear(); //clear buf

    friend String operator + (const String&, const String&);
    friend String operator + (const String&, const char);
    friend String operator + (const char ch, const String& s2);
    friend String operator + (const String&, const char*);
    friend String operator + (const char*, const String&);
    String& operator += (const String&);
    String& operator += (const char);
    String& operator += (const char*);
    String& operator = (const String&);
    String& operator = (const char);
    String& operator = (const char*);
    friend const bool operator == (const String&, const String&); // compare bufs
    const char getIsymb(const unsigned int i); // getting I symbole
    bool changeIsymb(const unsigned int, const char); // changing I symbhole
    const char& operator [](unsigned int);
    String operator * (const unsigned int); // "ab" * 3 = "ababab"
    String& operator *= (const unsigned int);
    friend std::ostream& operator <<(std::ostream& out, String& s);
    friend std::istream& operator >>(std::istream& in, String& s);
    
};