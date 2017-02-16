#pragma once
#include "Matrix.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
void summing(const int NumRows,const int NumColumns,const int iterations) {
    typedef float f;
    srand(time(NULL));
    f** a = new f*[NumRows];
    for (int i = 0; i < NumRows; i++)
        a[i] = new f[NumRows];
    for (int i = 0; i < NumRows; i++)
        for (int j = 0; j < NumColumns; j++)
            a[i][j] = rand();
    for (int i = 0; i < NumRows; i++) {
        for (int j = 0; j < NumColumns; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }

    try {
        Matrix<f> m(NumRows, NumColumns, a);
        for (int i = 0; i < iterations; i++)
            m = m + m;
        cout << m;
    }
    catch (length_error& e)
    {
        cerr << e.what() << endl;
    }
}

void gettingpow(const int NumRows, const int iterations) {
    typedef float f;
    int NumColumns = NumRows;
    srand(time(NULL));
    f** a = new f*[NumRows];
    for (int i = 0; i < NumRows; i++)
        a[i] = new f[NumRows];
    for (int i = 0; i < NumRows; i++)
        for (int j = 0; j < NumColumns; j++)
            a[i][j] = rand();
    for (int i = 0; i < NumRows; i++) {
        for (int j = 0; j < NumColumns; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }

    try {
        squareMatrix<f> m(NumRows, NumColumns, a);
        m.getpow(iterations);
        cout << m;
    }
    catch (length_error& e)
    {
        cerr << e.what() << endl;
    }
}

void transpowing(const int NumRows, const int iterations) {
    typedef float f;
    int NumColumns = NumRows;
    srand(time(NULL));
    f** a = new f*[NumRows];
    for (int i = 0; i < NumRows; i++)
        a[i] = new f[NumRows];
    for (int i = 0; i < NumRows; i++)
        for (int j = 0; j < NumColumns; j++)
            a[i][j] = rand();
    for (int i = 0; i < NumRows; i++) {
        for (int j = 0; j < NumColumns; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }

    try {
        Matrix<f> m(NumRows, NumColumns, a);
        for (int i = 0; i < iterations; i++)
            m = m.transp();
        cout << m;
    }
    catch (length_error& e)
    {
        cerr << e.what() << endl;
    }
}