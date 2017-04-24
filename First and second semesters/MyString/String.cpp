#include "String.h"
#include <cstring>
#include <iostream>

String:: String(const char* st) {
    size = strlen(st);
    capacity = size + 1;
    buf = new char[capacity];
    for (unsigned int i = 0; i < size; i++) {
        buf[i] = st[i];
    }
}

String::String(const char ch) {
    size = 1;
    capacity = size + 1;
    buf = new char[capacity];
    buf[0] = ch;    
}

String:: String(const String& str) {
    buf = new char[str.capacity];
    size = str.size;
    for (unsigned int i = 0; i < size; i++) {
        buf[i] = str.buf[i];
    }
    capacity = str.capacity;
}

String:: ~String() {
    delete[] buf;
}

String operator +(const String& s1, const String& s2) {
    String s;
    
    s.size = s1.size + s2.size;
    s.capacity = s2.capacity + s1.capacity;
    delete[] s.buf;
    s.buf = new char[s.capacity];
    unsigned int i = 0;
    for (i; i < s1.size; i++) {
        s.buf[i] = s1.buf[i];
    }
    for (i; i < s2.size + s1.size; i++) {
        s.buf[i] = s2.buf[i - s1.size];
    }

    return s;
}

String operator +(const String& s1, const char ch) {
    String s;
    delete[] s.buf;
    s.size = s1.size + 1;
    s.capacity = s1.capacity + 1;
    s.buf = new char[s.capacity];
    unsigned int i = 0;
    for (i; i < s1.size; i++) {
        s.buf[i] = s1.buf[i];
    }
    s.buf[i] = ch;
    return s;
}

String operator +(const char ch, const String& s2) {
    String s;
    delete[] s.buf;
    s.size = s2.size + 1;
    s.capacity = s2.capacity + 1;
    s.buf = new char[s.capacity];
    unsigned int i = 0;
    s.buf[i] = ch;
    i++;
    for (i; i < s2.size + 1; i++) {
        s.buf[i] = s2.buf[i - 1];
    }
    return s;
}

String operator + (const String& s1, const char* st) {
    unsigned int stSize = strlen(st);
    String s;
    delete[] s.buf;
    s.size = s1.size + stSize;
    s.capacity = s1.capacity + stSize;
    s.buf = new char[s.capacity];
    unsigned int i = 0;
    for (i; i < s1.size; i++) {
        s.buf[i] = s1.buf[i];
    }
    for (i; i < stSize + s1.size; i++) {
        s.buf[i] = st[i - s1.size];
    }
    return s;
}

String operator + (const char* st, const String& s2) {
    unsigned int stSize = strlen(st);
    String s;
    delete[] s.buf;
    s.size = s2.size + stSize;
    s.capacity = s2.capacity + stSize;
    s.buf = new char[s.capacity];
    unsigned int i = 0;
    for (i; i < stSize; i++) {
        s.buf[i] = st[i];
    }
    for (i; i < stSize + s2.size; i++) {
        s.buf[i] = s2.buf[i - stSize];
    }
    return s;
}

String& String:: operator += (const String& s) {
    if (size + s.size > capacity - 1) {
        if (capacity * grow_factor > capacity + s.capacity)
            capacity *= grow_factor;
        else
            capacity += s.capacity;

        char* temp = new char[capacity];
        unsigned int i = 0;
        for (i; i < size; i++) {
            temp[i] = buf[i];
        }
        
        for (i; i < size + s.size; i++) {
            temp[i] = s.buf[i - size];
        }
        size += s.size;
        delete[] buf;
        buf = new char[capacity];
        for (unsigned int i = 0; i < size; i++)
            buf[i] = temp[i];
        delete[] temp;
        return *this;
    }
    else {
        for (unsigned int i = size; i < size + s.size; i++) {
            buf[i] = s.buf[i - size];
        }
        size += s.size;
        return *this;
    }
}

String& String:: operator += (const char ch) {
    if (size + 1 > capacity - 1) {
        capacity *= grow_factor;

        char* temp = new char[capacity];
        unsigned int i = 0;
        for (i; i < size; i++) {
            temp[i] = buf[i];
        }       
        temp[i] = ch;
        size += 1;
        delete[] buf;
        buf = new char[capacity];
        for (unsigned int i = 0; i < size; i++)
            buf[i] = temp[i];
        delete[] temp;
        return *this;
    }
    else {
        buf[size] = ch;
        size += 1;
        return *this;
    }
}

String& String:: operator += (const char* st) {
    unsigned int stSize = strlen(st);
    if (size + stSize > capacity - 1) {
        if (capacity * grow_factor > capacity + stSize)
            capacity *= grow_factor;
        else
            capacity += stSize;

        char* temp = new char[capacity];
        unsigned int i = 0;
        for (i; i < size; i++) {
            temp[i] = buf[i];
        }
        
        for (i; i < size + stSize; i++) {
            temp[i] = st[i - size];
        }
        size += stSize;
        delete[] buf;
        buf = new char[capacity];
        for (unsigned int i = 0; i < size; i++)
            buf[i] = temp[i];
        delete[] temp;
        return *this;
    }
    else {       
        for (unsigned int i = size; i < size + stSize; i++) {
            buf[i] = st[i - size];
        }
        size += stSize;
        return *this;
    }
}

String& String:: operator = (const String& s) {
    if (s.size > capacity - 1) {
        if (capacity * grow_factor - 1 > s.size)
            capacity *= grow_factor;
        else
            capacity += s.size;
        char* temp = new char[capacity];
        unsigned int i = 0;
        for (i; i < s.size; i++) {
            temp[i] = s.buf[i];
        }        
        size = s.size;
        delete[] buf;
        buf = new char[capacity];
        for (unsigned int i = 0; i < size; i++)
            buf[i] = temp[i];
        delete[] temp;
        return *this;
    }
    else {
        size = s.size;
        for (unsigned int i = 0; i < s.size; i++)
            buf[i] = s.buf[i];
        return *this;
    }
}

void String::setString(const String& s) {
    *this = s;
}

void String::setString(const char* st) {
    String s(st);
    *this = s;
}

void String::setString(const char ch) {
    String s(ch);
    *this = s;
}

String& String:: operator = (const char ch) {
    String s(ch);
    *this = s;
    return *this;
}

String& String:: operator = (const char*st) {
    String s(st);
    *this = s;
    return *this;
}

const char String::getIsymb(const unsigned int i) {
    if (i < size)
        return buf[i];
    else
        return ' ';
}

bool String::changeIsymb(const unsigned int i, const char ch) {
    if (i < size) {
        buf[i] = ch;
        return true;
    }
    else {
        return false;
    }
}

const unsigned int String:: getSize() {
    return size;
}

const unsigned int String::getCapacity() {
    return capacity;
}

/*const char* String::getBuf() {
    buf[size] = '\0';
    return buf;
}*/

void String::clear() {
    size = 0;
    delete[] buf;
}

const char& String:: operator [](unsigned int i) {
    return buf[i];
}

String& String:: operator *= (const unsigned int i) {
    char* st = new char[size + 1];
    for (unsigned int j = 0; j < size; j++)
        st[j] = buf[j];
    st[size] = '\0';
    for (unsigned int j = 0; j < i - 1; j++) {
        *this += st;
    }
    delete[] st;
    return *this;
}

String String:: operator * (const unsigned int i) {
    char* st = new char[size + 1];
    for (unsigned int j = 0; j < size; j++)
        st[j] = buf[j];
    st[size] = '\0';
    String s;
    for (unsigned int j = 0; j < i; j++) {
        s += st;
    }
    return s;
}

const bool operator == (const String& s1, const String& s2) {
    if (s1.size == s2.size) {
        for (unsigned int i = 0; i < s1.size; i++) {
            if (s1.buf[i] != s2.buf[i])
                return false;
        }
        return true;        
    }
    else
        return false;
}

std::ostream& operator <<(std::ostream& output, String& s) {
    for (unsigned int i = 0; i < s.size; i++) {
        output << s.buf[i];
    }
    return output;
}


std::istream& operator >>(std::istream& in, String& s) {    
    const unsigned int maxStreamSize = 10000;
    char st[maxStreamSize];
    in >> st;
    s = st;
    return in;    
}




