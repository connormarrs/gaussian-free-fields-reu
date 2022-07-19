#include "../headers/DFGF_S1.hpp"
#include <vector>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
// #include "../vcpkg/packages/jsoncpp_x64-linux/include/json/json_features.h"
// #include "../vcpkg/packages/jsoncpp_x64-linux/include/json/writer.h"
#include <json/json.h>
//Gives the mean of the maxima for specified s and n values over a number of trials
//Not Used?
double getMeans(double s, int n, int numTrials){
	RandVec randvec(n, numTrials);
	DFGF_S1 dfgf(s, n, numTrials, randvec);
	dfgf.runTrials();
	dfgf.computeMaxVectors();

	return dfgf.computeEmpMean();
}

string fileNaming(int sVal, int numTrialVal) {
	time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%m-%d-%Y", &tstruct);
	string outFileName;
	string runNumFile("../output/runNum.txt");
    fstream file1;
    file1.open(runNumFile);
	string runNumStr;
	// int runNumInt = 0;
	getline(file1, runNumStr);
	// runNumInt = stoi(runNumStr) +1;
	file1.close();
	file1.open(runNumFile);
	file1 << buf;
	file1.close();
	
	return "";
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
	int end_in = 50;
	int num_in = 5;
	int numTrials = 20;
	// int size = end_in;
	double s = 0.25;
	string sVal = "025";
	//decide whether or not you want to save during the calcualtions or after
	//saving during slightly slows the code
	// bool intermittentSave = true;

	// Simulations setup
	vector<int> n_vals = Tools::linspace(start_in, end_in, num_in);
	vector<double> means;
	vector<future<double>> tasks;
	vector<int> times;

	// Creates the main json object
	Json::Value jsonRoot;

	// Adds already known information to the json
	jsonRoot["info"]["maxN"] = end_in;
	jsonRoot["info"]["numTrials"] = numTrials;
	jsonRoot["info"]["s"] = s;

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
		cout << "Finished n=" << n_vals[n] << ". Time elapsed is " << elapsed.count() << " milliseconds." << "\n";
		times.push_back(elapsed.count());

	// 	//open files and write
	// 	if(intermittentSave){
	// 		//Open Files to Append
	// 		string filename1("../output/expectedMaxData.csv");
	// 		fstream file1;
	// 		file1.open(filename1, std::ios_base::app | std::ios_base::in);
			
	// 		//Writing Time
	// 		string filename2("../output/timeData.csv");
	// 		fstream file2;
	// 		file2.open(filename2, std::ios_base::app | std::ios_base::in);
	// 		if (file1.is_open()) {
	// 			file1 << n_vals[n] << ',' << means[n] << '\n';		
	// 		}
	// 		if (file1.is_open()) {
	// 			file2 << n_vals[n] << ',' << times[n] << '\n';
	// 		}	
	// 	}
		

	}

	// 		if(!intermittentSave){
	// 		string filename1("../output/expectedMeanData.csv");
	// 		fstream file1;
	// 		file1.open(filename1, std::ios_base::app | std::ios_base::in);
			
				
	// 		string filename2("../output/timeData.csv");
	// 		fstream file2;
	// 		file2.open(filename2, std::ios_base::app | std::ios_base::in);
	// 		for(long unsigned int n = 0; n<means.size();n++){
	// 			if (file1.is_open()) {
	// 				file1 << n_vals[n] << ',' << means[n] << '\n';		
	// 			}
	// 			if (file1.is_open()) {
	// 				file2 << n_vals[n] << ',' << times[n] << '\n';
	// 			}	
	// 		}
	// 	}

	// Creates a name for the file and includes it in the json
	std::string runName = "..\\output\\test_1.json";
	jsonRoot["run"] = runName;

	// Writes the contents of jsonRoot (our json object) to a file
	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "  ";
	std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
	std::ofstream outputFileStream("../../output/test_1.json");
	writer -> write(jsonRoot, &outputFileStream);
	// cout << jsonRoot << endl;
	outputFileStream.close();
	return 0;
}



