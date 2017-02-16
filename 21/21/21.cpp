#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cassert>
#include <ctime>
#include <time.h>
#include <stdlib.h> 

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
    friend bool operator > (const BigInt&, const int);
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

    //friend BigInt operator / (const BigInt&, const BigInt&);
    //BigInt operator / (const BigInt&)const;
    friend int difference(BigInt& x, BigInt& y, BigInt& z, int length); // difference between x and y in z
    BigInt& operator = (const BigInt&);
    BigInt& operator = (const long long);

    BigInt operator/(const BigInt& p) const;

    void clear();
    friend std::ostream& operator <<(std::ostream& out, BigInt& s);
};

bool operator <= (const BigInt& t, const long long a) {
    BigInt b(a);
    return (t <= b);
}

BigInt BigInt::xabs()const {
    BigInt t(*this);
    t.minusflag = true;
    return t;
}

BigInt& BigInt::operator = (const long long a) {
    BigInt ai(a);
    (*this) = ai;
    return(*this);
}

void BigInt::setBigInt(const int msize, const int* a, const bool minus) {
    if (a == nullptr) {
        CurSize = 1;
        minusflag = true;
        buf[0] = 0;
        return;
    }
    if (msize < maxlen) {
        for (int i = 0; i < msize; i++)
            buf[i] = a[i];
        CurSize = msize;
        minusflag = minus;
    }
    else
        assert(true);
}

void BigInt::setBigInt(const BigInt& a) {
    CurSize = a.CurSize;
    minusflag = a.minusflag;
    for (int i = 0; i < CurSize; i++)
        buf[i] = a.buf[i];
}

void BigInt::setBigInt(const int b) {
    int a = 0;
    if (b >= 0) {
        a = b;
        minusflag = true;
    }
    else {
        minusflag = false;
        a = b * (-1);
    }
    int i = 0;
    CurSize = 0;
    while (a != 0) {
        buf[i] = a % base;
        i++;
        CurSize++;
        a = a / base;
    }
}

void BigInt::setBigInt(const char* st) { //
    int start = 0; // start of number in st (0 or 1)
    int l = strlen(st);
    if (st[0] == '-') {
        minusflag = false;
        start = 1;
        l -= 1;
    }
    else
        minusflag = true;

    if (l % pow == 0)
        CurSize = l / pow;
    else
        CurSize = l / pow + 1;

    for (int i = 0; i < CurSize; i++) {
        char temp[pow];
        int t = (l - 1) - i * pow + start;
        int k = 0;
        for (int j = t - pow + 1; j < t + 1; j++) {
            temp[k] = st[j];
            k++;
        }
        buf[i] = abs(atoi(temp));
    }
}

BigInt:: ~BigInt() {}

BigInt::BigInt(const int* a, const int msize, const bool minus) {
    setBigInt(msize, a, minus);
}
BigInt::BigInt(const BigInt& a) {
    setBigInt(a);
}
BigInt::BigInt(const char*a) {
    setBigInt(a);
}

BigInt::BigInt(const int a) {
    setBigInt(a);
}

BigInt operator + (const BigInt& x, const BigInt& y) {
    BigInt temp;
    BigInt a;

    a.setzerocoef();
    a = x;

    a.buf[a.CurSize] = 0;
    BigInt b;
    b.setzerocoef();
    b = y;
    b.buf[b.CurSize] = 0;
    if (a.minusflag == b.minusflag) {
        temp.minusflag = true;
        temp.setzerocoef();
        int length = 0;
        if (a.CurSize > b.CurSize)
            length = a.CurSize + 1;
        else
            length = b.CurSize + 1;

        for (int i = 0; i < length; i++) {
            temp.buf[i] = temp.buf[i] + a.buf[i] + b.buf[i];
            temp.buf[i + 1] += (temp.buf[i] / temp.base);
            temp.buf[i] %= temp.base;
        }
        if (temp.buf[length - 1] == 0)
            length--;

        temp.CurSize = length;
        return temp;
    }
    else {
        BigInt temp;
        if (a.minusflag == false) {
            a.minusflag = true;
            b.minusflag = true;
            temp = b - a;
        }
        else if (b.minusflag == false) {
            a.minusflag = true;
            b.minusflag = true;
            temp = a - b;
        }
        return temp;
    }
}

void BigInt::setzerocoef() {
    for (int i = 0; i < this->maxlen; i++) {
        this->buf[i] = 0;
    }
}

BigInt operator + (const int c, const BigInt& b) {
    BigInt a(c);
    return a + b;
}

BigInt operator + (const BigInt& b, const int c) {
    BigInt a(c);
    return a + b;
}

BigInt operator + (const char* st, const BigInt& b) {
    BigInt a(st);
    return a + b;
}

BigInt operator + (const BigInt& b, const char* st) {
    BigInt a(st);
    return a + b;
}

BigInt operator - (const int c, const BigInt& b) {
    BigInt a(c);
    return a - b;
}

BigInt operator - (const BigInt& b, const int c) {
    BigInt a(c);
    return b - a;
}

BigInt operator - (const char* st, const BigInt& b) {
    BigInt a(st);
    return a - b;
}

BigInt operator - (const BigInt& b, const char* st) {
    BigInt a(st);
    return b - a;
}

int comparison(const BigInt& a, const BigInt& b) {
    int k = 3; // if k == 3, then ==
    if (a.minusflag == true && b.minusflag == false)
        return 1;
    if (a.minusflag == false && b.minusflag == true)
        return 2;
    int length = a.CurSize;
    if (a.CurSize > b.CurSize) {
        length = a.CurSize;
        k = 1; // first is bigger than second
    }
    else
        if (b.CurSize > a.CurSize) {
            length = b.CurSize;
            k = 2; // second is bigger
        }
        else
            for (int ix = 0; ix < length; ix++) // bitwise comparison
            {
                if (a.buf[ix] > b.buf[ix]) // first bitwise >
                {
                    k = 1; // this means first is bigger

                }

                if (b.buf[ix] > a.buf[ix]) // second bitwise > 
                {
                    k = 2; // this means second is bigger

                }
            }
    if (a.minusflag == true && b.minusflag == true)
        return k;
    else if (a.minusflag == false && b.minusflag == false) {
        if (k == 3)
            return k;
        else if (k == 1)
            return 2;
        else if (k == 2)
            return 1;
    }
}

bool operator > (const BigInt& a, const BigInt& b) {
    int k = comparison(a, b);
    if (k == 1)
        return true;
    else
        return false;
}
bool operator < (const BigInt& a, const BigInt& b) {
    int k = comparison(a, b);
    if (k == 2)
        return true;
    else
        return false;
}
bool operator == (const BigInt& a, const BigInt& b) {

    int k = comparison(a, b);
    if (k == 3)
        return true;
    else
        return false;
}
bool operator == (const BigInt& a, const long long b) {
    BigInt t(b);
    if (a == t)
        return true;
    else
        return false;
}

bool operator >= (const BigInt& a, const BigInt& b) {
    int k = comparison(a, b);
    if (k == 3 || k == 1)
        return true;
    else
        return false;
}
bool operator <= (const BigInt& a, const BigInt& b) {
    int k = comparison(a, b);
    if (k == 3 || k == 2)
        return true;
    else
        return false;
}
BigInt operator - (const BigInt& a, const BigInt& b) {
    BigInt x(a);
    BigInt y(b);
    int length = 0;
    BigInt z;
    if (x.CurSize >= y.CurSize)
        length = x.CurSize;
    else
        length = y.CurSize;
    if (x.minusflag == y.minusflag) { // then we do '-'
        if (x >= y) {
            difference(x, y, z, length);
            z.minusflag = x.minusflag;
        }
        else {
            difference(y, x, z, length);
            z.minusflag = false;
        }
    }
    else { // then we do "+"
        if (x.minusflag == false) { // we doing "+", but change sings
            x.minusflag = true;
            y.minusflag = true;
            z = x + y;
            z.minusflag = false;
        }
        else if (y.minusflag == false) {
            x.minusflag = true;
            y.minusflag = true;
            z = x + y;
        }
    }
    if (z.CurSize == 1 && z.buf[0] == 0)
        z.minusflag = true;
    if (z.CurSize == 0) {
        z.CurSize = 1;
        z.buf[0] = 0;
        z.minusflag = true;
    }
    return z;
}

int difference(BigInt& x, BigInt& y, BigInt& z, int length) {
    z.setzerocoef();

    if (x == y) {
        z.CurSize = 1;
        z.buf[0] = 0;
        z.minusflag = true;
        return 0;
    }
    for (int ix = 0; ix < length; ix++) // pass all the digits of the number from the last,
    {
        if (ix < (length - 1)) // if the current rank of numbers is not the first
        {
            x.buf[ix + 1]--; // next discharge occupy a greater number 1.
            z.buf[ix] += BigInt::base + x.buf[ix]; // the result of the sum of the values of the discharge current and a larger number of base

        }
        else  // if the current digit numbers - the first
            z.buf[ix] += x.buf[ix]; // in response to summarize the value of the current discharge a larger number of

        z.buf[ix] -= y.buf[ix]; //We subtract the value of the current discharge fewer

        if (z.buf[ix] / BigInt::base > 0)
        {
            z.buf[ix + 1]++; // turn 1 to the next discharge
            z.buf[ix] %= BigInt::base; // remove it from this discharge
        }
        if (z.buf[length - 1] == 0)
            z.CurSize = length - 1;
        else
            z.CurSize = length;
    }
    while (z.buf[z.CurSize - 1] == 0)
        z.CurSize--;
    return 0;
}

BigInt operator * (const BigInt& a, const BigInt& b) {
    BigInt c;
    c.setzerocoef();
    int length;
    length = a.CurSize + b.CurSize + 1;

    for (int i = 0; i < a.CurSize; i++)
        for (int j = 0; j < b.CurSize; j++)
            c.buf[i + j] += a.buf[i] * b.buf[j];

    for (int i = 0; i < length; i++)
    {
        c.buf[i + 1] += c.buf[i] / BigInt::base;
        c.buf[i] %= BigInt::base;
    }

    while (c.buf[length - 1] == 0)
        length--;
    if (length == 0)
        length = 1;
    c.CurSize = length;
    return c;
}


BigInt& BigInt::operator = (const BigInt& a) {
    (*this).setzerocoef();
    for (int i = 0; i < a.CurSize; i++)
        this->buf[i] = a.buf[i];
    this->CurSize = a.CurSize;
    this->minusflag = a.minusflag;
    return (*this);
}

std::ostream& operator <<(std::ostream& output, BigInt& s) {
    if (s.minusflag == false)
        output << '-';
    for (int i = s.CurSize - 1; i >= 0; i--) {
        output << s.buf[i];
    }

    return output;
}

void BigInt::clear() {
    setzerocoef();
    CurSize = 0;
}

BigInt operator * (const long long x, const BigInt& b) {
    BigInt a(x);
    return a * b;
}

BigInt operator * (const BigInt& b, const long long x) {
    BigInt a(x);
    return a * b;
}

void BigInt::_shift_right() {
    if (this->CurSize == 0) {
        this->buf[0] = 0;
        this->CurSize = 1;
        return;
    }
    this->buf[this->CurSize] = this->buf[this->CurSize - 1];
    this->CurSize++;
    // ����� ������ ������� ����� ��� ������� ���� � ������� ���� �� �������������� �������,
    for (size_t i = this->CurSize - 2; i > 0; --i)
        this->buf[i] = this->buf[i - 1];
    this->buf[0] = 0;
}

void BigInt::_remove_leading_zeros() {
    for (int i = CurSize - 1; i > 0; i--) {
        if (this->buf[i] == 0)
            this->CurSize--;
        else
            return;
    }
    return;
}
/*
BigInt operator / (const BigInt& left, const BigInt& right) {
if (right.CurSize == 1 && right.buf[0] == 0)
assert(false);
BigInt b = right;
b.minusflag = true;
BigInt result, current;
result.setzerocoef();
current.setzerocoef();
result.CurSize = left.CurSize;
for (long long i = left.CurSize - 1; i >= 0; --i) {
current._shift_right();//����� ����� ������� ������
current.buf[0] = left.buf[i];
current._remove_leading_zeros();
int x = 0, l = 0, r = BigInt::base;
while (l <= r) {
int m = (l + r) / 2;
BigInt t;
t = b * m;
if (t <= current) {
x = m;
l = m + 1;
}
else r = m - 1;
}

result.buf[i] = x;
BigInt kuaka;
kuaka = b * x;
current = current - kuaka;

current._remove_leading_zeros();
}

result.minusflag = (left.minusflag == right.minusflag);
result._remove_leading_zeros();
if (result.CurSize == 1 && result.buf[0] == 0)
result.minusflag = true;
return result;
}
*/
void BigInt::LevelUp()
{
    for (int i = CurSize; i >= 1; i--)
        buf[i] = buf[i - 1];
    if (buf[CurSize])
        CurSize++;
}

/*
BigInt operator / (const BigInt &ia, const BigInt &ib)
{
BigInt a(ia);
BigInt b(ib);
a.minusflag = true;
b.minusflag = true;
BigInt res;
res.setzerocoef();
BigInt curValue;
for (int i = a.CurSize - 1; i >= 0; i--)
{
curValue.LevelUp(); // * osn
curValue.buf[0] = a.buf[i];
// ��������� ������������ ����� x, ����� ��� b * x <= curValue
int x = 0;
int l = 0, r = BigInt::base;
while (l <= r)
{
int m = (l + r) >> 1;
BigInt cur = b * m;
if (cur <= curValue)
{
x = m;
l = m + 1;
}
else
r = m - 1;
}
res.buf[i] = x;
curValue = curValue - b * x;
}
// ����������� �� ���������� �����
int pos = a.CurSize;
while (pos >= 0 && res.buf[pos - 1] == 0)
pos--;
res.CurSize = pos;


if (ia.minusflag == ib.minusflag)
res.minusflag = true;
else
res.minusflag = false;

if (res.CurSize == 0) {
res.CurSize = 1;
res.buf[0] = 0;
res.minusflag = true;
}

return res;
}
*/

/*
BigInt operator / (const BigInt& left, const BigInt& right) {
if (right.CurSize == 1 && right.buf[0] == 0)
assert(false);
BigInt le(left);
BigInt ri(right);
le.minusflag = true;
ri.minusflag = true;
BigInt m;
m.setzerocoef();
BigInt res;
BigInt fr;
res.setzerocoef();
m = le;
int fl = 0;
int prevlen = 0;
while (m >= ri) {
BigInt k;
k.setzerocoef();
int hi = m.CurSize;
int step = 0;

while (k < ri) {
k = k * BigInt::base + m.buf[hi - 1];
hi--;
step++;
if (fl == 1) {
if (prevlen > m.CurSize - step + 1)
res = res * 10;
}
}
fl = 1;

BigInt p;
p.setzerocoef();
int nj;
for (int i = BigInt::base - 1; i > 0; i--) {
if ((ri * i) <= k) {
nj = i;
break;
}
}
res = res * BigInt::base;
res = res + nj;
prevlen = m.CurSize - step;
if (m.CurSize > step) {
BigInt def = nj * ri;
for (int j = 0; j < m.CurSize - step; j++) {
def = def * BigInt::base;
}
m = m - def;
}
else {
m = m - nj * ri;
}

}
if (fl == 1 && prevlen == 1) {
res = res * 10;
}

if (left.minusflag == right.minusflag)
res.minusflag = true;
else
res.minusflag = false;

if (res.CurSize == 1 && res.buf[0] == 0)
res.minusflag = true;

return res;
}
*/


bool operator > (const BigInt& a, const int b) {
    BigInt t(b);
    if (a > t)
        return true;
    else
        return false;
}

BigInt BigInt::operator/(const BigInt& pa) const{
    BigInt m;
    m.setzerocoef();
    BigInt p(pa);
    p.minusflag = true;
    BigInt Th(*this);
    if (p == 1)
        return *this;

    if (*this == 0 || Th < p)
    {
        m.minusflag = true;
        m.CurSize = 1;
    }
    else
    {
        if (p == 2)
        {
            m = *this;
            bool fl = true;
            for (int i = this->CurSize - 1; i >= 0; --i)
            {
                if (i > 0)
                    m.buf[i - 1] += (m.buf[i] % 2) * base;
                m.buf[i] = m.buf[i] / 2;
                if (m.buf[i] == 0 && fl)
                    m.CurSize--;
                else
                    fl = false;
            }
        }
        else
        {
            BigInt i = 1, j = Th, avr;
            avr.setzerocoef();
            while (j > i)
            {
                avr = i + (j - i) / 2;
                if (Th == p * avr)
                {
                    j = avr;
                    i = avr;
                }
                else
                    if (Th < p * avr)
                    {
                        j = avr;
                        if ((Th - p * j) < p && (Th - p * j) > 0)
                            i = j;
                    }
                    else
                    {
                        i = avr;
                        if ((Th - p * i) < p && (Th - p * i) > 0)
                            j = i;
                    }
            }
            m = j;
            m._remove_leading_zeros();
        }
        if (this->minusflag == p.minusflag)
            m.minusflag = true;
        else
            m.minusflag = false;
    }
    return m;
}


using namespace std;
int main() {
    char t[255];
    int m;
    cin >> t;
    cin >> m;
    BigInt it(t);
    BigInt im(m);
    BigInt k;
    BigInt tres;

    /*
    for (int i = 1; i < 1000; i++)
    for (int j = 1; j < 1000; j++) {
    it.clear();
    im.clear();
    k.clear();
    it = i;
    im = j;
    int t = i / j;
    k = it / im;
    if (!(k == t) && t != 0) {
    cout << it << endl;
    cout << im << endl;
    cout << k << endl;
    int h;
    cin >> h;
    }
    }
    */

    k = it / im;

    if (it < im || it == 0) {
        cout << 0;
        return 0;
    }
    else
        cout << k << endl;
    int n;
    cin >> n;

    return 0;
}