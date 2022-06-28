#ifndef RANDVEC
#define RANDVEC
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <chrono>
#include <cstdint>
#include <future>

using namespace std;

/**
 *  Class that models a sequence of i.i.d. standard gaussians
 *  vector of distributions that can be sampled with random seeds, giving
 *  a model of uncorrelated Gaussian variables.
 */
class RandVec{
	private:
		int lenVec;
		// vector of generators to generate Gaussian Vectors;
    	vector<normal_distribution<double> > gaussianVector;
		default_random_engine generator;
		unsigned generateSeed();
	public:
		RandVec(int n);
		RandVec() = default; // pass in default constructor
    	//the following methods relate to the generation of vectors of iid standard normal rvs (and by extension dfgfs)
    	vector<double> sample(int size);
		//creates sequences of random variables in parallel (fast especially when there are a lot of cores)
		vector<vector<double>> parallelSampler(int size, int num_seq);
};

#endif