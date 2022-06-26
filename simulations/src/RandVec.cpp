#include "../headers/RandVec.hpp"

// /**
//  * Constructor for the Sampler class
//  */
// RandVec::RandVec(int n) {
// 	len_vec = n;
// 	// instantiate a vector of length n of i.i.d. gaussians
// 	for (int i=0; i<n; ++i) {
// 		// for each n, use a new generator to guarantee independence
// 		normal_distribution<double> distribution(0.0,1.0);
// 		gaussian_vector[i] = distribution;
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
// 	vector<double> randvec(size, 0);

// 	for (int j=0; j<size; j++){
// 		randvec[j]=gaussian_vector[j](generator);
// 	}
	
// 	return randvec;
// }

//pasted here because i was having trouble with imports otherwise

/**
 * Constructor for the Sampler class
 */
RandVec::RandVec(int n) {
	len_vec = n;
	// instantiate a vector of length n of i.i.d. gaussians
	for (int i=0; i<n; ++i) {
		// for each n, use a new generator to guarantee independence
		normal_distribution<double> distribution(0.0,1.0);
		// need to use push back
		gaussian_vector.push_back(distribution);
		

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
	vector<double> randvec;
	for (int j=0; j<size; j++){
		std::random_device rd;
		int offset=rd();
		unsigned randSeed=timeSinceEpochMillisec()+offset;
		generator.seed(randSeed);
		//cout << generator<<"\n";
		randvec.push_back(gaussian_vector[j](generator));
	}

	return randvec;
}
// method from https://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets
unsigned RandVec::timeSinceEpochMillisec(){
	using namespace std::chrono;
	return unsigned(duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count());
}

vector<vector<double>> RandVec::parallelSampler(int size, int num_seq){
	vector<vector<double>> seqs; 
	vector<std::future<vector<double>>> tasks;
	RandVec RandVecs;
	for (int i; i<num_seq; i++){
		int param = size;
		auto t = std::async(&RandVec::gen_rand_vec, &RandVecs, size);
		tasks.push_back(t);
	}
	for (int i; i<num_seq; i++){
		vector<double> sequence = tasks[i].get();
		seqs.push_back(sequence);
	}
	return seqs;
}
