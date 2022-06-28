#include "../headers/RandVec.hpp"
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <future>

using namespace std;

int num_vars=1000000;
int num_trials=2;
vector<vector<double>> generateTestingVectors(int num_var, int num_trial){
    vector<vector<double>> randomVecs;
    for (int j=0; j < num_trials; j++){
        RandVec RandVecs(num_var);
        unsigned randSeed= RandVecs.timeSinceEpochMillisec();
        vector<double> vec = RandVecs.gen_rand_vec(num_var);
        randomVecs.push_back(vec);
    }

    return randomVecs;

}

// vector printer from https://github.com/ourarash/multithreading_cpp
void PrintVector(std::vector<double> input) {
  cout << "input size is " << int(input.size());
  std::cout << "{ ";
  for (int n=0; n< input.size(); n++) {

    std::cout << input[n];
    if (n < input.size()) std::cout << ", ";
  }
  std::cout << " }" << std::endl;
}

double sampleMean(vector<double> data){
    double sum=0;
    int limit = data.size();
    for (int i=0; i<limit; i++){
        sum+= data[i];
    }
    if (limit>0){
        return sum/limit;
    }
    else{
        cout<<"division by zero error";
    }
    return 0;
}
double sampleCov(vector<double> data1, vector<double> data2){
    double sum=0;
    int limit = data1.size();
    if (data1.size()==data2.size()){
        for (int i=0; i<limit; i++){
            sum+= data1[i]*data2[i];
        }
        if (limit>0){
            return sum/limit-(sampleMean(data1)*sampleMean(data2));
        }
        else{
            cout<<"division by zero error";
        }
    }
    return 0;
}
    

int main() {
    int num_vars=100000;
    int num_trials=3;
    //auto k = generateTestingVectors(num_vars,num_trials);
    //PrintVector(k[0]);
    RandVec Randvecs(num_vars);
    cout<<"t1\n";
    vector<vector<double>> AA = Randvecs.parallelSampler(num_vars,num_trials);
    cout<<sampleCov(AA[0],AA[1])<<"\n";
    return 0;
}