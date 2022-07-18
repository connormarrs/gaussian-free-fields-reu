#include "../headers/RandArr.hpp"

/**
 * constructor: sets an empty vector of length n and then
 * fills it with standard gaussian variables
 * 
 * param n: length of random vector
 */
RandArr::RandArr(int maxN, int numTrials) {
	/* initialize constants to given values */
	dimArray = maxN;
	this->numTrials = numTrials;

	/* initialize samples[][][] vector to have all 0's */
	for(int i=0; i<numTrials; i++){
        /* creates an array interMed of dimension dimArray x dimArray with 0.0's */
		vector<vector<double>> interMed(dimArray, vector<double> (dimArray, 0.0));
		samples.push_back(interMed);
	}

	/* call threadSafeSample to quickly fill samples array */
	this->threadSafe_Sample();
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
void RandArr::sample_univariate_gaussian(unsigned int seed, int index1, int index2){
	/* seed the random generator with the seed given, use Mersenne Twister */
	std::mt19937 gen(seed);
	std::normal_distribution<double> dist(0, 1);

	for(int k=0; k<numTrials; k++){
		/* loop through trials and fill up (index)th component */
		this->samples[k][index1][index2] = dist(gen);
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
void RandArr::threadSafe_Sample() {
	/* initialize vector of tasks of length lenVec */
	vector<thread> tasks;

	/* for each component of the random vector spawn new thread to sample component */
	for(int j=0; j<dimArray; j++){
		for(int k=0; j<dimArray; j++){
            unsigned int seed = (unsigned int) (j*dimArray+k);
            /* we seed each generator with jk interpreted as a number base dimArray
            so by uniqueness of factorization, they have different seeds */
		    tasks.push_back(
			    thread(&RandArr::sample_univariate_gaussian, this, seed, j,k)
		    );
        }
	}
	for(unsigned int j=0; j<tasks.size(); j++){
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
vector<vector<vector<double>>> RandArr::getSample(int size) {
	vector<vector<vector<double>>> subArray;
	for(int j=0; j<numTrials; j++){
		vector<vector<double>> temp (size, vector<double> (size, 0.0));;
		for(int k=0; k<size; k++){
            for(int l=0; l<size; l++){
                temp[k][l] = samples[j][k][l];
            }
		}
		subArray.push_back(temp);
	}
	return subArray;
}
