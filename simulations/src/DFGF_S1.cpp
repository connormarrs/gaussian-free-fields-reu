#include "../headers/DFGF_S1.hpp"
#define _USE_MATH_DEFINES

/**
 * Constructor:
 *  
 */
DFGF_S1::DFGF_S1(double sVal, int nVal, int numberTrials, RandVec randVector) { 
	// set the parameters
	n = nVal;
	s = sVal;
	numTrials = numberTrials;

	/* copy array from randVector */
	vector<vector<double>> sampleArray = randVector.getSample(n);
	for(long unsigned int trial_index=0; trial_index<sampleArray.size(); trial_index++){
		vector<double> temp;
		for(long unsigned int point_index=0; point_index<sampleArray[trial_index].size(); point_index++){
			temp.push_back(sampleArray[trial_index][point_index]);
		}
		gaussianVector.push_back(temp);
	}

	// construct the eigenVals
	this->computeEigenVals();
	this->computeEigenVectors();
	this->computeCoeffs();
}

/**********************************************
 * 
 * 			SETUP COEFFICIENT METHODS
 * 
 **********************************************/

/**
 * @brief Computes the kth eigenvalue using the formula explained in the markdown.
 * 
 * @param r: the index of the eigenvalue to be computed.
 * 
 * @see Parameter r should be >= 1 in order to avoid the eigenvalue 0.
 * 
 * @return returns the rth eigenvalue
 */
double DFGF_S1::computeEigenVal(int r) {
	return pow(1.0*n,2.0)/(2.0*(pow(M_PI,2.0))) * (1.0-cos(2.0*M_PI*r/(1.0*n)));
}


/**
 * @brief Fills the array of eigenvalues with each eigenvalue.
 */
void DFGF_S1::computeEigenVals() {
	for(int r=0; r<n; r++){ 
		eigenVals.push_back(computeEigenVal(r));
	}
}

/**
 * @brief Computes the rth eigenfunction for the nth discrete laplacian
 * evaluated at the kth value.
 * 
 * @param r: which eigenvector to create (that is, )
 * @param k: the entry of the eigenvector
 * 
 * @return double the kth entry of the rth eigenvector
 */
double DFGF_S1::computeEigenFunctionPoint(int r, int k) {
	/* shortcut for computing the argument of trig functions */
	double arg = 2.0 * M_PI * r/n;
	
	//Accounts for Alternatning Sine Function
	if(n%2==0 && r==(n/2)) {
		return (M_SQRT2/2.0)*pow(-1.0, k);
	} else if(r<ceil(n/2.0)) {
		return (M_SQRT2/2.0)*cos(k*arg);
	} else {
		return (M_SQRT2/2.0)*sin(k*arg);
	}
}

/**
 * @brief computes the rth eigenvector
 * 
 * @param r which eigenvector to compute (e.g. the rth eigenvector)
 * @return vector<double> the rth eigenvector
 */
vector<double> DFGF_S1::computeEigenFunctionVector(int r){
	vector<double> eigenVector;
	for(int k = 0; k< n; k++){
		eigenVector.push_back(computeEigenFunctionPoint(r, k));
	}
	return eigenVector;
}

/**
 * @brief Compute each eigenvector and push them onto 2d array of eigenvectors
 */
void DFGF_S1::computeEigenVectors() {
	for(int r=1; r<n; r++){
		eigenVectors.push_back(computeEigenFunctionVector(r));
	}
}

/**
 * @brief compute the coefficient in the sum
 * 
 * @param r the index of term in summand
 * @param k the index of parameter passed to DFGF
 * @return double given by (lambda_r)^{-s}f_r(theta_k)
 */
double DFGF_S1::computeCoeffPoint(int r, int k){
	return pow(eigenVals[r], -1.0*s)*eigenVectors[r-1][k];
}

/**
 * @brief computes each coefficient for a fixed index r and each k
 * in the domain of the DFGF
 * 
 * @param r index of eigenvectors and eigenvalues to compute
 * @return vector<double> of coeff(r,k) for k in range(0,n)
 */
vector<double> DFGF_S1::computeCoefficientVector(int r){
	vector<double> coefficientVector;
	/* start indexing at 1 to not divide by 0 eigenvalue */
	for(int k = 0; k<n; k++){
		coefficientVector.push_back(computeCoeffPoint(r, k));
	}
	return coefficientVector;
}

/**
 * @brief function to compute the array of coefficients using multithreading
 */
void DFGF_S1::computeCoeffs() {
	// 2d vector of tasks for each entry of eigenvectors
	vector<future<vector<double>>> tasks;
	for(int r=1; r<n; r++){
		tasks.push_back(async(&DFGF_S1::computeCoefficientVector, this, r));
	}
	/* .size() returns long unsigned int */
	for(long unsigned int r=0; r<tasks.size(); r++){
		// pass in object with "this" keyword and multi-thread
		coefficients.push_back(tasks[r].get());
	}
}

/**********************************************
 * 
 * 				GETTER METHODS
 * 
 **********************************************/

/**
 * @brief Get the Eigen Vals object
 * 
 * @return vector<double> 
 */
vector<double> DFGF_S1::getEigenVals() {
	return eigenVals;
}

/**
 * @brief Get the Eigen Vectors object
 * 
 * @return vector<vector<double>> 
 */
vector<vector<double>> DFGF_S1::getEigenVectors() {
	return eigenVectors;
}

/**
 * @brief Get the Coefficients object
 * 
 * @return vector<vector<double>> 
 */
vector<vector<double>> DFGF_S1::getCoeffs(){
	return coefficients;
}


/**
 * @brief Get the Coefficients object
 * 
 * @return vector<vector<double>> 
 */
vector<vector<double>> DFGF_S1::getTrialData(){
	return trialData;
}

/**
 * @brief Get the Coefficients object
 * 
 * @return vector<vector<double>> 
 */
vector<double> DFGF_S1::getMaximaList(){
	return maxima;
}

/**
 * @brief Get the Coefficients object
 * 
 * @return vector<vector<double>> 
 */
double DFGF_S1::getEmpMean(){
	return meanOfMaxima;
}

/**********************************************
 * 
 * 			EVALUATE AND SAMPLE METHODS
 * 
 **********************************************/

/**
 * @brief computes the DFGF at point k given a sample of random numbers
 * 
 * @param k point in domain to evaluate (i.e. theta_k)
 * @param sampleVector vector of random numbers to evaluate
 * @return double DFGF(s,n,k)
 */
double DFGF_S1::evaluatePoint(int k, vector<double> sampleVector){
	double sum=0;
	for(int r = 1; r<n; r++){
		sum += coefficients[r-1][k]*sampleVector[r];
	}
	return sum;
}

/**
 * @brief computes the vector of points for this DFGF
 * 
 * @param sampleVector the vector of random numbers
 * @return vector<double> where kth entry if DFGF(s,n,k)
 */
vector<double> DFGF_S1::evaluate(vector<double> sampleVector){
	vector<double> dfgf;
	for(int k=0; k<n; k++){
		dfgf.push_back(this->evaluatePoint(k, sampleVector));
	}
	return dfgf;
}

/**
 * @brief samples numTrials samples and stores them in trialData
 */
void DFGF_S1::runTrials(){
	vector<future<vector<double>>> tasks;

	for(int i = 0; i < numTrials; i++){
		tasks.push_back(async(&DFGF_S1::evaluate, this, gaussianVector[i]));
	}
	for(long unsigned int i =0; i<tasks.size(); i++){
		trialData.push_back(tasks[i].get());
	}
	computeMaxVectors();
	computeEmpMean();
}

/**
 * @brief Compute a vector where the nth entry represents the
 * maximum of the DFGF computed for that nth trial.
 */
void DFGF_S1::computeMaxVectors(){
	vector<future<double>> tasks;
	for(long unsigned int j = 0; j<trialData.size(); j++){	
		tasks.push_back(std::async(Tools::compute_max, trialData[j]));
	}
	for(long unsigned int l = 0; l < tasks.size(); l++){
		maxima.push_back(tasks[l].get());
	}
}

/**
 * @brief 
 * 
 * @return double 
 */
void DFGF_S1::computeEmpMean(){
	double sum = 0;
	for(long unsigned int j=0; j<maxima.size(); j++){
		sum += maxima[j];
	}
	meanOfMaxima = sum/maxima.size();
}
