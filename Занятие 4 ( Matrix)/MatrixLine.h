#pragma once
#include <assert.h>
#include <iostream>

class Matrix {
public:
    typedef float t;
protected:
    t** IndexAr;
    t* buf;
    unsigned int columns, rows; //count of columns and rows
public:
    Matrix(int rows = 0, int columns = 0, t** array = nullptr);
    Matrix(const Matrix&);
    Matrix(int rows, int columns, t* array);
    virtual ~Matrix();
    void setBuf(unsigned int i = 0);
    void setMatrix(int rows, int columns, t** array);
    void setMatrix(int rows, int columns, t* array);
    void clear();
    t* operator [](unsigned int index);
    t* operator [](unsigned int index) const;
    int getrows()const;
    int getcolumns()const;
    friend std::ostream& operator <<(std::ostream& out, Matrix& s);
    friend std::istream& operator >>(std::istream& in, Matrix& s);

    Matrix& operator = (const Matrix&);
    Matrix operator * (const Matrix&) const;
    Matrix operator + (const Matrix&) const;
    Matrix operator * (const t) const;
    friend Matrix operator * (const t, const Matrix&);
    Matrix& operator *= (const Matrix&);
    Matrix& operator += (const Matrix&);
    Matrix& operator *= (const t k);
    Matrix& transp();
};

class squareMatrix : public Matrix {
public:
    squareMatrix(int rows = 0, int columns = 0, t** array = nullptr);
    squareMatrix(int rows, int columns, t* array);
    squareMatrix(const Matrix&);
    virtual ~squareMatrix();
    t& operator = (const squareMatrix);
    double Determinant();
};