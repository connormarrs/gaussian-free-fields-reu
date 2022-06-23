#include "../headers/RandVec.hpp"

/**
 * Constructor for the Sampler class
 */
RandVec::RandVec(int n) {
	len_vec = n;
	// instantiate a vector of length n of i.i.d. gaussians
	for (int i=0; i<n; ++i) {
		// for each n, use a new generator to guarantee independence
		normal_distribution<double> distribution(0.0,1.0);
		gaussian_vector[i] = distribution;
	}
}

/**
 *  gen_rand_vec
 */
vector<double> RandVec::gen_rand_vec(int size){
	// source: should guarantee that using std::normal_distribution
	// generates independent samples
	// https://stackoverflow.com/questions/21327249/how-to-generate
	//-uncorrelated-random-sequences-using-c
	// https://cplusplus.com/reference/random/normal_distribution/
	vector<double> randvec(size, 0);

	for (int j=0; j<size; j++){
		randvec[j]=gaussian_vector[j](generator);
	}
	
	return randvec;
}


