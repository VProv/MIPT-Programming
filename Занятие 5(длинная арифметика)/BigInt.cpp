#include "BigInt.h"


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
    try {
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
            throw std::out_of_range("too long");
    }
    catch (std::out_of_range& e)
    {
        std::cerr << e.what();
        return;
    }
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
    if ((*this) == a)
        return (*this);
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
    // здесь размер массива равен как минимум двум и перебор идет до предпоследнего разряда,
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

void BigInt::LevelUp()
{
    for (int i = CurSize; i >= 1; i--)
        buf[i] = buf[i - 1];
    if (buf[CurSize])
        CurSize++;
}


BigInt operator / (const BigInt& left, const BigInt& right) {
    try {
        if (right.CurSize == 1 && right.buf[0] == 0)
            throw std::invalid_argument("division by zero");
    }
    catch (std::invalid_argument& e)
    {
        throw e;
    }
    BigInt le(left);
    BigInt ri(right);
    le.minusflag = true;
    ri.minusflag = true;
    int k = left.CurSize;
    BigInt t;
    t.setzerocoef();
    t.CurSize = k;
    int pos = k - 1;
    for (int i = 0; i < k; i++) {
        for (int j = BigInt::base - 1; j >= 0; j--) {
            t.buf[pos] = j;
            if (t * ri <= le)
                break;
        }
        pos--;
    }
    t._remove_leading_zeros();

    if (left.minusflag == right.minusflag)
        t.minusflag = true;
    else
        t.minusflag = false;

    if (t.CurSize == 1 && t.buf[0] == 0)
        t.minusflag = true;

    return t;
}

BigInt operator % (const BigInt& left, const BigInt& right) {
    try {
        if (right.CurSize == 1 && right.buf[0] == 0)
            throw std::invalid_argument("division by zero");
    }
    catch (std::invalid_argument& e)
    {
        throw e;
    }
    BigInt t;
    t.setzerocoef();
    if (left < right)
        t = left;
    else if (left == right)
        t = 0;
    else {
        BigInt l = right * (left / right);
        l._remove_leading_zeros();
        t = left - l;
        t._remove_leading_zeros();

    }
    return t;
}


BigInt BigInt::sqrt()const {
    BigInt a(*this);
    int k = (a.CurSize + 1) / 2;
    BigInt t;
    t.setzerocoef();
    t.CurSize = k;
    int pos = k - 1;
    for (int i = 0; i < k; i++) {
        for (int j = BigInt::base - 1; j >= 0; j--) {
            t.buf[pos] = j;
            if (t * t <= a)
                break;
        }
        pos--;
    }
    return t;
}


BigInt GCD(const BigInt& a, const BigInt& b) { //greatest common divisor
    if (b == 0)
    {
        BigInt t(a);
        return t;
    }
    else
    {
        return GCD(b, a % b);
    }
}

std::istream& operator >>(std::istream& in, BigInt& s) {
    char a[BigInt::maxlen];
    in >> a;
    BigInt A(a);
    s = A;
    return in;
}