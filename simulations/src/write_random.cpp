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

	// Compute a single randvec for the largest value of n
	RandVec randvec(nval, numTrials);

	// Creates a name for the file
	string runName = "../../output/" + to_string(nval) + "_"+sRange+".csv";
	std::ofstream myfile;
	myfile.open (runName);
	
	/*
	* Writes the contents of cs (our json object) to a file
	*/
	myfile.close();

    	
	cout << "Job done :)" << endl;

	return 0;
}
