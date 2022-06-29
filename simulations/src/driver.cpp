#include "../headers/DFGF_S1.hpp"
#include <vector>
#include <stdio.h>
#include <chrono>

int start_in = 10;
int end_in = 31;
int num_in = 20;
int numTrials = 20;
int size = end_in;
double s = 0.25;

double getMeans(double s, int n, int numTrials){
	RandVec randvec(n);
	DFGF_S1 dfgf(s, n, numTrials, randvec);
	return dfgf.getMeanOfMaxima();
}


/**
 * The main file that runs the code
 */
int main() {
	/**
	 *	TESTING SECTION
	 */

	/**
	 *	EXPERIMENT SECTION
	 *
	 * Set the parameters and run the main method in the driver
	 * to generate the data.
	 */
	// int n_start = 5; // value to start indexing n by
	// int n_end = 100; // end value for n test values
	// int num_nvals = 20; // number of n values to test
	// int num_trials = 50; // number of trials to sample for each n
	// double s = .25; // parameter s of the FGF




	vector<int> n_vals = Tools::linspace(start_in, end_in, num_in);
	//Tools::prINTVector(n_vals);

	vector<double> means;
	vector<future<double>> tasks;
	int n =10;
	RandVec randvec(n);
	DFGF_S1 dfgf(s, n, numTrials, randvec);
	// for(int n = 0; n < n_vals.size(); n++){
	// 	tasks.push_back(async(getMeans, s, n_vals[n], numTrials));
	// }

	// for(int j = 0; j<tasks.size(); j++){
	// 	means.push_back(tasks[j].get());
	// }
	// Tools::printVector(means);
	// string filename("exp_sample.csv");
	// fstream file;
	// file.open(filename, std::ios_base::app | std::ios_base::in);
	// for(int i =0; i < means.size(); i ++){
	// 	if (file.is_open()) {
	// 		file << n_vals[i] << ',' << means[i] << '\n';
	// 	}
	// }


	return 0;
}



