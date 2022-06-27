#include "../headers/DFGF_S1.hpp"
#include <vector>
#include <stdio.h>
#include <chrono>

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
	int start_in = 1;
	int end_in = 1001;
	int num_in = 100;
	int num_seqs = 100;
	int size = end_in;
	double s = 0.25;
	DFGF_S1 DS1(s);//issue is in this line

	// Start measuring time 
	// code from this example https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9
    auto begin = std::chrono::high_resolution_clock::now();
	cout<<"calculating datatensor \n";
	
	auto datatensor = DS1.parallelDFGF(s, start_in, end_in, num_in, size, num_seqs);
	 
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	cout<< "time elapsed is " << elapsed.count()<< "\n";
	
	cout <<"calculating maximat\n";
	begin = std::chrono::high_resolution_clock::now();
	vector<vector<double>> maximamat = DS1.parallelMax(datatensor);
	
	end = std::chrono::high_resolution_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	cout<< "time elapsed is " << elapsed.count()<< "\n";

	cout<<"calculating maxima"<<"\n";
	begin = std::chrono::high_resolution_clock::now();
	vector<double> exmax = DS1.parallelMeans(maximamat);


	// Stop measuring time and calculate the elapsed time
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	cout<< "time elapsed is " << elapsed.count()<<"\n";
	cout<<"writing to csv"<<"\n";

	//write results
	vector<int> n_vals = Tools::linspace(start_in, end_in, num_in );
	string filename("mt1test.csv");
	fstream file;
	
	file.open(filename, std::ios_base::app | std::ios_base::in);
	for(int i =0; i < exmax.size(); i ++){
		if (file.is_open()) {
			file << n_vals[i] << ',' << exmax[i] << '\n';
		}
	}
	return 0;
}



// vector<int> nvals = Tools::linspace(n_start, n_end, num_nvals); // set the nvals array
	
	// // generate vector of values
	// vector<double> exp_Max(num_nvals);

	// // generate RandVec object to pass in to things
	// RandVec gaussian_vector(nvals[num_nvals-1]); //

	// // iterate over all values of n
	// for(int n=0; n<num_nvals; n++) {
	// 	// generate the DFGF_S1 object
	// 	DFGF_S1 sampleFGF(s, n, gaussian_vector);

	// 	double sum_Max = 0;
	// 	// loop over the number of trials, add the maximum to our total
	// 	for(int j=0; j<num_trials; j++) {
	// 		sum_Max += sampleFGF.compute_max();
	// 	}
	// 	// set expected value of M_k to be the empirical mean
	// 	exp_Max[n] = sum_Max/num_trials;
	// 	string filename("exp_sample.csv");
	// 	fstream file;
		
	// 	file.open(filename, std::ios_base::app | std::ios_base::in);
	// 	if (file.is_open()) {
	// 		file << nvals[n] << ',' << exp_Max[n] << '\n';
	// 	}
	// }
