#include "../headers/DFGF_S1.hpp"
#include <vector>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <jsoncpp/json/json.h>

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
	 *	TESTING SECTION
	 */

	/**
	 *	EXPERIMENT SECTION
	 *
	 * Set the parameters and run the main method in the driver
	 * to generate the data.
	 */
	int start_in = 1;
	int end_in = 500;
	int num_in = 500;
    double start_es = 0.0;
    double end_es = 0.5;
    string sRange = "s0.0-0.5";
    double increm = 0.001;
	int numTrials = 1000;

	// Simulations setup
	vector<int> n_vals = Tools::linspace(start_in, end_in, num_in);
    vector<double> s_vals = Tools::linspaceDouble( start_es, end_es, increm);
	vector<double> means;
	vector<future<double>> tasks;
	vector<int> times;

	// Creates a name for the file
	std::string runName = "../../output/" + fileName(start_in, end_in, sRange);

	// Creates the main json object
	Json::Value jsonRoot;

	// Adds already known information to the json
	jsonRoot["info"]["maxN"] = end_in;
	jsonRoot["info"]["numTrials"] = numTrials;
	jsonRoot["run"] = runName;

	// Runs through each n val to run the whole program
	vector<vector<int>> timeData;
	for(long unsigned int n=0; n < n_vals.size(); n++){
        // Runs through each s val for a given n val
        for (long unsigned int s=0; s < s_vals.size(); s++) {
            // Start Time
		auto begin = std::chrono::high_resolution_clock::now();
		
		// Instantiates the objects to collect data for the json file.
		RandVec randvec(n_vals[n], numTrials);
		DFGF_S1 dfgf(s, n_vals[n], numTrials, randvec);

		// Runs the trials
		dfgf.runTrials();

		// Adds the maxima vector to the json. f indexes each trial.
		vector<double> maxes = dfgf.computeMaxVectors();
        /**
        * Uncomment to include all maximas in the json file
        */
		// Json::Value vec3(Json::arrayValue);
		// for (long unsigned int f=0; f<maxes.size(); f++) {
		// 	vec3.append(maxes[f]);
		// }
		// jsonRoot["info"]["n"][to_string(n_vals[n])]["s"][to_string(s_vals[s])]["maxima"] = vec3;

		// Adds the meanOfMaxima to the json.
		jsonRoot["info"]["n"][to_string(n_vals[n])]["s"][to_string(s_vals[s])]["meanOfMaxima"] = dfgf.computeEmpMean();
		
		// This could be usefull for displaying all means at once instead of individually
		// means.push_back(dfgf.computeEmpMean()); 
		
		//Ending Time and Printing
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << "Finished n=" << n_vals[n] << ", s=" << s_vals[s] << ". Time elapsed is " << elapsed.count() << " milliseconds." << "\n";
		times.push_back(elapsed.count());
	    }
    }
    	
	/*
	* Writes the contents of jsonRoot (our json object) to a file
	*/
	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "";
	std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
	std::ofstream outFile(runName);
	writer -> write(jsonRoot, &outFile);
	outFile.close();

	return 0;
}