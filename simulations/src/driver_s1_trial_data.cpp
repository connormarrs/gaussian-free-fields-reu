#include "../headers/DFGF_S1.hpp"
#include <vector>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <memory>
// #include <jsoncpp/json/json.h>
using namespace std;
vector<double> getTrialData(double sval,int nval,int numtrials,RandVec randvec, bool dirichlet){
    std::shared_ptr<DFGF_S1> dfgf(new DFGF_S1(sval,nval,numtrials,randvec, dirichlet));
    //DFGF_S1 *dfgf= new DFGF_S1(sval,nval,numtrials,randvec,dirichlet);
	dfgf->runTrials();
    //std::unique_ptr<vector<double>> data(new vector<double>());
    std::shared_ptr<vector<vector<double>>> data1(new vector<vector<double>>(dfgf->getTrialData()));
    shared_ptr<vector<double>> data(new vector<double>);
    *data  = data1->at(0);
    data1.reset();
    return *data;
}
int main(int argc, char **argv){
    vector<double> temp_s_val{0.0, 0.225,0.25, 0.275, 0.5, 0.75, 1.0, 1.5};
    vector<double> s_val0;
    for(double i : temp_s_val){
        s_val0.push_back(i);
    }
    int nval = stoi(argv[1]);
    //n_vals should be in numerical order
    
    RandVec randvec= RandVec(nval,1);
    cout<<"first for loop\n";
    std::ofstream myfile;
    //vector<vector<double>> trialDatas;
    for(unsigned int s_index = 0; s_index<s_val0.size(); s_index ++){
        cout<<nval<<","<<s_val0[s_index]<<"\n";
        unique_ptr<vector<double>> tempData;
        tempData.reset(new vector<double>);
        *tempData = getTrialData(s_val0[s_index],nval,1,randvec,true);
        //trialDatas.push_back(getTrialData(s_val0[s_index],n_vals[n_index]    vector<double> *tempData = new vector<double>;,1,randvec,true));
        string runName = "../../output/" + to_string(nval) + "_"+to_string(s_val0[s_index])+".csv";
        myfile.open(runName);
        for(int k=0; k<nval; k++){
            myfile << to_string(k) << ',' << to_string(tempData->at(k)) << endl;
            //myfile << to_string(k) << ',' << to_string(trialDatas[0][k]) << endl;
        }
        myfile.close();
        tempData.reset();
        

    }
    cout<<"wrote "<<nval<<"s_vals0"<<"\n";
    }

// int main(){
//     vector<double> s_val0{0.0, 0.225,0.25, 0.275, 0.5};
//     //n_vals should be in numerical order
//     vector<int> temp_n_vals{10, 100, 1000, 10000, 20000};
//     vector<int> n_vals;
//     for (int i : temp_n_vals){
//         n_vals.push_back(i);
//     }
//     RandVec randvec= RandVec(n_vals.back(),1);
//    	for(long unsigned int n_index=0; n_index < n_vals.size(); n_index++){
//     	// Runs through each s val for a given n val
//     	queue<future<vector<double>>> *tasks = new queue<future<vector<double>>>(); // make this pointer
//     	std::ofstream myfile;
//     	// Creates a name for the file
//     	myfile.open (runName);
//     		for (long unsigned int s_index=0; s_index<s_val0.size(); s_index++){
//     			tasks->push(
//     				async(launch::async, getTrialData, s_val0[s_index],n_vals[n_index], 1, randvec, true)
//     			);
//     		}		
//     		for(long unsigned int s_index=0; s_index<s_val0.size(); s_index++){
//     			string runName = "../../output/" + to_string(n_vals[n_index]) + "_"+to_string(s_val0[s_index])+".csv";
//                 myfile.open(runName);
//                 tasks->pop();
//     			std::cout << "Thread n=" << n_vals[n_index] << " s=" << s_val0[s_index] << endl;
//     	}
//     }
// }