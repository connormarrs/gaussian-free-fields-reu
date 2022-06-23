#include "DFGF_S1.hpp"
#include "RandVec.hpp"
#include "tools.hpp"
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
	 */
	// void sample() {
	// vector<int> nvals = linspace(n_start, n_end, num_nvals); // set the nvals array
	
	// // generate vector of values
	// vector<double> exp_Max(num_nvals);

	// // iterate over all values of n
	// for(int k=0; k<num_nvals; k++) {
	// 	double sum_Max = 0;
	// 	// loop over the number of trials, add the maximum to our total
	// 	for(int j=0; j<num_trials; j++) {
	// 		sum_Max += compute_max(nvals[k], gen_rand_vec(nvals[k]));
	// 	}
	// 	// set expected value of M_k to be the empirical mean
	// 	exp_Max[k] = sum_Max/num_trials;
	// 	string filename("exp_sample.csv");
	// 	fstream file;
		
	// 	file.open(filename, std::ios_base::app | std::ios_base::in);
	// 	if (file.is_open()) {
	// 		file << nvals[k] << ',' << exp_Max[k] << '\n';
	// 	}
	// }
	// }

	return 0;
}