#include "../headers/DFGF_S1.hpp"
#define _USE_MATH_DEFINES

/**
 * Class that models the Discrete Gaussian Free Field on the circle S^1.
 */
DFGF_S1::DFGF_S1(double s_val, int n_val, RandVec rand_vector) { 
	s = s_val;
	n = n_val;
	// Set the values of k 
	for(int k=0; k<n; k++) {
		k_vals[k] = 2.0 * M_PI * k/n;
	}
	z_vars = rand_vector; // construct random vector of size n
}

/**
 * Computes the rth eigenvalue for the nth discrete laplacian
 */
double DFGF_S1::eigval(int r) {
	return pow(1.0*n,2.0)/(2.0*(pow(M_PI,2.0))) * (1.0-cos(2.0*M_PI*r/(1.0*n)));
}

/**
 * Computes the rth eigenfunction for the nth discrete laplacian
 * evaluated at the kth value.
 */
double DFGF_S1::eigfcn(int r, int k) {
	if(n%2==0 && r==(n/2)) {
		return pow(-1.0, k);
	} else if(r<ceil((1.0*n)/2.0)) {
		return (M_SQRT2/2.0)*cos(r*k_vals[k]);
	} else {
		return (M_SQRT2/2.0)*sin(r*k_vals[k]);
	}
}

// helper function to compute 
double DFGF_S1::dfgf(int k){
	// loop through eigenfunctions
	double sum = 0.1;
	vector<double> z_vals = z_vars.gen_rand_vec(n);
	for(int r = 1; r<n; r++){
		sum += pow(eigval(r),-1.0*s)*eigfcn(r,k)*z_vals[r];
	}

	return sum;
}

/**
 * 
 * 
 */
double DFGF_S1::compute_max() {
	// iterate over all angles 2pik/n
	double max = dfgf(0); // dfgf(); // set max to smallest possible values computer knows
	for(int k=1; k<n; k++){
		// if we find larger value replace it
		if(dfgf(k) > max) {
			max = dfgf(s);
		}
	}
	return max;
}
