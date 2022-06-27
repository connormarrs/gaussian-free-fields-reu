#ifndef TOOLS_H
#define TOOLS_H

#define _USE_MATH_DEFINES

#include <float.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <fstream>
#include <chrono>
#include <cstdint>
#include <future>
using namespace std;

class Tools {
    public:
        static vector<int> linspace(int start_in, int end_in, int num_in);
		static vector<double> fracpowers(int start_in, int end_in, int num_in,double s, int thread_num);
		static vector<double> joinVecs(vector<double> A, vector<double> B);
		static vector<double> exponentiate(vector<int> A, double s, int start, int stop);
		static void printVector(vector<double> input);
		static double sampleMean(vector<double> data);
		static double compute_max(vector<double> data);
		static void prINTVector(vector<int> input);
};
 
// vector<int> Tools::linspace(int start_in, int end_in, int num_in) {
// 	vector<int> linspaced;
	
// 	int start = static_cast<int>(start_in);
// 	int end = static_cast<int>(end_in);
// 	int num = static_cast<int>(num_in);
	
// 	if (num == 0) { 
// 		return linspaced; 
// 	}
// 	if (num == 1) {
// 		linspaced.push_back(start);
// 		return linspaced;
// 	}
	
// 	int delta = (end - start) / (num - 1);
	
// 	for(int i=0; i < num-1; ++i) {
// 		linspaced.push_back(start + delta * i);
// 	}
	
// 	return linspaced;
// }

// vector<double> Tools::exponentiate(vector<int> A, double s, int start, int stop){
// 	// this function will help streamline the code for multi threading
// 	vector<double> result;
// 	for (int i=start; i <stop; i++){

// 		result.push_back(pow(A[i],s));

// 	}
// 	return result;
// }

// // vector printer from https://github.com/ourarash/multithreading_cpp
// void Tools::printVector(vector<double> input) {
//   cout << "input size is " << int(input.size());
//   std::cout << "{ ";
//   for (int n=0; n< input.size(); n++) {

//     std::cout << input[n];
//     if (n < input.size()) std::cout << ", ";
//   }
//   std::cout << " }" << std::endl;
// }


// // vector printer from https://github.com/ourarash/multithreading_cpp
// void Tools::prINTVector(vector<int> input) {
//   cout << "input size is " << int(input.size());
//   std::cout << "{ ";
//   for (int n=0; n< input.size(); n++) {

//     std::cout << input[n];
//     if (n < input.size()) std::cout << ", ";
//   }
//   std::cout << " }" << std::endl;
// }


// vector<double> Tools::joinVecs(vector<double> A, vector<double> B){
// 	// quick vector joining method from https://stackoverflow.com/questions/3177241/what-is-the-best-way-to-concatenate-two-vectors
// 	vector<double> AB;
// 	AB.reserve( A.size() + B.size() ); // preallocate memory
// 	AB.insert( AB.end(), A.begin(), A.end() );
// 	AB.insert( AB.end(), B.begin(), B.end() );
// 	return AB;
// }


// //fractional powers of large integers take a long time to compute. We can speed this up with multithreading.
// // vector<double> Tools::fracpowers(int start_in, int end_in, int num_in, double s, int thread_num){
// // 	Tools tools;
// // 	vector<int> n_vals= linspace(start_in, end_in, num_in);
// // 	int thread_intervals = int(num_in/thread_num);
// // 	vector<future<vector<double>>> tasks;
// // 	for(int i=0; i < thread_intervals; i++){
// // 		if (i<thread_intervals-1){
// // 			tasks.push_back(std::async(Tools::exponentiate, n_vals, s, int(i*thread_intervals), int((i+1)*thread_intervals)));
// // 		}
// // 		else{
// // 			tasks.push_back(std::async(Tools::exponentiate, n_vals, s, i*thread_intervals, n_vals.size()));	
// // 		}
// // 	}
// // 	vector<double> powers;
// // 	for (int i =0; i< tasks.size(); i++){

// // 		powers=Tools::joinVecs(powers, tasks[i].get());
// // 	}
// // 	return powers;
// // }



// double Tools::sampleMean(vector<double> data){
//     double sum=0;
//     int limit = data.size();
//     for (int i=0; i<limit; i++){
//         sum+= data[i];
//     }
//     if (limit>0){
//         return sum/limit;
//     }
//     else{
//         cout<<"division by zero error";
//     }
//     return 0;
// }
// double Tools::compute_max(vector<double> data) {
// 	// iterate over all angles 2pik/n
// 	double max = data[0]; // dfgf(); // set max to smallest possible values computer knows
// 	for(int k=1; k<data.size(); k++){
// 		// if we find larger value replace it
// 		if(data[k] > max) {
// 			max = data[k];
// 		}
// 	}
// 	return max;
// }


#endif