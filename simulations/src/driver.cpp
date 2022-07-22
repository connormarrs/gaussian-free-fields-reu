#include "../headers/DFGF_S1.hpp"
#include <vector>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
// #include <jsoncpp/json/json.h>
using namespace std;


string fileName(int start_n, int end_n, string range) {
	string name;
	name += "d2_"+range+"_n"+to_string(start_n)+"-"+to_string(end_n)+".csv";

	return name;
}
/**
 * The main file that runs the code
 */
int main(int argc, char **argv) {
	/**
	 *	EXPERIMENT SECTION
	 *
	 * Set the parameters and run the main method in the driver
	 * to generate the data.
	 */
	// int start_in = 500;
	// int end_in = 2500;
	// int num_in = 400;

	double start_es = 0.0;
	double end_es = 0.5;
	string sRange = "s0.0-0.5";
	double increm = 0.001;
	int numTrials = 2000;

	// take in nvalue as argument
	int nval = stoi(argv[1]);

	// Simulations setup
	// vector<int> n_vals = Tools::linspace(start_in, end_in, num_in);
    vector<double> s_vals = Tools::linspaceDouble( start_es, end_es, increm);


	// for(unsigned long int n_index=0; n_index<n_vals.size(); n_index++){
	// 	// Compute a single randvec for the largest value of n
	// 	RandVec randvec(n_vals[n_index], numTrials);

	// 	// Creates a name for the file
	// 	string runName = "../../output/" + to_string(n_vals[n_index]) + "_"+sRange+".csv";
	// 	std::ofstream myfile;
	// 	myfile.open (runName);

	// 	for (long unsigned int s_index=0; s_index<s_vals.size(); s_index++){
	// 		// Instantiates the objects to collect data for the json file.
	// 		DFGF_S1 *dfgf = new DFGF_S1(s_vals[s_index], n_vals[n_index], numTrials, randvec);
	// 		dfgf->runTrials();
	// 		double empMean = dfgf->getEmpMean();
	// 		dfgf->~DFGF_S1();
	// 		operator delete(dfgf);
	// 		myfile << to_string(n_vals[n_index]) << ',' << to_string(s_vals[s_index]) << ',' << empMean << endl;
	// 		cout << to_string(n_vals[n_index]) << ',' << to_string(s_vals[s_index]) << endl;
	// 	}	
	
	// 	/*
	// 	* Writes the contents of cs (our json object) to a file
	// 	*/
	// 	myfile.close();
	// }

	// Compute a single randvec for the largest value of n
	RandVec randvec(nval, numTrials);

	// Creates a name for the file
	string runName = "../../output/" + to_string(nval) + "_"+sRange+".csv";
	std::ofstream myfile;
	myfile.open (runName);

	for (long unsigned int s_index=0; s_index<s_vals.size(); s_index++){
		// Instantiates the objects to collect data for the json file.
		DFGF_S1 *dfgf = new DFGF_S1(s_vals[s_index], nval, numTrials, randvec);
		dfgf->runTrials();
		double empMean = dfgf->getEmpMean();
		dfgf->~DFGF_S1();
		operator delete(dfgf);
		myfile << to_string(nval) << ',' << to_string(s_vals[s_index]) << ',' << empMean << endl;
	}	
	
	/*
	* Writes the contents of cs (our json object) to a file
	*/
	myfile.close();

    	
	cout << "Job done :)" << endl;

	return 0;
}
