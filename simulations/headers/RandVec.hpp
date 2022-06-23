#ifndef RANDVEC
#define RANDVEC
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

class RandVec{
	private:
		int len_vec;
    	vector<normal_distribution<double>> gaussian_vector;
		default_random_engine generator;
	public:
		RandVec(int n);
		RandVec() = default; // pass in default constructor
    	//the following methods relate to the generation of vectors of iid standard normal rvs (and by extension dfgfs)
    	vector<double> gen_rand_vec(int size);
};

#endif