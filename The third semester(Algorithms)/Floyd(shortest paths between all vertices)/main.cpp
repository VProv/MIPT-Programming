#include <fstream>
#include <vector>
#include "Floyd.h"

using namespace std;

int main() {
    // Окрываем файл для считывания.
    ifstream InFile( "floyd.in" );
    // Открываем файл для записи.
    ofstream OutFile( "floyd.out" );
    // Количество вершин.
    int n = 0;
    InFile >> n;
    // Граф
    vector<vector<double> > Graph( n, vector<double>( n ) );
    for( int i = 0; i < n; ++i )
        for( int j = 0; j < n; ++j ) {
            InFile >> Graph[i][j];
        }
    // Создаем ориентированный граф.
    COrGraph OrGraph( n, Graph );
    // Создаем класс алгоритма Флойда.
    CFloyd Floyd( OrGraph );
    const vector<vector<double> >& result = Floyd.performFloyd();
    for( int u = 0; u < n; ++u ) {
        for( int v = 0; v < n; ++v ) {
            OutFile << result[u][v] << ' ';
        }
        OutFile << endl;
    }
    // Закрываем файлы.
    InFile.close();
    OutFile.close();
    return 0;
}