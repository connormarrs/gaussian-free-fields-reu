#include "../headers/DFGF_S1.hpp"
#include <vector>
#include <queue>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <future>
#include <iostream>
#include <fstream>
#include <string>

// string fileName(int start_n, int end_n, string s_Val) {
// 	string name;
// 	name += s_Val+"_n"+to_string(start_n)+"-"+to_string(end_n)+".csv";
// 
// 	return name;
// }

using namespace std;

/**
 * The main file that runs the code
 */
int main() {
	/**
	 * EXPERIMENT SECTION
	 * 
	 * Set the parameters and run the main method in the driver
	 * to generate the data.
	 */
	int start_in = 500;
	int end_in = 3500;
	int num_in = 1000;
	double start_es = 0.0;
	double end_es = 0.5;
	string sRange = "s0.0-0.5";
	double increm = 0.001;
	int numTrials = 5000;

	// Simulations setup
	vector<int> n_vals = Tools::linspace(start_in, end_in, num_in);
	vector<double> s_vals = Tools::linspaceDouble( start_es, end_es, increm);
	
	// Compute a single randvec for the largest value of n
	RandVec randvec(n_vals[n_vals.size()-1], numTrials);

	for(long unsigned int n_index=0; n_index < n_vals.size(); n_index++){

		// Creates a name for the file
		string runName = "../../output/" + to_string(n_vals[n_index]) + "_"+sRange+".csv";
		std::ofstream myfile;
		myfile.open (runName);

		queue<future<double>> tasks;
		for (long unsigned int s_index=0; s_index < s_vals.size(); s_index++) {
			tasks.push(
				async(launch::async, [](int nvalue, double svalue, int numTrials, RandVec randvec){
					// Instantiates the objects to collect data for the json file.
					DFGF_S1 dfgf(svalue, nvalue, numTrials, randvec);
					// Runs the trials
					dfgf.runTrials();
					return dfgf.getEmpMean();
				},n_vals[n_index], s_vals[s_index], numTrials, randvec)
			);
		}

		for(long unsigned int s_index=0; s_index<s_vals.size(); s_index++){
			myfile << to_string(n_vals[n_index]) << ',' << to_string(s_vals[s_index]) << ',' << tasks.front().get() << endl;
			tasks.pop();
			cout << "Thread n=" << n_vals[n_index] << " s=" << s_vals[s_index] << endl;
		}

		/*
		* Writes the contents of jsonRoot (our json object) to a file
		*/
		myfile.close();
	}

	return 0;
}
