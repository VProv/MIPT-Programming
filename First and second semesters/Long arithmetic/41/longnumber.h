#pragma once
#include <iosfwd>

class istream;
class ostream;

// Класс длинной арифметики.
class LongNumber {
private:
	static const size_t base = 10000;
	static const size_t bufSize = 10000;
	static const int ten = 10;
	bool positive;
	size_t lgBase;
	int* buf;
	size_t size;
public:
	LongNumber();
	LongNumber( const int );
	LongNumber( const long long& );
	LongNumber( const unsigned long long& );
	LongNumber( const char* );
	LongNumber( const LongNumber& );
	~LongNumber();

	int& operator[]( const size_t );
	const int operator[]( const size_t ) const;

	LongNumber& operator=( const LongNumber& l );

	bool isPositive() const;

	void setSize( size_t );

	size_t getSize() const;
	size_t getBufSize() const;
	size_t getBase() const;

	friend std::istream& operator>>( std::istream&, LongNumber& );
	friend std::ostream& operator<<( std::ostream&, const LongNumber& );

	bool operator<( const LongNumber& ) const;
	bool operator>( const LongNumber& ) const;
	bool operator==( const LongNumber& ) const;
	bool operator!=( const LongNumber& ) const;

	LongNumber operator+( const LongNumber& ) const;
	LongNumber& operator+=( const LongNumber& );

	LongNumber operator-( const LongNumber& ) const;

	LongNumber operator*( const LongNumber& ) const;
	LongNumber nBasePower( const unsigned long ) const;
	LongNumber simpleMultiplication( const unsigned long ) const; 

	LongNumber operator/( const LongNumber& ) const;
	LongNumber getMiddle( const LongNumber&, const LongNumber& ) const;

	LongNumber sqrt() const;

	friend LongNumber nod( LongNumber, LongNumber );
};