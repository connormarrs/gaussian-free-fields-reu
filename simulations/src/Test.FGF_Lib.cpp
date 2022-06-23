/**
 * Testing the simulations
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include "gtest/gtest.h"

using namespace std;

const double s = .25; // parameter of the DFGF
const int num_nvals = 500; // number of n values to test
const int n_start = 20; // start of n vals;
const int n_end = 10000; //end of n vals;

/**
 * Computes the rth eigenvalue for the nth discrete laplacian
 */

double eigval(double r, int n) {
	return pow(1.0*n,2.0)/(2.0*(pow(M_PI,2.0))) * (1.0-cos(2.0*M_PI*r/(1.0*n)));
}


double eigfcn(double r, int n, double k) {
	if(n%2==0 && r==((int)(n/2))) {
		return pow(-1.0, k);
	} else if(r<ceil((1.0*n)/2.0)) {
		return (M_SQRT2/2.0)*cos(2.0*M_PI*k*r/(1.0*n));
	} else {
		return (M_SQRT2/2.0)*sin(2.0*M_PI*k*r/(1.0*n));
	}
}

TEST (EigenTest, Values){
	EXPET_EQ ((-1.0*27.0)/(4.0*pow(M_PI,2)), eigval (5.0, 3))
}

int main(int argc, char ∗∗argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
