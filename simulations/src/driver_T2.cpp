#include "../headers/DFGF_T2.hpp"
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

	RandArr randvec(nval, numTrials);

	// Creates a name for the file
	string runName = "../../output_T2/" + to_string(nval) + "_"+sRange+".csv";
	std::ofstream myfile;
	myfile.open (runName);

	for (long unsigned int s_index=0; s_index<s_vals.size(); s_index++){
		// Instantiates the objects to collect data for the json file.
		DFGF_T2 *dfgf = new DFGF_T2(s_vals[s_index], nval, numTrials, randvec, true);
		dfgf->runTrials();
		myfile << to_string(nval) << ',' << to_string(s_vals[s_index]) << ',' << dfgf->getEmpMean() << endl;
		dfgf->~DFGF_T2();
		operator delete(dfgf);
	}	
	
	/*
	* Writes the contents of cs (our json object) to a file
	*/
	myfile.close();

    	
	cout << "Job done :)" << endl;

	return 0;
}
