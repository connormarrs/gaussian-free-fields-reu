#include "../headers/DFGF_S1.hpp"
#include <vector>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <jsoncpp/json/json.h>
using namespace std;


string fileName(int start_n, int end_n, string range) {
	string name;
	name += "d2_"+range+"_n"+to_string(start_n)+"-"+to_string(end_n)+".json";

	return name;
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
	int end_in = 1000;
	int num_in = 10;
	double start_es = 0.0;
	double end_es = 0.5;
	string sRange = "s0.0-0.5";
	double increm = 0.01;
	int numTrials = 500;

	// Simulations setup
	vector<int> n_vals = Tools::linspace(start_in, end_in, num_in);
    vector<double> s_vals = Tools::linspaceDouble( start_es, end_es, increm);

	// Compute a single randvec for the largest value of n
	RandVec randvec(n_vals[n_vals.size()-1], numTrials);

	// Runs through each n val to run the whole program
	for(long unsigned int n_index=0; n_index < n_vals.size(); n_index++){
		// Runs through each s val for a given n val
		Json::Value jsonSmallRoot;
		queue<future<double>> tasks;

		/* set up filename and stuff for json */
		string runName = "../../output/numTrials"+to_string(numTrials)+"_sRange_"+sRange+"_n_val"+to_string(n_vals[n_index])+".json";
		jsonSmallRoot["info"]["nValue"] = n_vals[n_index];
		jsonSmallRoot["info"]["numTrials"] = numTrials;
		jsonSmallRoot["run"] = runName;
		for (long unsigned int s_index=0; s_index<s_vals.size(); s_index++){
			tasks.push(
				async(launch::async, [](int nvalue, double svalue, int numTrials, RandVec randvec){
					// Instantiates the objects to collect data for the json file.
					DFGF_S1 *dfgf = new DFGF_S1(svalue, nvalue, numTrials, randvec);
					dfgf->runTrials();
					double empMean = dfgf->getEmpMean();
					dfgf->~DFGF_S1();
					operator delete(dfgf);
					return empMean;
				},n_vals[n_index], s_vals[s_index], numTrials, randvec)
			);
		}	
		for(long unsigned int s_index=0; s_index<s_vals.size(); s_index++){
			jsonSmallRoot["info"]["n"][to_string(n_vals[n_index])]["s"][to_string(s_vals[s_index])]["meanOfMaxima"] = tasks.front().get();
			cout << "Thread n=" << n_vals[n_index] << " s=" << s_vals[s_index] << endl; // << " mean=" << tasks.front().get()
			tasks.pop();
		}
		Json::StreamWriterBuilder builder;
		builder["commentStyle"] = "None";
		builder["indentation"] = "";
		std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
		std::ofstream outFile(runName);
		writer -> write(jsonSmallRoot, &outFile);
		outFile.close();
	}
    	
	cout << "Job done :)" << endl;

	return 0;
}
