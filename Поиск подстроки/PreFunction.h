#pragma once
// ����� ������� �������.
// ��������� ����. ��.593.
#include<string>
#include<vector>
#include<algorithm>
#include<memory>

using std::vector;
using std::string;
class CZfunction;

// ����� ������� �������.
class CPrefunction {

public:
    // �������������� ������, �� ������� ����� ����� ��������� ������� �������.
    CPrefunction( const string* _st ) : st( _st ), PreArray( ( *_st ).size() ) {};
    // �������������� ������� ������� �� �������.
    CPrefunction( const vector<int>& _PreArray ) : PreArray( _PreArray ) {};
    // ������ ������� ������� �� Z �������.
    CPrefunction( const CZfunction& );
    // ����������� ��� ��������� ������� ������. ��������� ������ � ������.
    // � ������� ������ ���� ��������� ������ ������� ������ �� ��������.
    CPrefunction( const string* _st, const string* p );
    // ������� ����������� �������� ������� �������, ������ �� ������ st.
    void UpDatePF();
    // ������� ������ �� ������� ������� �������, � ����������� ������������������ �������.
    void createPreSt();

    const vector<int>& getPreArray()const { return PreArray; }
    const string& getPreSt()const { return PreSt; }
private:
    const string* st;
    vector<int> PreArray;
    // ������ ���������� �� ������� �������.
    string PreSt;
};