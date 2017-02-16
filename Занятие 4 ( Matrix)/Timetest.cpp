#include "Timetest.h"

void Mcreate(int size) {
    Matrix a(size, size);
}

double Creating(int n) {
    clock_t t1 = clock();
    int size = 10000;
    for (int i = 0; i < n; i++);
        Mcreate(10000);

    clock_t t2 = clock();
    double time = (t2 - t1) * 1.0 / CLOCKS_PER_SEC;

    return time;
}

void Trans(Matrix& a) {
    a.transp();
}

double Transp(int n) {
    clock_t t1 = clock();
    int t = 100;
    Matrix::t** a = new Matrix::t*[t];
    for (int i = 0; i < t; i++)
        a[i] = new Matrix::t[t];

    for (int i = 0; i < t; i++)
        for (int j = 0; j < t; j++)
            a[i][j] = 5;
    Matrix m(t, t, a);
    for (int i = 0; i < n; i++)
        Trans(m);

    clock_t t2 = clock();
    double time = (t2 - t1) * 1.0 / CLOCKS_PER_SEC;

    return time;
}