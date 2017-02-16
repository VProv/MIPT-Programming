//������� ������ ��������.(����� ������������� ������ � ������� ��������� ��������-�����).
//��������� ���� ��.593.

#include <iostream>
#include <cmath>
#include "Arbitration.h"

using namespace std;

int main() 
{
    //���������� �����
    int n = 0;
    cin >> n;
    cout << endl;
    // ����� ������ �����
    vector< vector<double> > edges(n, vector<double> (n));
    // ��������� ����� ������ �����(����� �����).
    for( int i = 0; i < n; ++i ) {
        for( int j = 0; j < n; ++j ) {
            if( i == j ) {
                edges[i][j] = 1;// ������� ��� ���� ������ ������ ����� � ���� 1:1
            } else {
                double exchangeRate = 0;
                cin >> exchangeRate;
                // ����� ���������� ���������� ��� ��������� ��������-����� ���������� log: log(a*b) = log(a) + log(b)
                edges[i][j] = -std::log(exchangeRate); 
            }
        }
        cout << endl;
    }
    // ������ ����: n ������, � edges(����� ������) - ��� �����.
    COrGraph graph( n, edges );
    // ������� ����� ������ �������.
    CArbitration k( n );
    // �������� ������� ������� �� ����� �����.
    if( k.DoArbitration( graph ) ) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    cin >> n;
    return 0;
}