#include <vector>
#include <string>
#include <algorithm>
#include <exception>

using std::vector;
using std::string;

class User {

public:
    User( const string& _LName, const string& _FName, const string& _PaName ) :
        LName( _LName ), FName( _FName ), PaName( _PaName ) {};
    void addInConv( int minuts ) {
        inConv += minuts;
    }
    void addExConv( int minutes ) {
        exConv += minutes;
    }
    bool operator == ( const User& right ) {
        return this->FName == right.FName && this->LName == right.LName && this->PaName == right.PaName;
    }
    bool operator < ( const User& right ) {
        return this->LName < right.LName || ( this->LName == right.LName && this->FName < right.FName ) ||
            ( this->LName == right.LName && this->FName == right.FName && this->PaName < right.PaName );
    }
    // �������.
    string LName;
    // ���.
    string FName;
    // ��������.
    string PaName;
    // �����.
    string number;
    // ���������� ���������. (� �������).
    int inConv;
    // �������.
    int exConv;
private:
};

class Book {

public:
    Book() = default;
    void addUser( const User& a ) {
        // �������� �� �� ��� ��� ��� ��� ���� ������.
        if( std::find(data.begin(),data.end(),a) == data.end() )
            data.push_back( a );
    }
    User& getUser( const string& Fname, const string& LName, const string& PaName ) {
        for( int i = 0; i < data.size(); ++i ) {
            if( data[i].FName == Fname && data[i].LName == LName && data[i].PaName == PaName ) {
                return  data[i];
            }
        }
        throw std::invalid_argument( "No Name" );
    }
    // ���������� ������ ���, � ���� �������� ���������� �����.
    vector<User> InOverLimit( int max )const {
        vector<User> answer;
        for( int i = 0; i < data.size(); ++i ) {
            if( data[i].inConv > max )
                answer.push_back( data[i] );
        }
        return answer;
    }
    // ���������� ������ ��� ��� ����������� ������� ������.
    vector<User> exUsers()const {
        vector<User> answer;
        for( int i = 0; i < data.size(); ++i ) {
            if( data[i].exConv > 0 )
                answer.push_back( data[i] );
        }
        return answer;
    }
  
    // ���������� � ���������� �������.
    void makeOrder() {
        std::sort( data.begin(), data.end() );
    }
    // ���������� ��������.
    const vector<User>& getData()const {
        return data;
    }
private:
    vector<User> data;
};

int main() {
    // ������ ����������)))
    
    Book book;
    // ������ ������
    //book.addUser(...)
    // ��������� �������� ������� ���������� � �������
    //book.getUser( ... ).addInConv;
    //book.getUser( ... ).addExConv;
    // ���������� ������ � ������� �� ����� 1
    //book.InOverLimit()
    // ���������� ������ � ������� �� ���� 2
    //book.exUsers()
    // ����� 3
    book.makeOrder();
    book.getData();

    return 0;
}