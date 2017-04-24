#pragma once
// ����� �������������� �����-�������, ��� �������� ����������� ������������� ����� �� ���������.
#include <cmath>
#include <vector>
#include <ctime>

using std::vector;

class CBoxMullerTransform {

public:
    // ����� �����.
    class Point {
    public:
        double x;
        double y;
        Point( double _x, double _y ) 
        {
            x = _x;
            y = _y;
        }
        double getDistance( const Point& a ) 
        {
            return sqrt( ( x - a.x ) * ( x - a.x ) + ( y - a.y ) * ( y - a.y ) );
        }
    };

    CBoxMullerTransform(int number,double _mathExpect = 0,double _sigma = 1):
        NormalDistribution() {
        pointsNumber = number; mathExpect = _mathExpect; sigma = _sigma;
    }
    void generateNormalDistribution();
    // ���������� ��������� �������������� �����.
    const vector<Point>& getDistribution()const 
    {
        return NormalDistribution;
    }
    vector<Point> getVectorDistribution()const 
    {
        return NormalDistribution;
    }
private:
    int pointsNumber;
    // �������������� ��������.
    double mathExpect;
    // ���������.
    double sigma;
    const static double pi;
    vector<Point> NormalDistribution;
};