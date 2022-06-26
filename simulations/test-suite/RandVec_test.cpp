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
    RandVec Randvecs(25);
    vector<vector<double>> seqs; 
	std::vector<future<vector<double>>> tasks;
	RandVec RandVecs;
	for (int i; i<num_trials; i++){
		int param = num_vars;
        auto t = std::async(&RandVec::gen_rand_vec, &RandVecs, num_vars);
		tasks.push_back(std::move(t));
	}
	for (int i; i<num_trials; i++){
		vector<double> sequence = tasks[i].get();
		seqs.push_back(sequence);
	}
    //vector<vector<double>> AA = Randvecs.parallelSampler(num_vars,num_trials);
    vector<double> vals1=seqs[0];
    vector<double> vals2=seqs[1];
    vector<vector<double>> AB;
    AB.reserve( vals1.size() + vals2.size() ); // preallocate memory
    AB.insert( AB.end(), vals1.begin(), vals1.end() );
    AB.insert( AB.end(), vals2.begin(), vals2.end() );
    //PrintVector(AB);
    //vector<vector<double>> vals3 = t3.get();
    //vals.insert(vals1.end(), vals2.begin(), vals2.end());
    //vals.insert(vals.end(), vals3.begin(),vals3.end());
    // for (int i=0; i<AB.size(); i++){
    //    PrintVector(AB[i]);
    // }
    // for (int i=0; i<vals2.size(); i++){
    //    PrintVector(vals2[i]);
    // }
    for (int i=0; i<AB.size(); i++){
       PrintVector(AB[i]);
    }
    cout << "Sample Covariance is "<<sampleCov(vals1,vals2)<<"\n";


}