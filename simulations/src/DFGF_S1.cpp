#include "../headers/DFGF_S1.hpp"
#define _USE_MATH_DEFINES

#define _USE_MATH_DEFINES

/**
 * Class that models the Discrete Gaussian Free Field on the circle S^1.
 */
DFGF_S1::DFGF_S1(double s) { 
	s = s;
	// n = n_val;
	// // Set the values of k 
	// for(int k=0; k<n; k++) {
	// 	k_vals[k] = 2.0 * M_PI * k/n;
	// }
	// z_vars = rand_vector; // construct random vector of size n
}

/**
 * Computes the rth eigenvalue for the nth discrete laplacian
 */
double DFGF_S1::eigval(int r, int n) {
	return pow(1.0*n,2.0)/(2.0*(pow(M_PI,2.0))) * (1.0-cos(2.0*M_PI*r/(1.0*n)));
}

/**
 * Computes the rth eigenfunction for the nth discrete laplacian
 * evaluated at the kth value.
 */
double DFGF_S1::eigfcn(int r, int j, int n) {
	vector<double> k_vals;
	for(int k=0; k<n; k++) {
		k_vals.push_back(2.0 * M_PI * k/n);
	}
	if(n%2==0 && r==(n/2)) {
		return pow(-1.0, j);
	} else if(r<ceil((1.0*n)/2.0)) {
		return (M_SQRT2/2.0)*cos(r*k_vals[j]);
	} else {
		return (M_SQRT2/2.0)*sin(r*k_vals[j]);
	}
}

// helper function to compute 
double DFGF_S1::dfgf(int k,int n, double s, vector<double> z_vars){
	// loop through eigenfunctions
	double sum = 0.0;
	//vector<double> z_vals = z_vars.gen_rand_vec(n);
	for(int r = 1; r<n; r++){
		sum += pow(eigval(r, n),-1.0*s)*eigfcn(r,k, n)*z_vars[r];
	}

	return sum;
}

/**
 * 
 * 
 */

vector<double> DFGF_S1::FullDFGF_S1(double s, int n, vector<double> randomVector){
	DFGF_S1 dfgfs1(s);
	
	vector<double> DFGF;
	vector<future<double>> tasks;
	for(int k=0; k<n; k++){
		tasks.push_back(std::async(&DFGF_S1::dfgf, &dfgfs1, k, n, s, randomVector));
	}
	for (int j = 0; j< tasks.size(); j++){
		DFGF.push_back(tasks[j].get());
	}
	return DFGF;
}

vector<vector<vector<double>>> DFGF_S1::parallelDFGF(double s, int start_in, int end_in, int num_in, int size, int num_seqs){
	RandVec RandVecs(size);
	vector<int> trialns = Tools::linspace(start_in, end_in, num_in);

	vector<vector<vector<double>>> dfgftensor;
	for(int n = 0; n < trialns.size(); n++){
		cout<<"     calculating n="<<trialns[n]<<"\n";
		vector<vector<double>> dfgfmat;
		vector<vector<double>> z_seqs = RandVecs.parallelSampler(trialns[n], num_seqs);
		for(int t = 0; t< num_seqs; t++){
			DFGF_S1 dfgf_s1(0.25);
			vector<double> fgf = dfgf_s1.FullDFGF_S1(s, trialns[n], z_seqs[t]);
			dfgfmat.push_back(fgf);
		}
		dfgftensor.push_back(dfgfmat);
	}
	return dfgftensor;
}

vector<vector<double>> DFGF_S1::parallelMax(vector<vector<vector<double>>> data){
	vector<vector<double>> maximamat;
	for(int i = 0; i<data.size(); i++){
		vector<future<double>> tasks;
		vector<double> maxima;
		for(int j = 0; j<data[i].size(); j++){
			tasks.push_back(std::async(Tools::compute_max, data[i][j]));
			}
		for(int l = 0; l < tasks.size(); l++){
			maxima.push_back(tasks[l].get());
		}
		maximamat.push_back(maxima);
		}
		return maximamat;
	}

vector<double> DFGF_S1::parallelMeans(vector<vector<double>> data){
	vector<future<double>> tasks;
	vector<double> exMaxima;
	for(int i = 0; i<data.size(); i++){
		tasks.push_back(std::async(Tools::sampleMean, data[i]));
	}
	for(int i = 0; i<tasks.size(); i++){
		exMaxima.push_back(tasks[i].get());
	}
	return exMaxima;
}









































// /**
//  * Class that models the Discrete Gaussian Free Field on the circle S^1.
//  */
// DFGF_S1::DFGF_S1(double s_val, int n_val, RandVec rand_vector) { 
// 	s = s_val;
// 	n = n_val;
// 	// Set the values of k 
// 	for(int k=0; k<n; k++) {
// 		k_vals[k] = 2.0 * M_PI * k/n;
// 	}
// 	z_vars = rand_vector; // construct random vector of size n
// }

// /**
//  * Computes the rth eigenvalue for the nth discrete laplacian
//  */
// double DFGF_S1::eigval(int r) {
// 	return pow(1.0*n,2.0)/(2.0*(pow(M_PI,2.0))) * (1.0-cos(2.0*M_PI*r/(1.0*n)));
// }

// /**
//  * Computes the rth eigenfunction for the nth discrete laplacian
//  * evaluated at the kth value.
//  */
// double DFGF_S1::eigfcn(int r, int k) {
// 	if(n%2==0 && r==(n/2)) {
// 		return pow(-1.0, k);
// 	} else if(r<ceil((1.0*n)/2.0)) {
// 		return (M_SQRT2/2.0)*cos(r*k_vals[k]);
// 	} else {
// 		return (M_SQRT2/2.0)*sin(r*k_vals[k]);
// 	}
// }

// // helper function to compute 
// double DFGF_S1::dfgf(int k){
// 	// loop through eigenfunctions
// 	double sum = 0.1;
// 	vector<double> z_vals = z_vars.gen_rand_vec(n);
// 	for(int r = 1; r<n; r++){
// 		sum += pow(eigval(r),-1.0*s)*eigfcn(r,k)*z_vals[r];
// 	}

// 	return sum;
// }

// /**
//  * 
//  * 
//  */
// double DFGF_S1::compute_max() {
// 	// iterate over all angles 2pik/n
// 	double max = dfgf(0); // dfgf(); // set max to smallest possible values computer knows
// 	for(int k=1; k<n; k++){
// 		// if we find larger value replace it
// 		if(dfgf(k) > max) {
// 			max = dfgf(s);
// 		}
// 	}
// 	return max;
// }
