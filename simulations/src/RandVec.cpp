#include "../headers/RandVec.hpp"

/**
 * constructor: sets an empty vector of length n and then
 * fills it with standard gaussian variables
 * 
 * param n: length of random vector
 */
RandVec::RandVec(int maxN, int numTrials) {
	/* initialize constants to given values */
	lenVec = maxN;
	this->numTrials = numTrials;

	/* initialize samples[][] vector to have all 0's */
	for(int i=0; i<numTrials; i++){
		vector<double> intermed(maxN,0.0);
		samples.push_back(intermed);
	}

	/* call threadSafeSample to quickly fill samples array */
	this->threadSafe_Sample();
}

/**
 * @brief given a specific seed
 * 
 * @param seed the seed to be fed to generator mt19937 - the Mersenne Twister of
 * period 19937 built into C++. According to stackoverflow, passing in pid's
 * should be random --> ensures 
 * 
 * @return double 
 */
double RandVec::getRandomValue(unsigned int seed){
	/* use mersenne twister to generate random numbers*/
	std::mt19937 gen(seed);
	std::normal_distribution<double> dist(0.0, 1.0); // Create distribution
	
	return dist(gen);
}

/**
 * @brief This method seeds the Mersenne Twister algorithm mt19937 with the given seed
 * and fills the column of samples representing the (index)th component of the random
 * vector with values from a standard gaussian distribution.
 * 
 * @cite https://stackoverflow.com/questions/14923902/random-numbers-for-multiple-threads
 * 
 * @param seed the value passed into the mersenne twister mt19937
 * @param index the component of the vector to be sampled
 */
void RandVec::sample_univariate_gaussian(unsigned int seed, int index){
	/* seed the random generator with the seed given, use Mersenne Twister */
	std::mt19937 gen(seed);
	std::normal_distribution<double> dist(0, 1);

	for(int k=0; k<numTrials; k++){
		/* loop through trials and fill up (index)th component */
		this->samples[k][index] = dist(gen);
	}
}

/**
 * @brief This method safely spawns a thread for each component of the vector
 * and fills the corresponding column of samples with values from a univariate gaussian
 * 
 * Since we seed these methods with different seeds, the values of each column
 * will behave as though they are from independent random variables.
 * 
 */
void RandVec::threadSafe_Sample() {
	/* initialize vector of tasks of length lenVec */
	vector<thread> tasks;

	/* for each component of the random vector spawn new thread to sample component */
	for(int j=0; j<lenVec; j++){
		/* we seed each generator with distinct value of j ==> different streams of random numbers */
		tasks.push_back(
			thread(&RandVec::sample_univariate_gaussian, this, (unsigned int)j, j)
		);
	}
	for(int j=0; j<lenVec; j++){
		/* for each task, wait until completion to return to main thread */
		tasks[j].join();
	}
}

/**
 * @brief creates a subarray of samples of shape (size) x (numTrials)
 * in order to let us use one RandVec object for multiple instances of smaller size
 * 
 * @param size 
 * @return vector<vector<double>> 
 */
vector<vector<double>> RandVec::getSample(int size) {
	vector<vector<double>> subArray;
	for(int j=0; j<numTrials; j++){
		vector<double> temp;
		for(int k=0; k<size; k++){
			temp.push_back(samples[j][k]);
		}
		subArray.push_back(temp);
	}
	return subArray;
}