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

vector<double> getMaximaBB(double svalue, int nvalue, int numTrials, RandVec randvec){
	// Instantiates the objects to collect data for the json file.
	//FGF_S1 *dfgf = new DFGF_S1(svalue, nvalue, numTrials, randvec, true);
	std::shared_ptr<DFGF_S1> dfgf(new DFGF_S1(svalue,nvalue,numTrials,randvec, true));
	dfgf->runTrialsBB();
	double empMean = dfgf->getEmpMean();
    vector<double> maximaVector = dfgf->getMaximaList();
    maximaVector.push_back(empMean);
	return maximaVector;
}
vector<double> standardNormalMax(int numTrials, RandVec randvec){
    vector<vector<double>> randomArr = randvec.getSample(numTrials);
    vector<double> maxima;
    for(vector<double> i: randomArr){
        maxima.push_back(Tools::compute_max(i));
    }
    maxima.push_back(Tools::sampleMean(maxima));
    return maxima;
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
	int start_in = 2500;
	int end_in = 2500;
	int n_increm = 5;
	double start_es = 0.0;
	double end_es = 0.5;
	double s_increm = 0.5;
	int numTrials = 2000;
	double s_split_increm = 0.5;

	// Simulations setup
	vector<int> n_vals = Tools::linspace(start_in, end_in, n_increm);
	vector<double> s_split = Tools::linspaceDouble(start_es, end_es, s_split_increm, true);

	// Compute a single randvec for the largest value of n
	RandVec randvec(n_vals.back(), numTrials);
	// Runs through each n val to run the whole program
    std::ofstream myfile;
	// for(long unsigned int n_index=0; n_index < n_vals.size(); n_index++){
	// 	// Runs through each s val for a given n val
	// 	queue<future<vector<double>>> *tasks = new queue<future<vector<double>>>(); // make this pointer
	// 	// Creates a name for the file
	// 	for(unsigned int i =0; i<s_split.size()-1; i++){
	// 		vector<double> s_vals = Tools::linspaceDouble(s_split[i], s_split[i+1], s_increm, true);
    //         cout<<"";
    //         Tools::printVector(s_vals);

	// 		for (long unsigned int s_index=0; s_index<s_vals.size(); s_index++){
	// 			tasks->push(
	// 				async(launch::async, getMaximaBB, s_vals[s_index],n_vals[n_index], numTrials, randvec)
	// 			);
	// 		}		
	// 		for(long unsigned int s_index=0; s_index<s_vals.size(); s_index++){
    //             string runName = "../../output/" + to_string(n_vals[n_index]) + "_"+to_string(s_vals[s_index])+".csv";
    //             cout<<runName<<"\n";
    //             cout<<s_index<<tasks->size()<<"\n";
    //             myfile.open(runName);
    //             vector<double> temp = tasks->front().get();
    //             tasks->pop();
    //            // Tools::printVector(temp);
    //             for (unsigned int i =0; i< temp.size()-1; i++){
    //                 myfile << to_string(temp[i])<<","<<to_string(temp.back()) << endl;
    //             }
    //             std::cout << "Thread n=" << n_vals[n_index] << " s=" << s_vals[s_index] << endl;
    //             myfile.close();
    //         }
	// 	}


	
	// }
	// start_in = 100;
	// end_in = 30000;
	// n_increm = 100;
	// numTrials = 2000;
	// n_vals = Tools::linspace(start_in,end_in,n_increm);
	// string runName = "../../output/gaussian_expected_maxima" + to_string(n_vals.back()) +".csv";
    // cout<<runName<<"\n";
    // myfile.open(runName);
	// RandVec randvec2(30000,2000);
	// for(long unsigned int n_index=0; n_index < n_vals.size(); n_index++){
	// // Runs through each s val for a given n val
	// queue<future<double>> *tasks = new queue<future<double>>(); // make this pointer
	// // Creates a name for the file
	// 	tasks->push(
	// 		async(launch::async, [](int nval, RandVec randvec){
	// 			vector<vector<double>> data=randvec.getSample(nval);
	// 			vector<double> maximaVector;
	// 			for(vector<double> i: data){
	// 				maximaVector.push_back(Tools::compute_max(i));
	// 			}
	// 			double maxima = Tools::sampleMean(maximaVector);
	// 			return maxima;
	// 		}
			
	// 		,n_vals[n_index], randvec2)
	// 	);
    //     double temp = tasks->front().get();
    //     tasks->pop();
    //     // Tools::printVector(temp);
    //     myfile << to_string(n_vals[n_index])<<","<<to_string(temp) << endl;
    //     std::cout << "Thread n=" << n_vals[n_index] << endl;


	// 	}

    // myfile.close();	
	RandVec randvec3(25000, 40000);
    vector<double> gaussianMaxes = standardNormalMax(40000, randvec3);
    myfile.open("../../output/"+to_string(25000)+'_'+to_string(40000)+"_standard_normal_maxima.csv") ;
    for(unsigned int i = 0; i<gaussianMaxes.size()-1; i++){
        myfile<<to_string(gaussianMaxes[i])+","<<to_string(gaussianMaxes.back())<<endl;
    }
	std::cout << "Job done :)" << endl;

	return 0;
}