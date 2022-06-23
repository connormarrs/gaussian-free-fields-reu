//code from sample_max.cpp rewritten as a class (consts are passed into the constructor)
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

class SampleMax {
    public:
        SampleMax(double s, int numvals, int n_start, int n_end);
        //Computes the rth eigenvalue for the nth discrete laplacian
        double eigval(double r, int n);
        //Computes the rth eigenfunction for the nth discrete laplacian
        // evaluated at the kth value.
        double eigfcn(double r, int n, double k);
        // helper function to compute 
        double dfgf(double s, int n, double k, vector<double> randvec);
        //computes the max of the dfgf over theta for a given omega (randvec is fixed)
        double compute_max(int n, vector<double> randvec);
        //computes the sample mean of the max of m nth degree dfgfs
        double compute_smmax(int n, vector<double> randvec, int m);
        //computes the sample variance of the max of m nth degree dfgfs 
        double compute_svmax(int n, vector<double> randvec, int m);

        //getters for the private variables
        double get_s0();
        int get_numvals0();
        int get_n_start0();
        int get_n_end0();
    private:
        double s0; //paramater for the discrete fractional gaussian field (this generally stays fixed so we can observe the limiting behaviors)
        int numvals0; // total number of n values to test
        int n_start0; // start of n values 
        int n_end0; // end of n values
};
SampleMax::SampleMax(double s, int numvals, int n_start, int n_end) {
    s0=s;
    numvals0=numvals;
    n_start0=n_start;
    n_end0=n_end;
}
double SampleMax::eigval(double r, int n) {
	return pow(1.0*n,2.0)/(2.0*(pow(M_PI,2.0))) * (1.0-cos(2.0*M_PI*r/(1.0*n)));
}
double SampleMax::eigfcn(double r, int n, double k) {
	if(n%2==0 && r==((int)(n/2))) {
		return pow(-1.0, k);
	} else if(r<ceil((1.0*n)/2.0)) {
		return (M_SQRT2/2.0)*cos(2.0*M_PI*k*r/(1.0*n));
	} else {
		return (M_SQRT2/2.0)*sin(2.0*M_PI*k*r/(1.0*n));
	}
}
double SampleMax::dfgf(double s, int n, double k, vector<double> randvec){
	// loop through eigenfunctions
	double sum = 0;
	for(int r = 1; r<n; r++){
		sum += pow(eigval(1.0*r,n),-1.0*s)*eigfcn(1.0*r, n, k)*randvec[r];
	}

	return sum;
}
double SampleMax::compute_max(int n, vector<double> randvec) {
	// iterate over all angles 2pik/n
	double max = dfgf(s0,n, 1.0,randvec); // set max to smallest possible values computer knows (replacement of -DBL_MAX is okay cause we check all values anyway)
	for(int k=0; k<n; k++){
		// if we find larger value replace it
		if(dfgf(s0, n, 1.0*k,randvec) > max) {
			max = dfgf(s0, n, 1.0*k,randvec);
		}
	}
	return max;
}
double SampleMax::compute_smmax(int n, vector<double> randvec, int m){
    return 0.0;
}
double SampleMax::compute_svmax(int n, vector<double> randvec, int m){
    return 0.0;
}

