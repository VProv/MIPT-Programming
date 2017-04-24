#include "longnumber.h"
#include <iostream>

LongNumber::LongNumber() {
	buf = new int[bufSize];

	for( size_t i = 0; i < bufSize; i++ ) {
		buf[i] = 0;
	}
	size = 0;
	size_t b = base;
	b--;
	while( b > 0 ) {
		b /= ten;
		lgBase++;
	}
	positive = true;
}

LongNumber::LongNumber( const int number ) {
	size_t b = base;
	int num = number;
	b--;
	if( num >= 0 ) {
		positive = true;
	}
	else {
		positive = false;
	}
	while( b > 0 ) {
		b /= ten;
		lgBase++;
	}
	buf = new int[bufSize];
	size = 0;
	if( num == 0 ) {
		buf[0] = 0;
		size++;
	}
	else {
		while( num > 0 ) {
			buf[size] = num % base;
			num /= base;
			size++;
		}
	}
	for( size_t i = size; i < bufSize; i++ ) {
		buf[i] = 0;
	}
}

LongNumber::LongNumber( const long long& number ) {
	size_t b = base;
	long long num = number;
	b--;
	if( num >= 0 ) {
		positive = true;
	}
	else {
		positive = false;
	}
	while( b > 0 ) {
		b /= ten;
		lgBase++;
	}
	buf = new int[bufSize];
	size = 0;
	if( num == 0 ) {
		buf[0] = 0;
		size++;
	}
	else {
		while( num > 0 ) {
			buf[size] = num % base;
			num /= base;
			size++;
		}
	}
	for( size_t i = size; i < bufSize; i++ ) {
		buf[i] = 0;
	}
}

LongNumber::LongNumber( const unsigned long long& number ) {
	size_t b = base;
	unsigned long long num = number;
	b--;
	positive = true;
	while( b > 0 ) {
		b /= ten;
		lgBase++;
	}
	buf = new int[bufSize];
	size = 0;
	if( num == 0 ) {
		buf[0] = 0;
		size++;
	}
	else {
		while( num > 0 ) {
			buf[size] = num % base;
			num /= base;
			size++;
		}
	}
	for( size_t i = size; i < bufSize; i++ ) {
		buf[i] = 0;
	}
}

int charToInt( char c ) {
	switch ( c ) {
	case '0' :
		return 0;
		break;
	case '1' :
		return 1;
		break;
	case '2' :
		return 2;
		break;
	case '3' :
		return 3;
		break;
	case '4' :
		return 4;
		break;
	case '5' :
		return 5;
		break;
	case '6' :
		return 6;
		break;
	case '7' :
		return 7;
		break;
	case '8' :
		return 8;
		break;
	case '9' :
		return 9;
		break;
	default:
		return 0;
	};
}

LongNumber::LongNumber( const char* ch ) {
	buf = new int[bufSize];
	size_t numberOfCurrentCh = 0;
	if( ch[0] == '-' ) {
		positive = false;
		numberOfCurrentCh = 1;
	}
	else {
		positive = true;
	}

	size_t b = base;
	b--;
	lgBase = 0;
	while( b > 0 ) {
		b /= ten;
		lgBase++;
	}

	int currentDigit;
	size_t length = 0;
	while( ch[length] != '\0' ) {
		length++;
	}
	length--;
	if( !positive ) {
		length--;
	}
	size = ( length + lgBase - 1 ) / lgBase;
	size_t first = length % lgBase;
	if( first == 0 ) {
		first = lgBase;
	}
	currentDigit = 0;
	for( size_t i = 0; i < first; i++ ) {
		currentDigit = currentDigit * 10 + charToInt( ch[numberOfCurrentCh] );
		numberOfCurrentCh++;
	}
	buf[size-1] = currentDigit;
	for( size_t i = 0; i < size - 1; i++ ) {
		currentDigit = 0;
		for( size_t j = 0; j < lgBase; j++ ) {
			currentDigit = currentDigit * 10 + charToInt( ch[numberOfCurrentCh] );
			numberOfCurrentCh++;
		}
		buf[size-2-i] = currentDigit;
	}
	for( size_t i = size; i < bufSize; i++ ) {
		buf[i] = 0;
	}
}

LongNumber::LongNumber( const LongNumber& l ) {
	buf = new int[bufSize];
	size = l.size;
	positive = l.positive;
	for( size_t i = 0; i < bufSize; i++ ) {
		buf[i] = l[i];;
	}
}

LongNumber::~LongNumber() {
	size = 0;
	delete [] buf;
	buf = nullptr;
}

int& LongNumber::operator[]( const size_t index ) {
	return buf[index];
}

const int LongNumber::operator[]( const size_t index ) const {
	return buf[index];
}

LongNumber& LongNumber::operator=( const LongNumber& l ) {
	if( this == &l ) {
		return *this;
	}
	size = l.size;
	positive = l.positive;
	for( size_t i = 0; i < size; i++ ) {
		buf[i] = l[i];
	}
	for( size_t i = size; i < bufSize; i++ ) {
		buf[i] = 0;
	}
	return *this;
}

bool LongNumber::isPositive() const {
	return positive;
}

void LongNumber::setSize( size_t index ) {
	size = index;
}

size_t LongNumber::getSize() const {
	return size;
}

size_t LongNumber::getBufSize() const {
	return bufSize;
}

size_t LongNumber::getBase() const {
	return base;
}

std::istream& operator>>( std::istream& in, LongNumber& l ) {
	char c = '0';
	size_t index = 0;
	char* ch = new char[l.getBufSize()];
	while( c != '\n' ) {
		in.get(c);
		ch[index] = c;
		index++;
	}
	ch[index] = '\0';
	LongNumber result( ch );
	delete [] ch;
	l = result;
	return in;
}

std::ostream& operator<<( std::ostream& out, const LongNumber& l ) {
	if( !l.isPositive() ) {
		out << '-';
	}
	size_t size = l.getSize();
	out << l[size-1];
	for( size_t i = 1; i < size; i++ ) {
		size_t b = l.getBase();
		b /= 10;
		while( b > 0 ) {
			if( b > l[size-i-1] ) {
				out << '0';
			}
			b /= 10;
		}
		if( l[size-i-1] != 0 ) {
			out << l[size-i-1];
		}
	}
	return out;
}

bool LongNumber::operator==( const LongNumber& l ) const {
	if( size != l.size ) {
		return false;
	}
	else {
		for( size_t i = 0; i < size; i++ ) {
			if( buf[i] != l[i] ) {
				return false;
			}
		}
		return true;
	}
}

bool LongNumber::operator!=( const LongNumber& l ) const {
	if( size != l.size ) {
		return true;
	}
	else {
		for( size_t i = 0; i < size; i++ ) {
			if( buf[i] != l[i] ) {
				return true;
			}
		}
		return false;
	}
}

bool LongNumber::operator<( const LongNumber& l ) const {
	if( size > l.size ) {
		return false;
	}
	else if( size < l.size ) {
		return true;
	}
	else {
		for( size_t i = 0; i < size; i++ ) {
			if( buf[size-i-1] > l[size-i-1] ) {
				return false;
			}
			else if( buf[size-i-1] < l[size-i-1] ) {
				return true;
			}
		}
		return false;
	}
}

bool LongNumber::operator>( const LongNumber& l ) const {
	if( size < l.size ) {
		return false;
	}
	else if( size > l.size ) {
		return true;
	}
	else {
		for( size_t i = 0; i < size; i++ ) {
			if( buf[size-i-1] < l[size-i-1] ) {
				return false;
			}
			else if( buf[size-i-1] > l[size-i-1] ) {
				return true;
			}
		}
		return false;
	}
}

LongNumber LongNumber::operator+( const LongNumber& l ) const {
	if( ( positive && l.positive ) || ( !positive && !l.positive ) ) {
		LongNumber result( *this );
		for( size_t i = 0; i < l.size; i++ ) {
			result[i] += l[i];
			if( result[i] >= base ) {
				result[i+1]++;
				result[i] -= base;
			}
		}
		if( result.size < l.size ) {
			result.size = l.size;
		}
		if( result[result.size] > 0 ) {
			result.size++;
		}
		return result;
	}
	else if( *this > l ) {
		LongNumber result( *this );
		for( size_t i = 0; i < l.size; i++ ) {
			result[i] -= l[i];
			if( result[i] < 0 ) {
				result[i] += base;
				result[i+1]--;
			}
		}
		size_t i = l.size;
		while( result[i] < 0 ) {
			result[i] += base;
			i++;
			result[i]--;
		}
		while( result[result.size-1] == 0 ) {
			result.size--;
		}
		return result;
	}
	else {
		LongNumber result( l );
		for( size_t i = 0; i < size; i++ ) {
			result[i] -= buf[i];
			if( result[i] < 0 ) {
				result[i] += base;
				result[i+1]--;
			}
		}
		size_t i = size;
		while( result[i] < 0 ) {
			result[i] += base;
			i++;
			result[i]--;
		}
		while( result[result.size] == 0 ) {
			result.size--;
		}
		return result;
	}
}

LongNumber& LongNumber::operator+=( const LongNumber& l ) {
	if( ( positive && l.positive ) || ( !positive && !l.positive ) ) {
		for( size_t i = 0; i < l.size; i++ ) {
			buf[i] += l[i];
			if( buf[i] >= base ) {
				buf[i+1]++;
				buf[i] -= base;
			}
		}
		if( size < l.size ) {
			size = l.size;
		}
		if( buf[size] > 0 ) {
			size++;
		}
		return *this;
	}
	else if( *this > l ) {
		for( size_t i = 0; i < l.size; i++ ) {
			buf[i] -= l[i];
			if( buf[i] < 0 ) {
				buf[i] += base;
				buf[i+1]--;
			}
		}
		size_t i = l.size;
		while( buf[i] < 0 ) {
			buf[i] += base;
			i++;
			buf[i]--;
		}
		while( buf[size] == 0 ) {
			size--;
		}
		return *this;
	}
	else {
		positive = l.positive;
		for( size_t i = 0; i < size; i++ ) {
			buf[i] = l[i] - buf[i];
			if( buf[i] < 0 ) {
				buf[i] += base;
				buf[i+1]++;
			}
		}
		for( size_t i = size; i < l.size; i++ ) {
			buf[i] = l[i];
		}
		size = l.size;
		while( buf[size] == 0 ) {
			size--;
		}
		return *this;
	}
}

LongNumber LongNumber::operator-( const LongNumber& l ) const {
	LongNumber m( l );
	if( m.positive == true ) {
		m.positive = false;
	}
	else {
		m.positive = true;
	}
	return ( *this + m );
}

LongNumber LongNumber::operator*( const LongNumber& l ) const {
	LongNumber result( 0 );
	for( size_t i = 0; i < l.size; i++ ) {
		result += ( this->simpleMultiplication( l[i] ) ).nBasePower( i );
	}
	return result;
}

LongNumber LongNumber::nBasePower( const unsigned long s ) const {
	LongNumber result;
	for( size_t i = 0; i < size; i++ ) {
		result[i+s] = buf[i];
	}
	result.size = size + s;
	result.positive = positive;
	return result;
}	

LongNumber LongNumber::simpleMultiplication( const unsigned long n ) const {
	unsigned long r = 0;
	unsigned long d = 0;
	LongNumber result( *this );
	for( size_t i = 0; i < size; i++ ) {
		r = buf[i] * n;
		result[i] = r % base;
		result[i] += d;
		d = r / base;
	}
	if( d > 0 ) {
		result[result.size] += d;
		result.size++;
	}
	return result;
}

LongNumber LongNumber::operator/( const LongNumber& div ) const {
	LongNumber left(0), right(*this), middle, res;
	while( left < ( right - 1 ) ) {
		middle = getMiddle( left, right );
		res = middle * div;
//		std::cout << left << "  " << middle << "  " << right  << "  " << res << "  " << div << std::endl;
		if( res == *this ) {
			return middle ;
		}
		else if( res > *this ) {
			right = middle;
		}
		else {
			left = middle;
		}
	}
	return left;
}

LongNumber LongNumber::getMiddle( const LongNumber& left, const LongNumber& right ) const {
	LongNumber result( left + right );
	for( size_t i = 0; i < result.size - 1; i++ ) {
		if( result[result.size-i-1] % 2 == 1 ) {
			result[result.size-i-2] += base;
		}
		result[result.size-i-1] /= 2;
	}
	result[0] /= 2;
	if( result[result.size - 1] == 0 ) {
		result.size--;
	}
	return result;
}

LongNumber LongNumber::sqrt() const {
	LongNumber left(1), right(1), middle, res;
	left = left.nBasePower( ( this->size - 1 ) / 2 );
	right = right.nBasePower( ( this->size + 1 ) / 2 );
	while( left < ( right - 1 ) ) {
		middle = getMiddle( left, right );
		res = middle * middle;
//		std::cout << left << "  " << middle << "  " << right  << "  " << res  << std::endl;
		if( res == *this ) {
			return middle ;
		}
		else if( res > *this ) {
			right = middle;
		}
		else {
			left = middle;
		}
	}
	return left;
}

LongNumber nod( LongNumber l1, LongNumber l2 ) {
	while( l1 != l2 ) {
		if( l1 > l2 ) {
			l1 = l1 - ( l1 / l2 ) * l2;
		}
		else {
			l2 = l2 - ( l2 / l1 ) * l1;
		}
	}
	return l1;
}