/**
 * @author Connor Marrs
 * @date June 20th, 2022
 *
 * This code is meant to be an efficient alternative to the simulation
 * of the DFGF in the Jupyter notebook.
 */

#define _USE_MATH_DEFINES

#include <float.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <fstream>

using namespace std;
using std::fstream;
using std::string;

const double s = .25; // parameter of the DFGF
const int num_nvals = 100; // number of n values to test
const int n_start = 1000; // start of n vals;
const int n_end = 1500; // end of n vals;
const int num_trials = 3000; // number of trials

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
 * 
 * 
 */
double compute_max(int n, vector<double> randvec) {
	// iterate over all angles 2pik/n
	double max = -DBL_MAX; // set max to smallest possible values computer knows
	for(int k=0; k<n; k++){
		// if we find larger value replace it
		if(dfgf(s,n,1.0*k,randvec) > max) {
			max = dfgf(s,n,1.0*k,randvec);
		}
	}
	return max;
}

/**
 * Computes an n-dimensional Gaussian vector. More specifically, we compute
 * a vector of n i.i.d. N(0,1) random variables.
 */
vector<double> gen_rand_vec(int size){
	// source: should guarantee that using std::normal_distribution
	// generates independent samples
	// https://stackoverflow.com/questions/21327249/how-to-generate
	//-uncorrelated-random-sequences-using-c
	// https://cplusplus.com/reference/random/normal_distribution/
	default_random_engine generator;
	
	vector<double> randvec(size,0);
	
	for (int i=0; i<size; ++i) {
		// for each n, use a new generator to guarantee independence
		normal_distribution<double> distribution(0.0,1.0);
		randvec[i] = distribution(generator);
	}
	
	return randvec;
}

void test_rand_vec(){
	int n = 12;
	vector<double> random = gen_rand_vec(n);
	cout << "Random Vector Sample" << '\n';
	for(int k=0; k<n; k++) {
		cout << random[k] << ',';
	}
}

void test_arithmetic(){
	int n = 10;
	vector<double> V = { 0.0, 3.4, .69, .72, .85, .43, -.43, -1.2, -1.16, 0.8 };
	//gen_rand_vec(num_vals);

	cout << "Vector Sample" << '\n';

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
 * Method borrowed from here:
 * https://stackoverflow.com/questions/27028226/python-linspace-in-c
 */
vector<int> linspace(int start, int end, int num) {
	vector<int> linspaced;
	
	if (num == 0) { 
		return linspaced; 
	}
	if (num == 1) {
		linspaced.push_back(start);
		return linspaced;
	}
	
	int delta = (int) round((end - start) / (1.0*(num - 1)));
	
	for(int i=0; i < num; ++i) {
		linspaced.push_back(start + delta * i);
	}
	
	return linspaced;
}

void test_linspace() {
	int start_ind = 10;
	int end_ind = 160;
	int num_ind = 32;

	linspace(start_ind, end_ind, num_ind);
}

void test_max() {
	
}

void sample() {
	vector<int> nvals = linspace(n_start, n_end, num_nvals); // set the nvals array
	
	// generate vector of values
	vector<double> exp_Max(num_nvals);

	// iterate over all values of n
	for(int k=0; k<num_nvals; k++) {
		double sum_Max = 0;
		// loop over the number of trials, add the maximum to our total
		for(int j=0; j<num_trials; j++) {
			sum_Max += compute_max(nvals[k], gen_rand_vec(nvals[k]));
		}
		// set expected value of M_k to be the empirical mean
		exp_Max[k] = sum_Max/num_trials;
		string filename("exp_sample.csv");
		fstream file;
		
		file.open(filename, std::ios_base::app | std::ios_base::in);
		if (file.is_open()) {
			file << nvals[k] << ',' << exp_Max[k] << '\n';
		}
	}
}

/**
 * The main file that runs the code
 */
int main() {
	/**
	 *	TESTING SECTION
	 */
	test_rand_vec();
	test_arithmetic();
	test_max();
	test_linspace();

	/**
	 *	EXPERIMENT SECTION
	 */
	sample();

	return 0;
}
