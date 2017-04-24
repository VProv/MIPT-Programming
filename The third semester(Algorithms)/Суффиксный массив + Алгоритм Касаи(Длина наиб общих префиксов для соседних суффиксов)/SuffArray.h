#pragma once
// ����� ����������� �������.
// ��������� ����. ��. 593.
#include <algorithm>
#include <vector>
#include <string>

using std::vector;
using std::string;
// ����� ����������� �������.
// ���������� �� O(nlogn), ������� ���������� ����������� �������. ���������� ��������� ���������� � 0.
class CSuffArray {

public:
    CSuffArray( const string& _st ) : st( _st ) { createSuffArray(); };

    // ��������� ���������� ������.
    // ���������� �� O(nlogn) �������� ����� ������� � ����������.
    void createSuffArray();

    // ���������� LCP. �������� ����� (�������� ���������� ����� ��������� 
    // ���� �������� ���������, ��������������� � ������������������ �������).
    vector<int> buildLCP( const string& str, const vector<int>& suffArr );

    const string& getSt()const { return st; }
    const vector<int>& getSuffArray()const { return SuffArray; }
private:
    // ���������� ����� ����������� ������� � ������.
    void sortingCycleShifts( vector<int>& answer );
    const string& st;
    vector<int> SuffArray;
};