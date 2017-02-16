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
    // Фамилия.
    string LName;
    // Имя.
    string FName;
    // Отчество.
    string PaName;
    // Номер.
    string number;
    // Внутренние разговоры. (В минутах).
    int inConv;
    // Внешние.
    int exConv;
private:
};

class Book {

public:
    Book() = default;
    void addUser( const User& a ) {
        // Проверка на то что тут уже был этот объект.
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
    // Возвращает массив тех, у кого привышен внутренний лимит.
    vector<User> InOverLimit( int max )const {
        vector<User> answer;
        for( int i = 0; i < data.size(); ++i ) {
            if( data[i].inConv > max )
                answer.push_back( data[i] );
        }
        return answer;
    }
    // Возвращает массив тех кто пользовался внешней связью.
    vector<User> exUsers()const {
        vector<User> answer;
        for( int i = 0; i < data.size(); ++i ) {
            if( data[i].exConv > 0 )
                answer.push_back( data[i] );
        }
        return answer;
    }
  
    // Сортировка в алфавитном порядке.
    void makeOrder() {
        std::sort( data.begin(), data.end() );
    }
    // Возвращает значения.
    const vector<User>& getData()const {
        return data;
    }
private:
    vector<User> data;
};

int main() {
    // Сделай считывание)))
    
    Book book;
    // Ложить нового
    //book.addUser(...)
    // Добавлять значения звонков внутренние и внешние
    //book.getUser( ... ).addInConv;
    //book.getUser( ... ).addExConv;
    // Возвращает вектор с ответом на пункт 1
    //book.InOverLimit()
    // Возвращает вектор с ответом на пунк 2
    //book.exUsers()
    // Пункт 3
    book.makeOrder();
    book.getData();

    return 0;
}