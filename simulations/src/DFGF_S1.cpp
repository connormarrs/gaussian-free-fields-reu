#include "../headers/DFGF_S1.hpp"
#define _USE_MATH_DEFINES
#define _USE_MATH_DEFINES

/**
 * Class that models the Discrete Gaussian Free Field on the circle S^1.
 */
DFGF_S1::DFGF_S1(double sVal, int nVal, int numberTrials, RandVec randVector) { 
	// set the parameters
	n = nVal;
	s = sVal;
	gaussianVector = randVector;
	numTrials = numberTrials;

	// construct the eigenVals
	cout<<"calculating: "<<n<<"\n";
	this->computeEigenVals();
	this->computeEigenVectors();
	this->computeCoefficients();



	//this may be a little extreme for some uses (maybe we dont want to run these in the constructor)
	this->runTrials();
	this -> parallelMax();
	meanOfMaxima = Tools::sampleMean(maxima);
}

/**
 * Computes the kth eigenvalue for the nth discrete laplacian
 */
double DFGF_S1::computeEigenVal(int k) {
	return pow(1.0*n,2.0)/(2.0*(pow(M_PI,2.0))) * (1.0-cos(2.0*M_PI*k/(1.0*n)));
}

/**
 * Computes the rth eigenvalue for the nth discrete laplacian
 */
void DFGF_S1::computeEigenVals() {
	vector<future<double>> tasks;
	// for(int k=1; k<n; k++){
	// 	// pass in object with "this" keyword and multi-thread
	// 	tasks.push_back(
	// 		async([this](int k)-> double {
    //         return this->computeEigenVal(k);
    //     }, k)
	// 	);
	// }

	// for(int j=0; j<tasks.size(); j++){
	// 	eigenVals.push_back(tasks[j].get());
	// }
	for(int k=1; k<n; k++){
		eigenVals.push_back(computeEigenVal(k));
	}

}

/**
 * Computes the rth eigenfunction for the nth discrete laplacian
 * evaluated at the kth value.
 */
double DFGF_S1::computeEigenVector(int r, int k) {

	double arg = 2.0 * M_PI * k/n;

	if(n%2==0 && r==(n/2)) {
		return pow(-1.0, k);
	} else if(r<ceil((1.0*n)/2.0)) {
		return (M_SQRT2/2.0)*cos(r*arg);
	} else {
		return (M_SQRT2/2.0)*sin(r*arg);
	}
}

vector<double> DFGF_S1::computeFullEigenVector(int r){
	vector<double> eigenVector;
	for(int k = 0; k< n-1; k++){
		eigenVector.push_back(computeEigenVector(r, k));
	}
	return eigenVector;
}

/**
 * Computes the rth eigenvalue for the nth discrete laplacian
 */
void DFGF_S1::computeEigenVectors() {
	// 2d vector of tasks for each entry of eigenvectors
	vector<future<vector<double>>> tasks;
	// for(int r=0; r<n-1; r++){
	// 	tasks.push_back(async(&DFGF_S1::computeFullEigenVector, this, r));
	// }

	// for(int r=0; r<tasks.size(); r++){
	// 	// pass in object with "this" keyword and multi-thread
	// 		eigenVectors.push_back(tasks[r].get());
	// }
	for(int r=1; r<n; r++){
		eigenVectors.push_back(computeFullEigenVector(r));
	}

}

double DFGF_S1::computeCoeff(int r, int k){
	return pow(eigenVals[r], -1.0*s)*eigenVectors[r][k];
}

vector<double> DFGF_S1::computeFullCoefficients(int r){
	vector<double> coefficientVector;
	for(int k = 1; k< n; k++){
		coefficientVector.push_back(computeCoeff(r, k));
	}
	return coefficientVector;
}

/**
 * Computes the rth eigenvalue for the nth discrete laplacian
 */
void DFGF_S1::computeCoefficients() {
	// 2d vector of tasks for each entry of eigenvectors
	vector<future<vector<double>>> tasks;
	for(int r=0; r<n-1; r++){
		tasks.push_back(async(&DFGF_S1::computeFullCoefficients, this, r));
	}
	for(int r=0; r<tasks.size(); r++){
		// pass in object with "this" keyword and multi-thread
		coefficients.push_back(tasks[r].get());
	}
	for(int r = 0; r<n-1; r++){
		coefficients.push_back(computeFullCoefficients(r));
	}
	// cout<<"printing coefficients\n";
	// for(int i =0; i<coefficients.size();i++){
	// 	cout<<(coefficients[i].size())<<"\n";
	// 	Tools::printVector(coefficients[i]);
	//}
	}


// helper to compute the value of the DFGF at a particular theta_k
double DFGF_S1::evaluatePoint(int k, vector<double> sampleVector){
	double sum=0;
	for(int i = 0; i<n-1; i++){
		//cout<<"term is "<<coefficients[i][k]*sampleVector[i]<<"\n";
		sum += coefficients[i][k]*sampleVector[i];
	}
	return sum;
}
// evaluates the DFGF on S1 at each theta_k and returns a vector of the values
vector<double> DFGF_S1::evaluate(vector<double> sampleVector){
	vector<double> dfgf;

	for(int k=0; k<n-1; k++){
		dfgf.push_back(this->evaluatePoint(k, sampleVector));
	}
	vector<future<double>> tasks;
	// for(int k=0; k<n-1; k++){//k=0 to n-1?
	// 	tasks.push_back(async(&DFGF_S1::evaluatePoint, this, k, sampleVector));
	// }
	// for(int k=0; k<tasks.size(); k++){
	// 	dfgf.push_back(tasks[k].get());
	// }
	return dfgf;
}
// creates a matrix where the ith row is the DFGF in the ith trial
void DFGF_S1::runTrials(){
	vector<future<vector<double>>> tasks;
	vector<vector<double>> sampleArray= gaussianVector.parallelSampler(n, numTrials);
	vector<vector<double>> data;
	for(int i = 0; i < numTrials; i++){
		//Tools::printVector(sampleArray[i]);
		tasks.push_back(async(&DFGF_S1::evaluate, this, sampleArray[i]));
	}
	for(int i =0; i<tasks.size(); i++){
		data.push_back(tasks[i].get());
	}
	trialData = data;
	// cout<<"printing data\n";
	// for (int i =0; i < trialData.size();i++){
	// 	Tools::printVector(trialData[i]);
	// }
}


// returns vector containing the maxima of each row of a matrix
void DFGF_S1::parallelMax(){
	vector<future<double>> tasks;
	for(int j = 0; j<trialData.size(); j++){	
		tasks.push_back(std::async(Tools::compute_max, trialData[j]));
		}
	for(int l = 0; l < tasks.size(); l++){
		maxima.push_back(tasks[l].get());
	}
	// for(int j = 0; j<trialData.size(); j++){	
	// 	maxima.push_back(Tools::compute_max(trialData[j]));
	// 	}
	
}

double DFGF_S1::getMeanOfMaxima(){
	return meanOfMaxima;
}