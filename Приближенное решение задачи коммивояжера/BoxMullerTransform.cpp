#include "BoxMullerTransform.h"

const double CBoxMullerTransform::pi = 3.1415926535;

void CBoxMullerTransform::generateNormalDistribution() {
    srand( clock() );
    for( int i = 0; i < pointsNumber; ++i ) {
        double r = 1.0*rand() / RAND_MAX;
        double phi = 1.0*rand() / RAND_MAX;
        double temp = sqrt( -2 * log( r ) );
        double cos = std::cos( 2 * pi * phi );
        Point p( mathExpect + sigma * cos * temp, mathExpect + sigma * ( 1 - cos * cos ) * temp );
        NormalDistribution.push_back( p );
    }
    return;
}