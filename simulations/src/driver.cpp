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
double getMean(int nvalue, double svalue, int numTrials, RandVec randvec){
	// Instantiates the objects to collect data for the json file.
	//DFGF_S1 *dfgf = new DFGF_S1(svalue, nvalue, numTrials, randvec);
	std::shared_ptr<DFGF_S1> dfgf(new DFGF_S1(svalue,nvalue,numTrials,randvec));
	dfgf->runTrials();
	double empMean = dfgf->getEmpMean();
	//dfgf->~DFGF_S1();
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
	int num_in = 400;
	double start_es = 0.0;
	double intermediate_es;
	double end_es = 0.5;
	string sRange = "s0.0-0.5";
	double increm = 0.001;
	int numTrials = 2000;

	// Simulations setup
	vector<int> n_vals = Tools::linspace(start_in, end_in, num_in);
    vector<double> s_vals0 = Tools::linspaceDouble( start_es, intermediate_es, increm);
	vector<double> s_vals1 = Tools::linspaceDouble( intermediate_es, end_es, increm);

	// Compute a single randvec for the largest value of n
	RandVec randvec(n_vals[n_vals.size()-1], numTrials);

	// Runs through each n val to run the whole program
	for(long unsigned int n_index=0; n_index < n_vals.size(); n_index++){
		// Runs through each s val for a given n val
		queue<future<double>> *tasks = new queue<future<double>>(); // make this pointer

		// Creates a name for the file
		string runName = "../../output/" + to_string(n_vals[n_index]) + "_"+sRange+".csv";
		std::ofstream myfile;
		myfile.open (runName);


		// for (long unsigned int s_index=0; s_index<s_vals.size(); s_index++){
		// 	tasks->push(
		// 		async(launch::async, [](int nvalue, double svalue, int numTrials, RandVec randvec){
		// 			// Instantiates the objects to collect data for the json file.
		// 			//DFGF_S1 *dfgf = new DFGF_S1(svalue, nvalue, numTrials, randvec);
		// 			std::shared_ptr<DFGF_S1> dfgf(new DFGF_S1);
		// 			dfgf->runTrials();
		// 			double empMean = dfgf->getEmpMean();
		// 			cout<<"empMean"<<empMean;
		// 			//dfgf->~DFGF_S1();
		// 			return empMean;
		// 		},n_vals[n_index], s_vals[s_index], numTrials, randvec)
		// 	);
		// }
		for (long unsigned int s_index=0; s_index<s_vals0.size(); s_index++){
			tasks->push(
				async(launch::async, getMean,n_vals[n_index], s_vals0[s_index], numTrials, randvec)
			);
		}		
		for(long unsigned int s_index=0; s_index<s_vals0.size(); s_index++){
			myfile << to_string(n_vals[n_index]) << ',' << to_string(s_vals0[s_index]) << ',' << tasks->front().get() << endl;
			tasks->pop();
			std::cout << "Thread n=" << n_vals[n_index] << " s=" << s_vals0[s_index] << endl;
		}
		for (long unsigned int s_index=0; s_index<s_vals1.size(); s_index++){
			tasks->push(
				async(launch::async, getMean,n_vals[n_index], s_vals1[s_index], numTrials, randvec)
			);
		}		
		for(long unsigned int s_index=0; s_index<s_vals1.size(); s_index++){
			myfile << to_string(n_vals[n_index]) << ',' << to_string(s_vals1[s_index]) << ',' << tasks->front().get() << endl;
			tasks->pop();
			std::cout << "Thread n=" << n_vals[n_index] << " s=" << s_vals1[s_index] << endl;
		}

		/*
		* Writes the contents of cs (our json object) to a file
		*/
		myfile.close();
		operator delete(tasks);
	}
    	
	cout << "Job done :)" << endl;

	return 0;
}


					// // Instantiates the objects to collect data for the json file.
					// DFGF_S1 *dfgf = new DFGF_S1(svalue, nvalue, numTrials, randvec);
					// dfgf->runTrials();
					// double empMean = dfgf->getEmpMean();
					// dfgf->~DFGF_S1();
					// operator delete(dfgf);
					// return empMean;