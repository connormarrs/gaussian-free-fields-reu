#ifndef RANDARR
#define RANDARR
#define _USE_MATH_DEFINES

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
class RandArr{
	private:
		int dimArray;
		int numTrials;
		vector<vector<vector<double>>> samples; /* numTrials vs N array of */
		void threadSafe_Sample();
		void sample_univariate_gaussian(unsigned int seed, int index1, int index2);
	public:
		RandArr(int maxDim, int numTrials);
		RandArr() = default; // pass in default constructor
		~RandArr() = default;
		vector<vector<vector<double>>> getSample(int size);
};

#endif