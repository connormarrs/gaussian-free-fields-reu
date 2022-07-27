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
double getMean(double svalue, int nvalue, int numTrials, RandVec randvec){
	// Instantiates the objects to collect data for the json file.
	//FGF_S1 *dfgf = new DFGF_S1(svalue, nvalue, numTrials, randvec, true);
	std::shared_ptr<DFGF_S1> dfgf(new DFGF_S1(svalue,nvalue,numTrials,randvec, true));
	dfgf->runTrials();
	double empMean = dfgf->getEmpMean();
	return empMean;
}
/**
 * The main file that runs the code
 */
int main() {
	/**
	 *	EXPERIMENT SECTION 
	 *
	 * Set the parameters and run the main method in the driver
	 * to generate the data.
	 */
	int start_in = 500;
	int end_in = 2500;
	int n_increm = 5;
	double start_es = 0.0;
	double end_es = 0.5;
	string sRange = "s"+to_string(start_es)+"-"+to_string(end_es);
	double s_increm = 0.001;
	int numTrials = 2000;
	double s_split_increm = 0.125;

	// Simulations setup
	vector<int> n_vals = Tools::linspace(start_in, end_in, n_increm);
	vector<double> s_split = Tools::linspaceDouble(start_es, end_es, s_split_increm, true);

	// Compute a single randvec for the largest value of n
	RandVec randvec(n_vals.back(), numTrials);
	// Runs through each n val to run the whole program
	for(long unsigned int n_index=0; n_index < n_vals.size(); n_index++){
		// Runs through each s val for a given n val
		queue<future<double>> *tasks = new queue<future<double>>(); // make this pointer
		std::ofstream myfile;
		// Creates a name for the file
		string runName = "../../output/" + to_string(n_vals[n_index]) + "_"+sRange+".csv";
		myfile.open (runName);
		for(unsigned int i =0; i<s_split.size()-1; i++){
			vector<double> s_vals = Tools::linspaceDouble(s_split[i], s_split[i+1], s_increm, false);
			for (long unsigned int s_index=0; s_index<s_vals.size(); s_index++){
				tasks->push(
					async(launch::async, getMean, s_vals[s_index],n_vals[n_index], numTrials, randvec)
				);
			}		
			for(long unsigned int s_index=0; s_index<s_vals.size(); s_index++){
				myfile << to_string(n_vals[n_index]) << ',' << to_string(s_vals[s_index]) << ',' << tasks->front().get() << endl;
				tasks->pop();
				std::cout << "Thread n=" << n_vals[n_index] << " s=" << s_vals[s_index] << endl;
			}
		}


		/*
		* Writes the contents of cs (our json object) to a file
		*/
		myfile.close();
		//operator delete(tasks);
	}
    	
	std::cout << "Job done :)" << endl;

	return 0;
}
