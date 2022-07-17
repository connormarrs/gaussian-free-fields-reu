#include "../headers/DFGF_T2.hpp"

void DFGF_T2::computeEigenVals(){

}
double DFGF_T2::computeEigenVal(int p, int q){

}
void DFGF_T2::computeEigenVectors(){

}
void DFGF_T2::computeCoeffs(){

}
void DFGF_T2::computeMaxVectors(){
    
    for(i = 0; i<trialData.size();i++){
        int max=trialData[i][0][0]
        for(j = 0; j<trialData[i].size();j++){
            for(k= 0; k<trialData[i][j].size()){
                if(trialData[i][j][k]>max){
                    max=trialData[i][j][k];
                }
            }
        }
        maxima.push_back(max);
    }
}

// constructors
DFGF_T2::DFGF_T2(double sVals, int nVals, int numberTrials, vector<RandVec> gaussianVector){
	// set the parameters
	n = nVal;
	s = sVal;
	gaussianVector = randVector;
	numTrials = numberTrials;

	// construct the eigenVals
	this->computeEigenVals();
	this->computeEigenVectors();
	this->computeCoeffs();
}
vector<vector<double>> DFGF_T2::getEigenVals(){

}
/* returns f_p,q(theta_j, theta_k) */
double DFGF_T2::computeEigenFunctionPoint(int p, int q, int j, int k){

}
/* returns 2d vector containing f_p,q(j,k) at each point (j,k) in grid */
vector<vector<double>> DFGF_T2::computeEigenFunctionVector(int p, int q){

}
/* return the 4d array of all values f_p,q(j,k )*/
vector<vector<vector<vector<double>>>>  DFGF_T2::getEigenVectors(){

}

/* returns f_p,q(theta_j, theta_k) */
double DFGF_T2::computeCoefficientPoint(int p, int q, int j, int k){

}
/* returns 2d vector containing f_p,q(j,k) at each point (j,k) in grid */
vector<vector<double>> DFGF_T2::computeCoefficientVector(int p, int q){

}
/* return the 4d array of all values f_p,q(j,k )*/
vector<vector<vector<vector<double>>>>  DFGF_T2::getCoefficients(){

}

/* returns value of DFGF at point (j,k) in grid */
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
/* returns 2d array containing values of DFGF at each point given the sample random vector*/
vector<vector<double>> DFGF_T2::evaluate(vector<vector<double>> sampleVector){
    vector<vector<double>> dfgf;
    for(int j=0; j<n; j++){
        vector<double> dfgfRow;
        for(int k=0; k<n; k++){
            dfgfRow.push_back(this->evaluatePoint(j,k), sampleVector);
        }
        dfgf.push_back(dfgfRow)
    }
    return dfgf
}

void DFGF_T2::runTrials(){
	vector<future<vector<double>>> tasks;
	/* get the sample data from gaussianVector but scale size for DFGF */
	vector<vector<vector<double>>> sampleArray;
    for(i = 0; i<numTrials; i++){
        sampleArray.push_back(gaussianVector.getSampleArray(n));
    }

	for(int i = 0; i < numTrials; i++){
		tasks.push_back(async(&DFGF_T2::evaluate, this, sampleArray[i]));
	}
	for(long unsigned int i =0; i<tasks.size(); i++){
		trialData.push_back(tasks[i].get());
	}
}
double DFGF_T2::computeEmpMean(){

}