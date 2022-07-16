#ifndef RANDVEC
#define RANDVEC
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cmath>
#include <thread>

using namespace std;

/**
 *  Class that models a sequence of i.i.d. standard gaussians
 *  vector of distributions that can be sampled with random seeds, giving
 *  a model of uncorrelated Gaussian variables.
 */
class RandVec{
	private:
		int lenVec;
		int numTrials;
		vector<vector<double>> samples; /* numTrials vs N array of */
		void threadSafe_Sample();
		void sample_univariate_gaussian(unsigned int seed, int index);
		double getRandomValue(unsigned int seed);
	public:
		RandVec(int maxN, int numTrials);
		RandVec() = default; // pass in default constructor
		~RandVec() = default;
		vector<vector<double>> getSample(int size);
		vector<vector<double>> getSampleArray(int dimension); 
		}

#endif