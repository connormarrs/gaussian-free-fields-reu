#include "../headers/DFGF_T2.hpp"

/**
 * @brief 
 * 
 */
void DFGF_T2::computeEigenVals(){

}

/**
 * @brief 
 * 
 * @param p 
 * @param q 
 * @return double 
 */
double DFGF_T2::computeEigenVal(int p, int q){

}

/**
 * @brief 
 * 
 */
void DFGF_T2::computeEigenVectors(){

}

/**
 * @brief 
 * 
 */
void DFGF_T2::computeCoeffs(){

}

/**
 * @brief 
 * 
 */
void DFGF_T2::computeMaxVectors(){
    
    for(unsigned long int i = 0; i<trialData.size();i++){
        int max=trialData[i][0][0];
        for(unsigned long int j = 0; j<trialData[i].size();j++){
            for(unsigned long int k= 0; k<trialData[i][j].size(); k++){
                if(trialData[i][j][k]>max){
                    max=trialData[i][j][k];
                }
            }
        }
        maxima.push_back(max);
    }
}

/**
 * @brief Construct a new dfgf t2::dfgf t2 object
 * 
 * @param sVals 
 * @param nVals 
 * @param numberTrials 
 * @param gaussianVector 
 */
DFGF_T2::DFGF_T2(double sVals, int nVals, int numberTrials, vector<RandVec> gaussianVector){
	// set the parameters
	n = nVals;
	s = sVals;
	gaussianVector = gaussianVector;
	numTrials = numberTrials;

	// construct the eigenVals
	this->computeEigenVals();
	this->computeEigenVectors();
	this->computeCoeffs();
}

/**
 * @brief 
 * 
 * @return vector<vector<double>> 
 */
vector<vector<double>> DFGF_T2::getEigenVals(){

}

/**
 * @brief returns f_p,q(theta_j, theta_k)
 * 
 * @param p 
 * @param q 
 * @param j 
 * @param k 
 * @return double 
 */
double DFGF_T2::computeEigenFunctionPoint(int p, int q, int j, int k){

}

/**
 * @brief returns 2d vector containing f_p,q(j,k) at each point (j,k) in grid
 * 
 * @param p 
 * @param q 
 * @return vector<vector<double>> 
 */
vector<vector<double>> DFGF_T2::computeEigenFunctionVector(int p, int q){

}

/**
 * @brief return the 4d array of all values f_p,q(j,k )
 * 
 * @return vector<vector<vector<vector<double>>>> 
 */
vector<vector<vector<vector<double>>>>  DFGF_T2::getEigenVectors(){

}

/**
 * @brief returns f_p,q(theta_j, theta_k)
 * 
 * @param p 
 * @param q 
 * @param j 
 * @param k 
 * @return double 
 */
double DFGF_T2::computeCoefficientPoint(int p, int q, int j, int k){

}

/**
 * @brief returns 2d vector containing f_p,q(j,k) at each point (j,k) in grid
 * 
 * @param p 
 * @param q 
 * @return vector<vector<double>> 
 */
vector<vector<double>> DFGF_T2::computeCoefficientVector(int p, int q){

}

/**
 * @brief return the 4d array of all values f_p,q(j,k )
 * 
 * @return vector<vector<vector<vector<double>>>> 
 */
vector<vector<vector<vector<double>>>>  DFGF_T2::getCoefficients(){

}

/**
 * @brief returns value of DFGF at point (j,k) in grid
 * 
 * @param j 
 * @param k 
 * @param sampleVector 
 * @return double 
 */
double DFGF_T2::evaluatePoint(int j, int k, vector<vector<double>> sampleVector){
    double sum = 0;
    //make sure this works with the dummy zero coefficients
    for(int p=0; p<n; p++){
        for(int q=0; q<n; q++){
            sum += coefficients[p][q][j][k]*sampleVector[p][q];
        }
    }
    return sum;
}

/**
 * @brief returns 2d array containing values of DFGF at each point given the sample random vector
 * 
 * @param sampleVector 
 * @return vector<vector<double>> 
 */
vector<vector<double>> DFGF_T2::evaluate(vector<vector<double>> sampleVector){
    vector<vector<double>> dfgf;
    for(int j=0; j<n; j++){
        vector<double> dfgfRow;
        for(int k=0; k<n; k++){
            dfgfRow.push_back(this->evaluatePoint(j,k, sampleVector));
        }
        dfgf.push_back(dfgfRow);
    }
    return dfgf;
}

/**
 * @brief 
 * 
 */
void DFGF_T2::runTrials(){
    /* instantiate a vector of tasks */
	vector<future<vector<vector<double>>>> tasks;
    vector<vector<vector<double>>> rand_vals = gaussianArray.getSample(this->n);

	for(int i = 0; i < numTrials; i++){
		tasks.push_back(
            async(&DFGF_T2::evaluate, this, rand_vals[i])
        );
	}

	for(long unsigned int i =0; i<tasks.size(); i++){
		trialData.push_back(
            tasks[i].get()
        );
	}
}

/**
 * @brief 
 * 
 * @return double 
 */
double DFGF_T2::computeEmpMean(){

}