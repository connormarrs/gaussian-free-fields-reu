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

}

// constructors
DFGF_T2::DFGF_T2(double s, int n, int numberTrials, RandVec gaussianVector){

}
DFGF_T2::DFGF_T2()=default{

}
DFGF_T2::~DFGF_T2()=default{

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
double DFGF_T2::evaluatePoint(int j, int k, vector<double> sampleVector){

}
/* returns 2d array containing values of DFGF at each point given the sample random vector*/
vector<vector<double>> DFGF_T2::evaluate(vector<double> sampleVector){

}

void DFGF_T2::runTrials(){

}
double DFGF_T2::computeEmpMean(){

}