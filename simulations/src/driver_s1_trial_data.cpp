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
vector<double> s_val0{0.0,0.5};
vector<int> n_vals{50,100,500,1000};

RandVec randvec = RandVec(1000,1);

for(unsigned int n_index = 0; n_index<n_vals.size(); n_index++){
    for(unsigned int s_index = 0; s_index<s_val0.size(); s_index ++){
       //string runName = "../../output/" + to_string(n_vals[n_index]) + "_"+to_string(s_val0[s_index])+".csv"; 
       int s =2;
    }

}
for(unsigned int n_index = 0; n_index <n_vals.size(); n_index ++){
}