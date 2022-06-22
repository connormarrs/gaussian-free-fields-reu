/**
 * @author Connor Marrs
 * @date June 20th, 2022
 *
 * This code is meant to be an efficient alternative to the simulation
 * of the DFGF in the Jupyter notebook.
 */

#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

const double s = .25; // parameter of the DFGF

/**
 * Computes the rth eigenvalue for the nth discrete laplacian
 */
double eigval(double r, int n) {
	return pow(1.0*n,2.0)/(2.0*(pow(M_PI,2.0))) * (1.0-cos(2.0*M_PI*r/(1.0*n)));
}

/**
 * Computes the rth eigenfunction for the nth discrete laplacian
 * evaluated at the kth value.
 */
double eigfcn(double r, int n, double k) {
	if(n%2==0 && r==((int)(n/2))) {
		return pow(-1.0, k);
	} else if(r<ceil((1.0*n)/2.0)) {
		return (M_SQRT2/2.0)*cos(2.0*M_PI*k*r/(1.0*n));
	} else {
		return (M_SQRT2/2.0)*sin(2.0*M_PI*k*r/(1.0*n));
	}
}

// helper function to compute 
double dfgf(double s, int n, double k, vector<double> randvec){
	// loop through eigenfunctions
	double sum = 0;
	for(int r = 1; r<n; r++){
		sum += pow(eigval(1.0*r,n),-1.0*s)*eigfcn(1.0*r, n, k)*randvec[r];
	}

	return sum;
}

/**
 * Computes an n-dimensional Gaussian vector. More specifically, we compute
 * a vector of n i.i.d. N(0,1) random variables.
 */
vector<double> gen_rand_vec(int size){
	// TODO: figure out how to seed this so things are uncorrelated
	default_random_engine generator;
	normal_distribution<double> distribution(0.0,1.0);
	
	vector<double> randvec(size,0);
	
	for (int i=0; i<size; ++i) {
		 randvec[i] = distribution(generator);
	}
	
	return randvec;
}

void test_arithmetic(){
	int n = 10;
	vector<double> V = { 0.0, 3.4, .69, .72, .85, .43, -.43, -1.2, -1.16, 0.8 };
	//gen_rand_vec(num_vals);

	cout << "Random Vector Sample" << '\n';

	for(int k=0; k<n; k++) {
		cout << V[k] << ',';
	}

	cout << '\n' << "3rd Eigenfunction" << '\n';
	
	for(int k=0; k<n; k++) {
		cout << eigfcn(3.0,n,1.0*k)  << ',';
	}

	cout << '\n' << "5rd Eigenfunction" << '\n';
	
	for(int k=0; k<n; k++) {
		cout << eigfcn(5.0,n,1.0*k)  << ',';
	}

	cout << '\n' << "7th Eigenfunction" << '\n';
	
	for(int k=0; k<n; k++) {
		cout << eigfcn(7.0,n,1.0*k)  << ',';
	}

	cout <<'\n' << "Eigenvalues" << '\n';
	
	for(int r=0; r<n; r++) {
		cout << eigval(r,1.0*n)  << ',';
	}

	cout <<'\n' << "Eigenvalues to -.25" << '\n';
	
	for(int r=0; r<n; r++) {
		cout << pow(eigval(1.0*r,n),-1.0*s)  << ',';
	}

	cout << '\n' << "Values of DFGF(s)" << '\n';
	
	for(int k=0; k<n; k++) {
		cout << dfgf(s,n,1.0*k,V)  << ',';
	}
}

/**
 * The main file that runs the code
 */
int main() {
	const int num_vals = 10; // number of n values to test
	const int num_trials = 3000; // number of trials to run for each n

	test_arithmetic();

	return 0;

}
