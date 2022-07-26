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

vector<double> s_val0{0.225,0.25, 0.275};
vector<double> s_val1{0.0,0.5};
//n_vals should be in numerical order
vector<int> n_vals{50,100,500,1000};
int max_n = n_vals[n_vals.size()-1];
RandVec randvec = RandVec(max_n,1);


int main(){
    cout<<"entering loop";
    for(unsigned int n_index = 0; n_index<n_vals.size(); n_index++){
        vector<vector<double>> trialDatas;
        for(unsigned int s_index = 0; s_index<s_val0.size(); s_index ++){
            DFGF_S1 *dfgf = new DFGF_S1(s_val0[s_index],n_vals[n_index],1, randvec, true);
            dfgf->runTrials();
            cout<<dfgf->getTrialData().size();
            vector<double> tempData = dfgf->getTrialData()[0];
            cout<<"before first pushback";
            trialDatas.push_back(tempData);

        }
        for(unsigned int s_index = 0; s_index<s_val0.size(); s_index ++){
            string runName = "../../output/" + to_string(n_vals[n_index]) + "_"+to_string(s_val0[s_index])+".csv";
            std::ofstream myfile;
            myfile.open(runName);
            for(unsigned int k=0; k<trialDatas[s_index].size(); k++){
                myfile << to_string(k) << ',' << to_string(trialDatas[s_index][k]) << endl;
           }

        }
        cout<<"wrote "<<n_vals[n_index]<<"s_vals0";
    }
    for(unsigned int n_index = 0; n_index<n_vals.size(); n_index++){
        vector<vector<double>> trialDatas;
        for(unsigned int s_index = 0; s_index<s_val1.size(); s_index ++){
            DFGF_S1 *dfgf = new DFGF_S1(s_val1[s_index],n_vals[n_index],1, randvec, true);
            dfgf->runTrials();
            vector<double> tempData = dfgf->getTrialData()[0];
            trialDatas.push_back(tempData);

        }
        for(unsigned int s_index = 0; s_index<s_val1.size(); s_index ++){
            string runName = "../../output/" + to_string(n_vals[n_index]) + "_"+to_string(s_val1[s_index])+".csv";
            std::ofstream myfile;
            myfile.open(runName);
            for(unsigned int k=0; k<trialDatas[s_index].size(); k++){
                myfile << to_string(k) << ',' << to_string(trialDatas[s_index][k]) << endl;
           }

        }
        cout<<"wrote "<<n_vals[n_index]<<"s_vals0";
    }
    return 0;
}