#include "../headers/DFGF_S1.hpp"
#include <vector>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <json/json.h>

string fileName(int start_n, int end_n, string s_Val) {
	string name;
	name += s_Val+"_n"+to_string(start_n)+"-"+to_string(end_n)+".json";

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
	std::string runName = "../../output/" + fileName(start_in, end_in, sVal);

	// Creates the main json object
	Json::Value jsonRoot;

	// Adds already known information to the json
	jsonRoot["info"]["maxN"] = end_in;
	jsonRoot["info"]["numTrials"] = numTrials;
	jsonRoot["info"]["s"] = s;
	jsonRoot["run"] = runName;

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
		Json::Value vec1(Json::arrayValue);
		for (long unsigned int p=0; p<trialData.size(); p++) {
			Json::Value vec2(Json::arrayValue);
			for (long unsigned int q=0; q<trialData[0].size(); q++) {
				vec2.append(trialData[p][q]);
			}
			vec1.append(vec2);
		}
		jsonRoot["info"]["n"][to_string(n_vals[n])]["trialData"] = vec1;

		// Adds the maxima vector to the json. f indexes each trial.
		vector<double> maxes = dfgf.computeMaxVectors();
		Json::Value vec3(Json::arrayValue);
		for (long unsigned int f=0; f<maxes.size(); f++) {
			vec3.append(maxes[f]);
		}
		jsonRoot["info"]["n"][to_string(n_vals[n])]["maxima"] = vec3;

		// Adds the coefficients to the json. m indexes each trial,
		// where n indexes the individual data points
		vector<vector<double>> coeffs = dfgf.getCoeffs();
		Json::Value vec4(Json::arrayValue);
		for (long unsigned int m=0; m<coeffs.size(); m++) {
			Json::Value vec5(Json::arrayValue);
			for (long unsigned int n=0; n<coeffs[0].size();n++) {
				vec5.append(coeffs[m][n]);
			}
			vec4.append(vec5);
		}
		jsonRoot["info"]["n"][to_string(n_vals[n])]["coefficients"] = vec4;

		// Adds eigen vectors to the json. x indexes trials,
		// where y indexes the individual data points
		vector<vector<double>> eigVects = dfgf.getEigenVectors();
		Json::Value vec6(Json::arrayValue);
		for (long unsigned int x=0; x<eigVects.size(); x++) {
			Json::Value vec7(Json::arrayValue);
			for (long unsigned int y=0; y<eigVects[0].size(); y++) {
				vec7.append(eigVects[x][y]);
			}
			vec6.append(vec7);
		}
		jsonRoot["info"]["n"][to_string(n_vals[n])]["eigenVectors"] = vec6;

		// Adds eigen values to the json. z indexes individual values.
		vector<double> eigVals = dfgf.getEigenVals();
		Json::Value vec8(Json::arrayValue);
		for (long unsigned int z=0; z<eigVals.size(); z++) {
			vec8.append(eigVals[z]);
		}
		jsonRoot["info"]["n"][to_string(n_vals[n])]["eigenVals"] = vec8;

		// Adds the meanOfMaxima to the json.
		jsonRoot["info"]["n"][to_string(n_vals[n])]["meanOfMaxima"] = dfgf.computeEmpMean();
		
		// This could be usefull for displaying all means at once instead of individually
		// means.push_back(dfgf.computeEmpMean()); 
		
		//Ending Time and Printing
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << "Finished n=" << n_vals[n] << ". Time elapsed is " << elapsed.count() << " milliseconds." << "\n";
		times.push_back(elapsed.count());
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