#include "../headers/DFGF_S1.hpp"
#include <vector>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

string fileName(int start_n, int end_n, string s_Val) {
	string name;
	name += s_Val+"_n"+to_string(start_n)+"-"+to_string(end_n)+".csv";

	return name;
}

using namespace std;

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
	int start_in = 10;
	int end_in = 100;
	int num_in = 10;
	int numTrials = 20;

	// Change these values at the same time for fileName usage.
	// Example: 0.25 -> "s025"  OR 0 -> "s0"
	double s = 0.25;
	string sVal = "s025";

	// Simulations setup
	vector<int> n_vals = Tools::linspace(start_in, end_in, num_in);
	vector<double> means;
	vector<future<double>> tasks;
	vector<int> times;

	// Creates a name for the file
	string runName = "../../output/" + fileName(start_in, end_in, sVal);
	std::ofstream myfile;
	myfile.open (runName);

	// Runs through each n val to run the whole program
	vector<vector<int>> timeData;
	for(long unsigned int n=0; n < n_vals.size(); n++){
    	// Start Time
		auto begin = std::chrono::high_resolution_clock::now();
		
		// Instantiates the objects to collect data for the json file.
		RandVec randvec(n_vals[n], numTrials);
		DFGF_S1 dfgf(s, n_vals[n], numTrials, randvec);

		// Adds trialData to json. p indexes each trial,
		// where q indexes the individual data points
		vector<vector<double>> trialData = dfgf.runTrials();

		// Adds the maxima vector to the json. f indexes each trial.
		vector<double> maxes = dfgf.computeMaxVectors();
		double max = dfgf.computeEmpMean();
		myfile << n << ", " << max << " \n";

		// Adds the coefficients to the json. m indexes each trial,
		// where n indexes the individual data points
		vector<vector<double>> coeffs = dfgf.getCoeffs();

		// Adds eigen vectors to the json. x indexes trials,
		// where y indexes the individual data points
		vector<vector<double>> eigVects = dfgf.getEigenVectors();

		// Adds eigen values to the json. z indexes individual values.
		vector<double> eigVals = dfgf.getEigenVals();
		
		//Ending Time and Printing
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << "Finished n=" << n_vals[n] << ". Time elapsed is " << elapsed.count() << " milliseconds." << "\n";
		times.push_back(elapsed.count());
	}

	/*
	* Writes the contents of jsonRoot (our json object) to a file
	*/
	myfile.close();

	return 0;
}
