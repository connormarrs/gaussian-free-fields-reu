#include "../headers/RandVec.hpp"

/**
 * constructor: sets an empty vector of length n and then
 * fills it with standard gaussian variables
 * 
 * param n: length of random vector
 */
RandVec::RandVec(int n) {
	lenVec = n;
	// instantiate a vector of length n of i.i.d. gaussians
	for (int i=0; i<n; ++i) {
		// for each n, use a new generator to guarantee independence
		normal_distribution<double> distribution(0.0,1.0);
		// need to use push back to access entries
		gaussianVector.push_back(distribution);
	}
}

/**
 * gen_rand_vec: samples a given random vector. Ensures they do
 * feed the same seed to threads accidentally
 * 
 * param size: length of the random vector to sample - allows us to sample
 * vectors of length less than n so we can reuse gaussian vector
 */
vector<double> RandVec::sample(int size){
	vector<double> randVec;
	for (int j=0; j<size; j++){
		// ensures that we randomly seed shit given threads could seed it with the same time.
		generator.seed(generateSeed());
		randVec.push_back(gaussianVector[j](generator));
	}

	return randVec;
}

/**
 * method from https://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets
 * timeSinceEpochMillisec: returns the time from internal clock since last epoch
 * used to seed random vector
 */
unsigned RandVec::generateSeed(){
	std::random_device rd;
		int offset=rd();
	using namespace std::chrono;
	return unsigned(duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count()+offset);
}

/**
 * parallelSampler: returns an array of sampled random vectors from the gaussian vector
 * 
 * param size: the size of vectors to be sampled
 * 
 * param num_seq: how many times we will sample the vector
 */
vector<vector<double>> RandVec::parallelSampler(int size, int num_sample){
	vector<vector<double>> sample; 
	vector<future<vector<double>>> tasks; // list of threads
	RandVec RandVecs(size);

	// make a new thread for each sample and append to list of tasks
	for (int i=0; i<num_sample; i++){
		tasks.push_back(std::async(&RandVec::sample, &RandVecs, size));	
	}
	// loop through and fill array with values once computed
	for (int i =0; i<tasks.size();i++){
		sample.push_back(tasks[i].get());
	}
	return sample;
}
