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

	// Creates a name for the file
	//std::string runName = "../../output/" + fileName(start_in, end_in, sRange);

	// Runs through each n val to run the whole program
	for(long unsigned int n_index=0; n_index < n_vals.size(); n_index++){
		// Runs through each s val for a given n val
		Json::Value jsonSmallRoot;
		queue<future<double>> tasks;
		//string runName = "../../output/"+"d2_"+range+"_n"+to_string(start_n)+"-"+to_string(end_n)+"_n_val_"+to_string(n_vals[n_index])+".json" ;	
		string runName = "../../output/numTrials"+to_string(numTrials)+"_sRange_"+sRange+"_n_val"+to_string(n_vals[n_index])+".json";
		jsonSmallRoot["info"]["nValue"] = n_vals[n_index];
		jsonSmallRoot["info"]["numTrials"] = numTrials;
		jsonSmallRoot["run"] = runName;
		for (long unsigned int s_index=0; s_index < s_vals.size(); s_index++) {
			// tasks.push(
			// 	async(sampleDFGF, n_vals[n_index], s_vals[s_index], numTrials, randvec)
			// );
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
			jsonSmallRoot["info"]["n"][to_string(n_vals[n_index])]["s"][to_string(s_vals[s_index])]["meanOfMaxima"] = tasks.front().get();
			tasks.pop();
			cout << "Thread n=" << n_vals[n_index] << " s=" << s_vals[s_index] << endl;

			//string runName = "../../output/"+"d2_"+sRange+"_n"+to_string(start_in)+"-"+to_string(end_in)+"_n_val_"+to_string(n_vals[n_index])+".json" ;	
			//string runName = "../../output"+sRange+"_n_val"+to_string(n_vals[n_index])+".json"
			Json::StreamWriterBuilder builder;
			builder["commentStyle"] = "None";
			builder["indentation"] = "";
			std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
			std::ofstream outFile(runName);
			writer -> write(jsonSmallRoot, &outFile);
			outFile.close();

		}
	}
    	
	cout << "Job done :)" << endl;

	return 0;
}
