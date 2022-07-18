#include "../headers/DFGF_T2.hpp"
#include <iostream>


// constructors
DFGF_T2::DFGF_T2(double s, int n, int numberTrials, RandVec gaussianVector){

}

void DFGF_T2::computeCoeffs(){

    computeEigenVectors();
    computeEigenVals();

    for(int p = 0; p < n; p++){
        vector<vector<vector<double>>> subCoeffs;
        coefficients.push_back(subCoeffs);
        for(int q = 0; q < n; q++){
            coefficients[p].push_back(computeCoefficientVector(p,q));
        }
    }

}

/* returns 2d vector containing f_p,q(j,k) at each point (j,k) in grid */
vector<vector<double>> DFGF_T2::computeCoefficientVector(int p, int q){
    vector<vector<double>> coeffs_pq;

    for(int j = 0; j < n; j++){
        vector<double> subCoeffs;
        coeffs_pq.push_back(subCoeffs);
        for(int k = 0; k < n; k++){
            coeffs_pq[j].push_back(computeCoefficientPoint(p,q,j,k));
        }
    }

    return coeffs_pq;

}

/* returns f_p,q(theta_j, theta_k) / (lambda_p,q ^ s) */
double DFGF_T2::computeCoefficientPoint(int p, int q, int j, int k){

    if(p == 0 && q == 0){
        return 0;
    }
    else{
        return eigenVectors[p][q][j][k] / pow(eigenVals[p][q], s);
    }

}


/* return the 4d array of all values f_p,q(j,k )*/
vector<vector<vector<vector<double>>>>  DFGF_T2::getCoefficients(){
    return coefficients;
}

void DFGF_T2::computeEigenVectors(){

    for(int p = 0; p < n; p++){
        vector<vector<vector<double>>> subEigVect;
        eigenVectors.push_back(subEigVect);
        for(int q = 0; q < n; q++){
            eigenVectors[p].push_back(computeEigenFunctionVector(p,q));
        }
    }

}

/* returns 2d vector containing f_p,q(j,k) at each point (j,k) in grid */
vector<vector<double>> DFGF_T2::computeEigenFunctionVector(int p, int q){
    vector<vector<double>> eigenVect;

    for(int j = 0; j < n; j++){
        vector<double> subEigVect;
        eigenVect.push_back(subEigVect);
        for(int k = 0; k < n; k++){
            eigenVect[j].push_back(computeEigenFunctionPoint(p, q, j, k));
        }
    }

    return eigenVect;
}

/* returns f_p,q(theta_j, theta_k) */
double DFGF_T2::computeEigenFunctionPoint(int p, int q, int j, int k){
    double arg = (2 * M_PI * p * j/n) + (2 * M_PI * q * k/n);

    if(p <= ceil(1.0 * n / 2.0)){
        return cos(arg);
    }
    else{
        return sin(arg);
    }
}

/* return the 4d array of all values f_p,q(j,k )*/
vector<vector<vector<vector<double>>>>  DFGF_T2::getEigenVectors(){
    return eigenVectors;
}

double DFGF_T2::computeEigenVal(int p, int q){
    double normalizer = pow(1.0 * n, 2.0) / (2 * pow(M_PI, 2.0));
    double arg1 = (2 * M_PI * p) / (1.0 * n); 
    double arg2 = (2 * M_PI * q) / (1.0 * n);
    return normalizer * (2 - cos(arg1) - cos(arg2));

}

void DFGF_T2::computeEigenVals(){

    for(int p = 0; p < n; p++){
        vector<double> subEigVals;
        eigenVals.push_back(subEigVals);
        for(int q = 0; q < n; q++){
            eigenVals[p].push_back(computeEigenVal(p, q));
        }
    }

    cout<<"Hello World!"<<endl;
}

vector<vector<double>> DFGF_T2::getEigenVals(){
    return eigenVals;
}

/* returns value of DFGF at point (j,k) in grid */
double DFGF_T2::evaluatePoint(int j, int k, vector<double> sampleVector){
    return 0.0;
}
// returns 2d array containing values of DFGF at each point given the sample random vector
vector<vector<double>> DFGF_T2::evaluate(vector<double> sampleVector){
    vector<vector<double>> empty;
    return empty;
}

void DFGF_T2::runTrials(){

}

void DFGF_T2::computeMaxVectors(){

}

double DFGF_T2::computeEmpMean(){
    return 0.0;
}

int main(){

    DFGF_T2 obj;
    obj.computeEigenVals();

    return 0;
}