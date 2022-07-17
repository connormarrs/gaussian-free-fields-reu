#include "../headers/DFGF_S1.hpp"
#include <vector>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
// #include "../vcpkg/installed/x64linux/include/json/json.h"
#include <jsoncpp/json/json.h>

//Gives the mean of the maxima for specified s and n values over a number of trials
//Not Used?
double getMeans(double s, int n, int numTrials){
	RandVec randvec(n, numTrials);
	DFGF_S1 dfgf(s, n, numTrials, randvec);
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
	int end_in = 101;
	int num_in = 10;
	int numTrials = 500;
	// int size = end_in;
	double s = 0.25;
	string sVal = "025";
	//decide whether or not you want to save during the calcualtions or after
	//saving during slightly slows the code
	bool intermittentSave = true;

	string runName = "name";

	//simulations setup
	vector<int> n_vals = Tools::linspace(start_in, end_in, num_in);
	vector<double> means;
	vector<future<double>> tasks;
	vector<int> times;

	Json::Value jsonRoot;

	jsonRoot["info"]["maxN"] = end_in;
	jsonRoot["info"]["numTrials"] = numTrials;
	jsonRoot["info"]["s"] = s;
	jsonRoot["run"] = runName;
	
	Json::Value test1(Json::arrayValue);
	Json::Value test2(Json::arrayValue);
	// test1 = Json::arrayValue((1,2,3));
	// test2 = Json::arrayValue((3,4,5));

	Json::Value vec1(Json::arrayValue);
	Json::Value vec2(Json::arrayValue);
	vec1.append(Json::Value(1));
	vec1.append(Json::Value(2));
	vec2.append(Json::Value(3));
	vec2.append(Json::Value(4));
	test1.append(vec1);
	test1.append(vec2);
	jsonRoot["info"]["n"]["3"]["testArr"] = test1;
	

	vector<vector<int>> timeData;
	for(long unsigned int n=0; n < n_vals.size(); n++){
    // 		Start Time
		auto begin = std::chrono::high_resolution_clock::now();
		
		//Adding Mean of Max Values for n and s over numTrials to json file
		RandVec randvec(n_vals[n], numTrials);
		DFGF_S1 dfgf(s, n_vals[n], numTrials, randvec);
		jsonRoot["info"]["n"][to_string(n_vals[n])]["meanOfMaxima"] = dfgf.computeEmpMean();
		// This could be usefull for displaying all means at once instead of individually
		means.push_back(dfgf.computeEmpMean()); 
		
		//Ending Time and Printing
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		cout<< "time elapsed is " << elapsed.count()<< "\n";
		times.push_back(elapsed.count());

		//open files and write
		if(intermittentSave){
			//Open Files to Append
			string filename1("expectedMaxData.csv");
			fstream file1;
			file1.open(filename1, std::ios_base::app | std::ios_base::in);
			
			//Writing Time
			string filename2("timeData.csv");
			fstream file2;
			file2.open(filename2, std::ios_base::app | std::ios_base::in);
			if (file1.is_open()) {
				file1 << n_vals[n] << ',' << means[n] << '\n';		
			}
			if (file1.is_open()) {
				file2 << n_vals[n] << ',' << times[n] << '\n';
			}	
		}
		

	}

			if(!intermittentSave){
			string filename1("expectedMeanData.csv");
			fstream file1;
			file1.open(filename1, std::ios_base::app | std::ios_base::in);
			
				
			string filename2("timeData.csv");
			fstream file2;
			file2.open(filename2, std::ios_base::app | std::ios_base::in);\
			for(long unsigned int n = 0; n<means.size();n++){
				if (file1.is_open()) {
					file1 << n_vals[n] << ',' << means[n] << '\n';		
				}
				if (file1.is_open()) {
					file2 << n_vals[n] << ',' << times[n] << '\n';
				}	
			}
		}

	for (unsigned long int i=0; i<means.size(); i++) {
		cout << means[i] << ", ";
	}
	cout << endl;
	

	cout << jsonRoot << endl;

	return 0;
}



