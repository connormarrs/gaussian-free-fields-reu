#include "../headers/DFGF_S1.hpp"
#include <vector>
#include <stdio.h>
#include <chrono>



double getMeans(double s, int n, int numTrials){
	RandVec randvec(n);
	DFGF_S1 dfgf(s, n, numTrials, randvec);
	return dfgf.getMeanOfMaxima();
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
	int end_in = 2010;
	int num_in = 400;
	int numTrials = 500;
	int size = end_in;
	double s = 0.25;
	//decide whether or not u want to save during the calcualtions or after
	//saving during slightly slows the code
	bool intermittentSave = true;



	//simulations setup
	vector<int> n_vals = Tools::linspace(start_in, end_in, num_in);
	vector<double> means;
	vector<future<double>> tasks;
	vector<int> times;




	vector<vector<int>> timeData;
	// for(int n=0; n < n_vals.size(); n++){
	int n = 0;
	while(n<n_vals.size()){
		if(means.size()>= n){
		auto begin = std::chrono::high_resolution_clock::now();
		RandVec randvec(n_vals[n]);
		DFGF_S1 dfgf(s, n_vals[n], numTrials, randvec);
		means.push_back(dfgf.getMeanOfMaxima());
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		cout<< "time elapsed is " << elapsed.count()<< "\n";
		times.push_back(elapsed.count());
		}

		//open files and write
		if(means.size()>=n+1){
			if(intermittentSave){
				string filename1("expectedMaxData.csv");
				fstream file1;
				file1.open(filename1, std::ios_base::app | std::ios_base::in);

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
		n++;
		}
	
	//}

	}

			if(!intermittentSave){
			string filename1("expectedMeanData.csv");
			fstream file1;
			file1.open(filename1, std::ios_base::app | std::ios_base::in);

			string filename2("timeData.csv");
			fstream file2;
			file2.open(filename2, std::ios_base::app | std::ios_base::in);\
			for(int n = 0; n<means.size();n++){
				if (file1.is_open()) {
					file1 << n_vals[n] << ',' << means[n] << '\n';		
				}
				if (file1.is_open()) {
					file2 << n_vals[n] << ',' << times[n] << '\n';
				}	
			}
		}
	//Tools::printVector(means);
	// for(int n = 0; n < n_vals.size(); n++){
	// 	tasks.push_back(async(getMeans, s, n_vals[n], numTrials));
	// }
	// for(int j = 0; j<tasks.size(); j++){
	// 	double mean = tasks[j].get();
	// 	means.push_back(mean);
	// }
	// string filename1("expectedMeanData.csv");
	// fstream file;
	// file.open(filename1, std::ios_base::app | std::ios_base::in);
	// for(int i =0; i < means.size(); i ++){
	// 	cout<<n_vals[i]<<","<<means[i]<<"\n";
	// 	if (file.is_open()) {
	// 		file << n_vals[i] << ',' << means[i] << '\n';
	// 	}
	// }


	return 0;
}



