#include "../headers/tools.hpp"
using namespace std;
// takes in a start, end, and an interval to generate a vector of n values for testing
vector<int> Tools::linspace(int start_in, int end_in, int num_in) {
	vector<int> linspaced;
	
	int start = static_cast<int>(start_in);
	int end = static_cast<int>(end_in);
	int num = static_cast<int>(num_in);
	
	if (num == 0) { 
		return linspaced; 
	}
	if (num == 1) {
		linspaced.push_back(start);
		return linspaced;
	}
	
	int delta = (end - start) / (num - 1);
	
	for(int i=0; i < num-1; ++i) {
		linspaced.push_back(start + delta * i);
	}
	
	return linspaced;
}
// exponentiates each component of a vector
vector<double> Tools::exponentiate(vector<int> A, double s, int start, int stop){
	// this function will help streamline the code for multi threading
	vector<double> result;
	for (int i=start; i <stop; i++){

		result.push_back(pow(A[i],s));

	}
	return result;
}

// vector printer from https://github.com/ourarash/multithreading_cpp
// for double vectors
void Tools::printVector(vector<double> input) {
  cout << "input size is " << int(input.size());
  std::cout << "{ ";
  for (int n=0; n< input.size(); n++) {

    std::cout << input[n];
    if (n < input.size()) std::cout << ", ";
  }
  std::cout << " }" << std::endl;
}


// vector printer from https://github.com/ourarash/multithreading_cpp
// for integer vectors
void Tools::prINTVector(vector<int> input) {
  cout << "input size is " << int(input.size());
  std::cout << "{ ";
  for (int n=0; n< input.size(); n++) {

    std::cout << input[n];
    if (n < input.size()) std::cout << ", ";
  }
  std::cout << " }" << std::endl;
}

// joins a vector of doubles into one vector
vector<double> Tools::joinVecs(vector<double> A, vector<double> B){
	// quick vector joining method from https://stackoverflow.com/questions/3177241/what-is-the-best-way-to-concatenate-two-vectors
	vector<double> AB;
	AB.reserve( A.size() + B.size() ); // preallocate memory
	AB.insert( AB.end(), A.begin(), A.end() );
	AB.insert( AB.end(), B.begin(), B.end() );
	return AB;
}

double Tools::sampleMean(vector<double> data){
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
double Tools::compute_max(vector<double> data) {
	// iterate over all angles 2pik/n
	double max = data[0]; // dfgf(); // set max to smallest possible values computer knows
	for(int k=1; k<data.size(); k++){
		// if we find larger value replace it
		if(data[k] > max) {
			max = data[k];
		}
	}
	return max;
}


// code from this example https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9
//times parallelDFGF
vector<vector<vector<double>>> Tools::time_method1(double s, int start_in, int end_in, int num_in, int size, int num_seqs, vector<vector<vector<double>>>(*func)(double, int, int, int ,int, int)){
    auto begin = std::chrono::high_resolution_clock::now();
	cout<<"calculating datatensor \n";
	
	vector<vector<vector<double>>> datatensor = func(s, start_in, end_in, num_in, size, num_seqs);
	 
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	cout <<"time for parallelDFGF is "<<elapsed.count()<<"\n";
	return datatensor;
}

//times parallelDFGF
vector<vector<double>> Tools::time_method2(vector<vector<vector<double>>> datatensor, vector<vector<double>> (*func)(vector<vector<vector<double>>>)){
    auto begin = std::chrono::high_resolution_clock::now();
	cout<<"calculating maximat \n";
	
	vector<vector<double>> maximat = func(datatensor);
	 
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	cout <<"time for parallelMax is "<<elapsed.count()<<"\n";
	return maximat;
}

//times parallelDFGF
vector<double> Tools::time_method3(vector<vector<double>> maximat, vector<double>(*func)(vector<vector<double>>)){
    auto begin = std::chrono::high_resolution_clock::now();
	cout<<"calculating exmax \n";
	vector<double> exmax = func(maximat);
	 
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	cout <<"time for parallelMean is "<<elapsed.count()<<"\n";
	return exmax;
}


























//fractional powers of large integers take a long time to compute. We can speed this up with multithreading.
// vector<double> Tools::fracpowers(int start_in, int end_in, int num_in, double s, int thread_num){
// 	Tools tools;
// 	vector<int> n_vals= linspace(start_in, end_in, num_in);
// 	int thread_intervals = int(num_in/thread_num);
// 	vector<future<vector<double>>> tasks;
// 	for(int i=0; i < thread_intervals; i++){
// 		if (i<thread_intervals-1){
// 			tasks.push_back(std::async(Tools::exponentiate, n_vals, s, int(i*thread_intervals), int((i+1)*thread_intervals)));
// 		}
// 		else{
// 			tasks.push_back(std::async(Tools::exponentiate, n_vals, s, i*thread_intervals, n_vals.size()));	
// 		}
// 	}
// 	vector<double> powers;
// 	for (int i =0; i< tasks.size(); i++){

// 		powers=Tools::joinVecs(powers, tasks[i].get());
// 	}
// 	return powers;
// }