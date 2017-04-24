// Решение задачи "Расстояние Хэмминга"
// Провилков Иван гр.593.
#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include "Hamming.h"

using std::vector;
using std::deque;
using std::pair;
using std::max;
using std::min;
using std::string;

using namespace std;

int main()
{
    CReader test;
    test.ReadTest();
    CNetwork network( test );
    cout << network.GetMaxFlow() << std::endl;
    network.PrintRelations();
    int n;
    cin >> n;
    return 0;
}