#pragma once
#include <assert.h>
#include <iostream>
#include <stdexcept>

template<typename t>
class Matrix {
protected:
    const static unsigned int maxlen = 100000000;
    t** IndexAr; // Array of indexes pointing to rows
    t* buf; // we store all elements in one buffer
    unsigned int columns, rows; //count of columns and rows
public:
    Matrix(int rows = 0, int columns = 0, t** array = nullptr);
    Matrix(const Matrix&);
    Matrix(int rows, int columns, t* array);
    virtual ~Matrix();
    void setBuf(unsigned int i = 0); // we reserve memory for i elements
    void setMatrix(int rows, int columns, t** array);
    void setMatrix(int rows, int columns, t* array);
    void clear();
    t* operator [](unsigned int index);
    t* operator [](unsigned int index) const;
    int getNumRows()const;
    int getNumColumns()const;

    template<typename t2>
    friend std::ostream& operator << (std::ostream& out,const Matrix<t2>& s);

    template<typename t2>
    friend std::istream& operator >>(std::istream& in, Matrix<t2>& s);

    Matrix& operator = (const Matrix&);
    Matrix operator * (const Matrix&) const;
    Matrix operator + (const Matrix&) const;
    Matrix operator * (const t) const;
    template<typename t2>
    friend Matrix operator * (const t, const Matrix<t2>&);
    Matrix& operator *= (const Matrix&);
    Matrix& operator += (const Matrix&);
    Matrix& operator *= (const t k);
    Matrix transp(); //transponation of Matrix
    bool operator == (const Matrix&);
};

template<typename t>
class squareMatrix : public Matrix<t> {
public:
    squareMatrix(int rows = 0, int columns = 0, t** array = nullptr);
    squareMatrix(int rows, int columns, t* array);
    squareMatrix(const Matrix&);
    virtual ~squareMatrix();
    squareMatrix& operator = (const squareMatrix&);
    double Determinant();
    squareMatrix inverse();
    squareMatrix getpow(const int i)const; // return Matrix in Power of i
};


template<typename t>
Matrix <t> ::Matrix (int rowC, int columnC, t** array) {
    columns = columnC;
    rows = rowC;

    if (rowC == 0 || columnC == 0) {
        return;
    }
    try {
        if (rowC > maxlen)
            throw std::length_error("big length");
    }
    catch (std::length_error& e)
    {
        throw e;
    }
    IndexAr = new t*[rowC];
    unsigned int size = rowC * columnC;
    setBuf(size);

    for (int i = 0; i < rowC; i++) {
        IndexAr[i] = &buf[i * columnC];
    }
    if (array != nullptr) {
        for (int i = 0; i < rowC; i++)
            for (int j = 0; j < columnC; j++)
                (*this)[i][j] = array[i][j];
    }
}

template<typename t>
Matrix <t> ::Matrix (int rowC, int columnC, t* array) {
    columns = columnC;
    rows = rowC;

    if (rowC == 0 || columnC == 0) {
        IndexAr = nullptr;
        buf = nullptr;
        return;
    }
    try {
        if (rowC > maxlen)
            throw std::length_error("too big");
        IndexAr = new t*[rowC];

    }
    catch (std::length_error& e)
    {
        throw e;
    }

    unsigned int size = rowC * columnC;
    setBuf(size);

    for (int i = 0; i < rowC; i++) {
        IndexAr[i] = &buf[i * columnC];
    }
    if (array != nullptr) {
        for (int i = 0; i < rowC; i++)
            for (int j = 0; j < columnC; j++)
                (*this)[i][j] = array[i * columns + j];
    }
}

template<typename t>
void Matrix <t> ::setMatrix(int rowC, int columnC, t* array) {

    if (rowC == 0 || columnC == 0) {
        IndexAr = nullptr;
        buf = nullptr;
        return;
    }

    columns = columnC;
    rows = rowC;
    try { 
        if (rowC > maxlen)
            throw std::length_error("too big");
        IndexAr = new t*[rowC];
    }
    catch (std::length_error& e)
    {
        throw e;
        return -1;
    }
    unsigned int size = rowC * columnC;
    setBuf(size);

    for (int i = 0; i < rowC; i++) {
        IndexAr[i] = &buf[i * columnC];
    }
    if (array != nullptr) {
        for (int i = 0; i < rowC; i++)
            for (int j = 0; j < columnC; j++)
                (*this)[i][j] = array[i * columns + j];
    }
}

template<typename t>
Matrix<t>:: ~Matrix() {
    delete[] IndexAr;
    delete[] buf;
}


template<typename t>
void Matrix<t>::setBuf(unsigned int size) {
    try {
        if (size > maxlen)
            throw std::length_error("too big");
        buf = new t[size];
    }
    catch (std::length_error& e)
    {
        throw e;
    }
}

template<typename t>
t* Matrix<t>:: operator [](unsigned int index) {
    try {
        if (index <= rows)
            return IndexAr[index];
        else
            throw std::range_error("out of range");
    }
    catch (std::range_error& e)
    {
        throw e;
    }
}

template<typename t>
t* Matrix<t>:: operator [](unsigned int index) const {
    try {
        if (index <= rows)
            return IndexAr[index];
        else
            throw std::range_error("bad size");
    }
    catch (std::range_error& e)
    {
        throw e;
    }
}

template<typename t>
Matrix<t> Matrix<t>:: operator * (const Matrix<t>& m2) const {
    try {
        if (columns == m2.rows) {
            Matrix m(rows, m2.columns);
            for (unsigned int i = 0; i < rows; i++)
                for (unsigned int j = 0; j < m2.columns; j++) {
                    t sum = 0;
                    for (unsigned int b = 0; b < columns; b++) {
                        sum += (*this)[i][b] * m2[b][j];
                    }
                    m[i][j] = sum;
                }
            return m;
        }
        else
            throw std::length_error("bad_size");
    }
    catch (std::length_error& e)
    {
        throw e;
    }
}

template<typename t>
Matrix<t> Matrix<t>:: operator + (const Matrix<t>& m2) const {
    try {
        if (rows == m2.rows && columns == m2.columns) {
            Matrix m(rows, columns);
            for (unsigned int i = 0; i < rows; i++)
                for (unsigned int j = 0; j < columns; j++)
                    m[i][j] = (*this)[i][j] + m2[i][j];
            return m;
        }
        else
            throw std::length_error("bad size");
    }
    catch (std::length_error& e)
    {
        throw e;
    }
}

template<typename t>
Matrix<t> Matrix<t>:: operator * (const t k) const {
    Matrix m(rows, columns);
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < columns; j++)
            m[i][j] = (*this)[i][j] * k;
    }
    return m;
}

template<typename t>
Matrix<t> operator * (const t k, const Matrix<t>& m2) {
    Matrix m(m2.rows, m2.columns);
    for (unsigned int i = 0; i < m2.rows; i++)
        for (unsigned int j = 0; j < m2.columns; j++)
            m[i][j] = m2[i][j] * k;
    return m;
}

template<typename t>
Matrix<t>::Matrix(const Matrix<t>& m2) {
    columns = m2.columns;
    rows = m2.rows;

    if (m2.rows == 0 || m2.columns == 0) {
        IndexAr = nullptr;
        buf = nullptr;
        return;
    }
    try {
        if (m2.rows > maxlen)
            throw length_error("too big");
        IndexAr = new t*[m2.rows];
    }
    catch (std::length_error& e)
    {
        throw e;
    }

    unsigned int size = m2.rows * m2.columns;
    setBuf(size);

    for (unsigned int i = 0; i < m2.rows; i++) {
        IndexAr[i] = &buf[i * m2.columns];
    }

    for (unsigned int i = 0; i < m2.rows; i++)
        for (unsigned int j = 0; j < m2.columns; j++)
            (*this)[i][j] = m2[i][j];
}


template<typename t>
void Matrix<t>::setMatrix(int rows, int columns, t** array) {
    this->clear();
    Matrix(rows, columns, array);
}

template<typename t>
Matrix<t>& Matrix<t>:: operator = (const Matrix<t>& m2) {
    if (this->buf == m2.buf)
        return (*this);
    clear();
    columns = m2.columns;
    rows = m2.rows;

    if (m2.rows == 0 || m2.columns == 0) {
        IndexAr = nullptr;
        buf = nullptr;
        return *this;
    }

        IndexAr = new t*[m2.rows];

    unsigned int size = m2.rows * m2.columns;
    setBuf(m2.rows * m2.columns);

    for (unsigned int i = 0; i < m2.rows; i++) {
        IndexAr[i] = &buf[i * m2.columns];
    }

    for (int i = 0; i < m2.rows; i++)
        for (int j = 0; j < m2.columns; j++)
            (*this)[i][j] = m2[i][j];
    return *this;
}

template<typename t>
void Matrix<t>::clear() {
    delete[] buf;
    delete[] IndexAr;
    rows = 0;
    columns = 0;
}

template<typename t>
Matrix<t>& Matrix<t>:: operator *= (const Matrix<t>& m2) {
    *this = (*this) * m2;
    return *this;
}

template<typename t>
Matrix<t>& Matrix<t>:: operator += (const Matrix<t>& m2) {
    *this = (*this) + m2;
    return *this;
}

template<typename t>
Matrix<t>& Matrix<t>:: operator *= (const t k) {
    *this = (*this) * k;
    return *this;
}

template<typename t>
Matrix<t> Matrix<t>::transp() {
    try {
        if (rows * columns > maxlen * maxlen)
            throw length_error("too big rows and columns");
    }
    catch (length_error& e) {
        throw e;
    }
    t* tempbuf = new t[rows * columns];
    for (int i = 0; i < columns; i++)
        for (int j = 0; j < rows; j++)
            tempbuf[i * columns + j] = (*this)[j][i];   
    Matrix Mat(columns , rows, tempbuf);

    return Mat;
}

template<typename t>
squareMatrix<t>::squareMatrix(int rowC, int columnC, t** array) {
    try {
        if (rowC == columnC) {
            columns = columnC;
            rows = rowC;

            if (rowC == 0 || columnC == 0) {
                IndexAr = nullptr;
                buf = nullptr;
                return;
            }

            try {
                if (rowC > maxlen)
                    throw std::length_error("too big");
                IndexAr = new t*[rowC];
            }
            catch (std::length_error& e)
            {
                throw e;
            }

            unsigned int size = rowC * columnC;
            setBuf(rowC * columnC);

            for (unsigned int i = 0; i < rowC; i++) {
                IndexAr[i] = &buf[i * columnC];
            }
            if (array != nullptr) {
                for (int i = 0; i < rowC; i++)
                    for (int j = 0; j < columnC; j++)
                        (*this)[i][j] = array[i][j];
            }
        }
        else
            throw std::length_error("bad size of square matrix");
    }
    catch (std::length_error &e)
    {
        throw e;
    }
}

template<typename t>
squareMatrix<t>::squareMatrix(int rowC, int columnC, t* array) {
    try {
        if (rowC == columnC) {
            columns = columnC;
            rows = rowC;

            if (rowC == 0 || columnC == 0) {
                IndexAr = nullptr;
                buf = nullptr;
                return;
            }               
            IndexAr = new t*[rowC];

            unsigned int size = rowC * columnC;
            setBuf(rowC * columnC);

            for (unsigned int i = 0; i < rowC; i++) {
                IndexAr[i] = &buf[i * columnC];
            }

            for (int i = 0; i < rowC; i++)
                for (int j = 0; j < columnC; j++)
                    (*this)[i][j] = array[i * columns + j];
        }
        else
            throw std::length_error(" bad size");
    }
    catch (std::length_error& e)
    {
        throw e;
    }
}

template<typename t>
squareMatrix<t>:: ~squareMatrix() {

}

template<typename t>
int Matrix<t>::getNumRows()const {
    return rows;
}

template<typename t>
int Matrix<t>::getNumColumns()const {
    return columns;
}

template<typename t>
squareMatrix<t>::squareMatrix(const Matrix<t>& m2):Matrix(m2) {
    if (m2.getNumRows() != m2.getNumColumns())
        throw std::length_error("not square matrix");    
}

template<typename t>
std::ostream& operator <<(std::ostream& output,const Matrix<t>& s) {
    for (unsigned int i = 0; i < s.rows; i++) {
        for (unsigned int j = 0; j < s.columns; j++)
            output << s[i][j] << ' ';
        output << std::endl;
    }
    return output;
}


template<typename t>
std::istream& operator >>(std::istream& in, Matrix<t>& s) {
    unsigned int row, column;
    in >> row;
    in >> column;
    t a;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++) {
            in >> a;
            s[i][j] = a;
        }
    return in;
}

template<typename t>
squareMatrix<t>& squareMatrix<t>:: operator = (const squareMatrix<t>& m2) {
    if (this->buf == m2.buf)
        return (*this);
    clear();
    columns = m2.columns;
    rows = m2.rows;

    if (m2.rows == 0 || m2.columns == 0) {
        IndexAr = nullptr;
        buf = nullptr;
        return *this;
    }

    IndexAr = new t*[m2.rows];
    unsigned int size = m2.rows * m2.columns;
    setBuf(m2.rows * m2.columns);

    for (unsigned int i = 0; i < m2.rows; i++) {
        IndexAr[i] = &buf[i * m2.columns];
    }

    for (int i = 0; i < m2.rows; i++)
        for (int j = 0; j < m2.columns; j++)
            (*this)[i][j] = m2[i][j];
    return *this;
}

template<typename t>
double squareMatrix<t>::Determinant(){
    // Gauss method, a two-dimensional array because we should always have double
    try {
        if (rows == columns) {
            int n = rows;
            if (n == 1)
                return (*this)[0][0];
            if (n == 2)
                return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];

            double** temp = new double*[n];
            for (int i = 0; i < n; i++)
                temp[i] = new double[n];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    temp[i][j] = (*this)[i][j];

            double kst;
            int p = 0;
            for (int i = 0; i < n - 1; i++)
            {
                int t = 1;
                while (temp[i][i] == 0)
                {
                    for (int j = 0; j < n; j++)
                    {
                        temp[i][j] = kst;
                        temp[i][j] = temp[i + t][j];
                        temp[i + t][j] = kst;
                    }
                    p++;
                    t++;
                }

                for (int k = i + 1; k < n; k++)
                {
                    kst = temp[k][i] / temp[i][i];
                    for (int j = 0; j < n; j++)
                        temp[k][j] -= temp[i][j] * kst;
                }
            }

            kst = pow(-1, p);
            for (int i = 0; i < n; i++)
                kst *= temp[i][i];



            for (int i = 0; i < n; i++)
                delete[] temp[i];
            delete[] temp;

            return kst;
        }
        else
            throw std::length_error("bad size");
    }
    catch (std::length_error& e)
    {
        throw e;
    }
}

template<typename t>
bool Matrix<t>::operator == (const Matrix<t>& m2) {
    if (m2.columns == this->columns && m2.rows == this->rows) {
        for (int i = 0; i < rows * columns; i++)
            if (this->buf[i] != m2.buf[i])
                return false;
        return true;
    }
    return false;
}


template<typename t>
squareMatrix<t> squareMatrix<t>::inverse(){
    if (this->Determinant() == 0)
        throw std::logic_error("Determinant = 0");
    
    int N = rows;
    squareMatrix e(*this);

    // initializing matrix e
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            e[i][j] = (i == j ? 1 : 0);

    // converting matrix to e
    for (int i = 0; i < N; i++)
    {
        // normalizing row (making first element = 1)
        double tmp = *(this->buf + i*N + i);
        for (int j = N - 1; j >= 0; j--)
        {
            e[i][j] /= tmp;
            *(this->buf + i*N + j) /= tmp;
        }
        // excluding i-th element from each row except i-th one
        for (int j = 0; j < N; j++)
            if (j != i)
            {
                tmp = *(this->buf + j * N + i);
                for (int k = N - 1; k >= 0; k--)
                {
                    e[j][k] -= e[i][k] * tmp;
                    *(this->buf + j * N + k) -= *(this->buf + i*N + k)*tmp;
                }
            }
    }
    // now e contains inverted matrix 
    return e;
}


template<typename t>
squareMatrix<t> squareMatrix<t>::getpow(const int n)const {
    squareMatrix m(*this);
    squareMatrix p(*this);
    for (int i = 1; i < n; i++)
        m *= p;

    return m;
}