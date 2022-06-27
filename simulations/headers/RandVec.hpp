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

class RandVec{
	private:
		int len_vec;
    	vector<normal_distribution<double> > gaussian_vector;
		default_random_engine generator;
	public:
		RandVec(int n);
		RandVec() = default; // pass in default constructor
    	//the following methods relate to the generation of vectors of iid standard normal rvs (and by extension dfgfs)
    	vector<double> gen_rand_vec(int size);
		//get number of milliseconds since the start of the epoch as a basis for creating a random seed
		unsigned timeSinceEpochMillisec();
		//creates sequences of random variables in parallel (fast especially when there are a lot of cores)
		vector<vector<double>> parallelSampler(int size, int num_seq);
};


#endif

// /**
//  * Constructor for the Sampler class
//  */
// RandVec::RandVec(int n) {
// 	len_vec = n;
// 	// instantiate a vector of length n of i.i.d. gaussians
// 	for (int i=0; i<n; ++i) {
// 		// for each n, use a new generator to guarantee independence
// 		normal_distribution<double> distribution(0.0,1.0);
// 		// need to use push back
// 		gaussian_vector.push_back(distribution);
		

// 	}
// }

// /**
//  *  gen_rand_vec
//  */
// vector<double> RandVec::gen_rand_vec(int size){
// 	// source: should guarantee that using std::normal_distribution
// 	// generates independent samples
// 	// https://stackoverflow.com/questions/21327249/how-to-generate
// 	//-uncorrelated-random-sequences-using-c
// 	// https://cplusplus.com/reference/random/normal_distribution/
// 	vector<double> randvec;
// 	for (int j=0; j<size; j++){
// 		std::random_device rd;
// 		int offset=rd();
// 		unsigned randSeed=timeSinceEpochMillisec()+offset;
// 		generator.seed(randSeed);
// 		//cout << generator<<"\n";
// 		randvec.push_back(gaussian_vector[j](generator));
// 	}

// 	return randvec;
// }
// // method from https://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets
// unsigned RandVec::timeSinceEpochMillisec(){
// 	using namespace std::chrono;
// 	return unsigned(duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count());
// }

// vector<vector<double>> RandVec::parallelSampler(int size, int num_seq){
// 	vector<vector<double>> seqs; 
// 	seqs.reserve(num_seq);
// 	vector<future<vector<double>>> tasks;
// 	RandVec RandVecs(size);
// 	for (int i=0; i<num_seq; i++){
// 		tasks.push_back(std::async(&RandVec::gen_rand_vec, &RandVecs, size));	
// 	}
// 	for (int i =0; i<tasks.size();i++){
// 		seqs.push_back(tasks[i].get());	
// 	}
// 	return seqs;

// }
// #endif