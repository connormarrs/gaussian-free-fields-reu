#include "../headers/DFGF_S1.hpp"
#include "../headers/RandVec.hpp"
#include "../headers/tools.hpp"
#include <vector>

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
	int n_start = 5; // value to start indexing n by
	int n_end = 100; // end value for n test values
	int num_nvals = 20; // number of n values to test
	int num_trials = 50; // number of trials to sample for each n
	double s = .25; // parameter s of the FGF

	vector<int> nvals = Tools::linspace(n_start, n_end, num_nvals); // set the nvals array
	
	// generate vector of values
	vector<double> exp_Max(num_nvals);

	// generate RandVec object to pass in to things
	RandVec gaussian_vector(nvals[num_nvals-1]); //

	// iterate over all values of n
	for(int n=0; n<num_nvals; n++) {
		// generate the DFGF_S1 object
		DFGF_S1 sampleFGF(s, n, gaussian_vector);

		double sum_Max = 0;
		// loop over the number of trials, add the maximum to our total
		for(int j=0; j<num_trials; j++) {
			sum_Max += sampleFGF.compute_max();
		}
		// set expected value of M_k to be the empirical mean
		exp_Max[n] = sum_Max/num_trials;
		string filename("exp_sample.csv");
		fstream file;
		
		file.open(filename, std::ios_base::app | std::ios_base::in);
		if (file.is_open()) {
			file << nvals[n] << ',' << exp_Max[n] << '\n';
		}
	}

	return 0;
}