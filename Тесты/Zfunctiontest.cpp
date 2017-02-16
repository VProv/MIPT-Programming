#include <string>
#include <vector>
#include <algorithm>
// Восстановление строки по Z функции, через префикс функцию.
using std::string;
using std::vector;

// Класс Z-функции.
class CZfunction {

public:
    CZfunction( string* _st ) :st( _st ) {}
    CZfunction( const vector<int>& _ZArray ) : ZArray( _ZArray ) {};
    void UpDateZF() {
        ZArray.assign( st->size(), 0 );
        int left = 0;
        int right = 0;
        int n = st->size();
        for( int i = 1; i < n; ++i ) {
            ZArray[i] = std::max( 0, std::min( right - i, ZArray[i - left] ) );
            while( i + ZArray[i] < n && ( *st )[ZArray[i]] == ( *st )[i + ZArray[i]] )
                ZArray[i]++;
            if( i + ZArray[i] >= right ) {
                left = i;
                right = i + ZArray[i];
            }
        }
    }
    void createZst();
    const string& getZst()const { return Zst; }
    const vector<int>& getZF()const {
        return ZArray;
    }

private:
    string* st;
    vector<int> ZArray;
    string Zst;
};

#include<string>
#include<vector>
#include<algorithm>
#include<memory>

using std::vector;
using std::string;
class CZfunction;

// Класс префикс функции.
class CPrefunction {

public:
    CPrefunction( const string* _st ) : st( _st ), PreArray( ( *_st ).size() ) {};
    CPrefunction( const vector<int>& _PreArray ) : PreArray( _PreArray ) {};
    CPrefunction( const CZfunction& );
    void UpDatePF()
    {
        PreArray[0] = 0;
        int n = st->size();
        for( int i = 1; i < n; ++i ) {
            // Для поиска бордера наибольшей длины.
            int step = PreArray[i - 1];
            while( step > 0 && ( *st )[i] != ( *st )[step] ) {
                step = PreArray[step - 1];
            }
            if( ( *st )[i] == ( *st )[step] )
                ++step;
            PreArray[i] = step;
        }
        return;
    }

    // Построение строки по префикс функции.
    void createPreSt() {
        PreSt = 'a';
        int PreLen = PreArray.size();
        for( int i = 1; i < PreLen; ++i ) {
            for( char c = 'a'; c <= 'z'; ++c ) {
                // Предок, стоящий перед текущим символом. 
                int curParent = PreArray[i - 1];
                // Идем по предкам в нашей строке, чтобы в дальнейшем избежать наложений префиксов.
                while( curParent > 0 && c != PreSt[curParent] ) {
                    curParent = PreArray[curParent - 1];
                }
                // Если символ удовлетворяет отсутствию наложений(если 0), или продолжает текущий префикс, мы его ставим.
                if( ( c == PreSt[curParent] && PreArray[i] == curParent + 1 )
                    || ( PreArray[i] == curParent &&  c != PreSt[curParent] ) ) {
                    PreSt += c;
                    break;
                }
            }
        }
    }

    const vector<int>& getPreArray()const { return PreArray; }
    const string& getPreSt()const { return PreSt; }
private:
    const string* st;
    vector<int> PreArray;
    string PreSt;
};



// Класс конвертирующий префикс функцию в Z-функцию и обратно.
class CPreZConverter {

public:
    CPrefunction convertToPre( const CZfunction& z ) {
        const vector<int>& ZF = z.getZF();
        vector<int> PreF( ZF.size(), 0 );
        int size = ZF.size();
        for( int i = 1; i < size; ++i ) {
            for( int j = ZF[i] - 1; j >= 0; --j ) {
                if( PreF[i + j] > 0 )
                    break;
                else {
                    PreF[i + j] = j + 1;
                }
            }
        }
        CPrefunction temp( PreF );
        return temp;
    }
private:
};

void CZfunction::createZst() {
    CPrefunction temp( *this );
    temp.createPreSt();
    Zst = temp.getPreSt();
}


CPrefunction::CPrefunction( const CZfunction& z ) {
    CPreZConverter conv;
    *this = conv.convertToPre( z );
}

#include <iostream>

using namespace std;

int main() {

    vector<int> problem;
    int a = 0;
    while( cin >> a ) {
        problem.push_back( a );
    }

    CZfunction solver( problem );
    solver.createZst();
    string answer;
    answer = solver.getZst();
    cout << answer;

    return 0;
}