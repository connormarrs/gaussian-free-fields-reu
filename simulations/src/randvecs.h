//code from sample_max.cpp rewritten as a header
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

class RandVecs{
    public:
        //the following methods relate to the generation of vectors of iid standard normal rvs (and by extension dfgfs)
        vector<double> gen_rand_vec(int size);
        vector<int> linspace(int start_in, int end_in, int num_in);

};

vector<double> RandVecs::gen_rand_vec(int size){
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
vector<int> RandVecs::linspace(int start_in, int end_in, int num_in) {
	vector<int> linspaced;
	
	int start = static_cast<int>(start_in);
	int end = static_cast<int>(end_in);
	int num = static_cast<int>(num_in);
	
	if (num == 0) { 
		return linspaced; 
	}
	if (num == 1) {
		linspaced.push_back(start);
		return linspaced;
	}
	
	int delta = (end - start) / (num - 1);
	
	for(int i=0; i < num-1; ++i) {
		linspaced.push_back(start + delta * i);
	}
	
	return linspaced;
}
