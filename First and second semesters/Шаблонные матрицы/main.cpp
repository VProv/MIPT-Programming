#include <iostream>
#include <cstdlib>
#include "Matrix.h"
#include "Tests.h"

using namespace std;

int main() {

    typedef float f;

    int t = 10;
    f** a = new f*[t];
    for (int i = 0; i < t; i++)
        a[i] = new f[t];

    for (int i = 0; i < t; i++)
        for (int j = 0; j < t; j++)
            a[i][j] = rand();

    for (int i = 0; i < t; i++) {
        for (int j = 0; j < t; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }
    try {
    Matrix<f> m(t, t, a);
    squareMatrix<f> x(t, t, a);
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

    m = m.transp();
    cout << m << endl;
    }
    catch (length_error& e)
    {
        cerr << e.what() << endl;
    }

    f* param = new f[9];
    param[0] = 3;
    param[1] = 2;
    param[2] = 1;
    param[3] = 1;
    param[4] = 1;
    param[5] = 1;
    param[6] = 1;
    param[7] = 2;
    param[8] = 0;

    squareMatrix<f> tempik(3, 3, param);
    cout << tempik.Determinant() << endl;
    cout << tempik << endl;
    tempik = tempik.getpow(2);
    cout << tempik << endl;

    tempik = tempik.inverse();
    cout << tempik << endl;

    summing(3, 3, 3);
    cout << endl;
    gettingpow(3, 3);
    cout << endl;
    transpowing(3, 3);
    cout << endl;

    tempik = tempik + tempik;
    int gag;
    cin >> gag;
    return 0;
}