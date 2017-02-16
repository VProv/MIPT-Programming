#include "Timetest.h"


double summing(int r,int itterations) {
    clock_t t1 = clock();
    BigInt a(r);
    for (int i = 0; i < itterations; i++)
        a = a + a;

    clock_t t2 = clock();

    double time = (t2 - t1) * 1.0 / CLOCKS_PER_SEC;

    return time;
}