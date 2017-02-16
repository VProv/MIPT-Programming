#pragma once
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <stdexcept>

class BigInt {
    const static int maxlen = 1000;
    const static int base = 10;
    const static int pow = 1; // 10^pow = base,please, turn it, i don't use the cmath log, because it can be 1,999999...
    int buf[maxlen];
    int CurSize;
    bool minusflag; // true "+", false "-"
public:
    BigInt(const int* a = nullptr, const int msize = 0, const bool minus = true);
    BigInt(const BigInt&);
    BigInt(const char*);
    BigInt(const int);
    void setBigInt(const int msize, const int* a, bool minus);
    void setBigInt(const BigInt&);
    void setBigInt(const char*);
    void setBigInt(const int);
    virtual ~BigInt();
    void setzerocoef();

    BigInt xabs() const;

    friend BigInt operator + (const BigInt&, const BigInt&);
    friend BigInt operator + (const int, const BigInt&);
    friend BigInt operator + (const BigInt& b, const int c);
    friend BigInt operator + (const char* st, const BigInt& b);
    friend BigInt operator + (const BigInt& b, const char* st);

    friend int comparison(const BigInt&, const BigInt&); //return flag: 1 if(a>b), 2 if (b<a) 3 if (a = b)
    friend bool operator > (const BigInt&, const BigInt&);
    friend bool operator < (const BigInt&, const BigInt&);
    friend bool operator == (const BigInt&, const BigInt&);
    friend bool operator == (const BigInt&, const long long);
    friend bool operator >= (const BigInt&, const BigInt&);
    friend bool operator <= (const BigInt&, const BigInt&);
    friend bool operator <= (const BigInt&, const long long);

    friend BigInt operator - (const BigInt&, const BigInt&);
    friend BigInt operator - (const int, const BigInt&);
    friend BigInt operator - (const BigInt& b, const int c);
    friend BigInt operator - (const char* st, const BigInt& b);
    friend BigInt operator - (const BigInt& b, const char* st);
    friend BigInt operator * (const BigInt&, const BigInt&);
    friend BigInt operator * (const long long, const BigInt&);
    friend BigInt operator * (const BigInt&, const long long);
    void _shift_right();
    void _remove_leading_zeros();
    void LevelUp();
    friend BigInt operator / (const BigInt&, const BigInt&);
    friend BigInt operator % (const BigInt& left, const BigInt& right);
    
    friend int difference(BigInt& x, BigInt& y, BigInt& z, int length); // difference between x and y returns into z
    BigInt& operator = (const BigInt&);
    BigInt& operator = (const long long);
    BigInt sqrt()const;
    friend BigInt GCD(const BigInt& a, const BigInt& b); //greatest common divisor
    void clear();
    friend std::ostream& operator <<(std::ostream& out, BigInt& s);
    friend std::istream& operator >>(std::istream& in, BigInt& s);
};







