#include <fstream>
#include <vector>
#include "Floyd.h"

using namespace std;

int main() {
    // �������� ���� ��� ����������.
    ifstream InFile( "floyd.in" );
    // ��������� ���� ��� ������.
    ofstream OutFile( "floyd.out" );
    // ���������� ������.
    int n = 0;
    InFile >> n;
    // ����
    vector<vector<double> > Graph( n, vector<double>( n ) );
    for( int i = 0; i < n; ++i )
        for( int j = 0; j < n; ++j ) {
            InFile >> Graph[i][j];
        }
    // ������� ��������������� ����.
    COrGraph OrGraph( n, Graph );
    // ������� ����� ��������� ������.
    CFloyd Floyd( OrGraph );
    const vector<vector<double> >& result = Floyd.performFloyd();
    for( int u = 0; u < n; ++u ) {
        for( int v = 0; v < n; ++v ) {
            OutFile << result[u][v] << ' ';
        }
        OutFile << endl;
    }
    // ��������� �����.
    InFile.close();
    OutFile.close();
    return 0;
}