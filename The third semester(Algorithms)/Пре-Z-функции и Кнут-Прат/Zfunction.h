#pragma once
// ����� Z �������.
// ��������� ����. ��. 593.
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

// ����� Z-�������.
class CZfunction {

public:
    CZfunction( string* _st ) :st( _st ) {}
    CZfunction( const vector<int>& _ZArray ) : ZArray( _ZArray ) {};
    // ��������� �������� Z ������� � ����������� �� �������� �������� st.
    void UpDateZF();
    // ������ ������ ������������ ������������������� ������� �� Z �������. ����� �������������� � ������� �������.
    void createZst();
    const string& getZst()const { return Zst; }
    const vector<int>& getZF()const { return ZArray; }

private:
    // ��������� �� �������� ������.
    string* st;
    // ������ � Z ��������.
    vector<int> ZArray;
    // ������ ����������� �� Z �������.
    string Zst;
};