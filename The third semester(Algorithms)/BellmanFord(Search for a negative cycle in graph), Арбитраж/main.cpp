//Решение задачи арбитраж.(Поиск отрицательных циклов с помощью алгоритма Беллмана-Форда).
//Провилков Иван гр.593.

#include <iostream>
#include <cmath>
#include "Arbitration.h"

using namespace std;

int main() 
{
    //количество валют
    int n = 0;
    cin >> n;
    cout << endl;
    // Курсы обмена валют
    vector< vector<double> > edges(n, vector<double> (n));
    // Считываем курсы обмена валют(ребра графа).
    for( int i = 0; i < n; ++i ) {
        for( int j = 0; j < n; ++j ) {
            if( i == j ) {
                edges[i][j] = 1;// Считаем что курс обмена валюты самой к себе 1:1
            } else {
                double exchangeRate = 0;
                cin >> exchangeRate;
                // Чтобы складывать расстояния для Алгоритма Беллмана-Форда используем log: log(a*b) = log(a) + log(b)
                edges[i][j] = -std::log(exchangeRate); 
            }
        }
        cout << endl;
    }
    // Строим граф: n вершин, и edges(курсы обмена) - его ребра.
    COrGraph graph( n, edges );
    // Создаем класс нашего решения.
    CArbitration k( n );
    // Вызываем функцию решения на нашем графе.
    if( k.DoArbitration( graph ) ) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    cin >> n;
    return 0;
}