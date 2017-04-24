#include <iostream>
#include <fstream>
#include <ctime>
#include "longnumber.h"

int main() {
	std::ofstream out;
	out.open("output.txt");

	LongNumber l1, l2, l;
	const size_t b = l1.getBase();
	clock_t t1, t2, t3;
	int k = 2; 
		l1.setSize( k );
		l2.setSize( k+2 );
		for( int i = 0; i < k; i++ ) {
			l1[i] = rand() % b;
			l2[i+2] = rand() % b;
		}
		l2[0] = rand() % b;
		l2[1] = rand() % b;
/*		t1 = clock();	
		for( int j = 0; j < 1000; j++ ) {
			l = l1 + l2;
		}
		t2 = clock();
		for( int j = 0; j < 1000; j++ ) {
			l = l1;
		}
		t3 = clock();
		out << "Base = " << b << " Size = " << k << " Time = " << ( 2 * t2 - t1 - t3 ) * 1. / CLOCKS_PER_SEC << '\n';
*/		
		std::cin >> l1;
		std::cin >> l2;
		out.close();
		out.open("output11.txt");
		out << l1 / l2;
		out << '\n';	
	
	
	
		out.close();
	return 0;
}
