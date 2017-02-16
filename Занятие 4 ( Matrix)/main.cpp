#include <iostream>
#include <cstdlib>
#include "MatrixLine.h"
#include "Timetest.h"

using namespace std;

int main() {

    cout << Creating(10) << endl;
    cout << Creating(100000) << endl;
    cout << Transp(100) << endl;

    int t = 10;
    Matrix::t** a = new Matrix::t*[t];
    for (int i = 0; i < t; i++)
        a[i] = new Matrix::t[t];

    for (int i = 0; i < t; i++)
        for (int j = 0; j < t; j++)
            a[i][j] = rand();

    for (int i = 0; i < t; i++) {
        for (int j = 0; j < t; j++)
            cout << a[i][j];
        cout << endl;
    }

    Matrix m(t,t,a);
    squareMatrix x(t, t, a);

    cout << m << endl;
    cout << x << endl;
    cout << m[5][5] * 2 << endl;
    for (int j = 0; j < t; j++)
        delete[] a[j];
    delete[] a;

    m = m * 2;
    cout << m << endl;
    m += m;

    cout << m << endl;
    m.transp();
    cout << m << endl;

    int l = 3;
    squareMatrix d(l, l);
    cout << " turn Matrix" << endl;
    for (int i = 0; i < l; i++)
        for (int j = 0; j < l; j++)
            cin >> d[i][j];
    cout << "Matrix" << endl << d << endl;
    cout << "Determ: " << d.Determinant() << endl;

    int gag;
    cin >> gag;
    return 0;
}