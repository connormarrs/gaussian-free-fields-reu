#include "../headers/DFGF_T2.hpp"

/**
 * @brief Construct a new dfgf t2::dfgf t2 object
 * 
 * @param sVals 
 * @param nVals 
 * @param numberTrials 
 * @param gaussianVector 
 */
DFGF_T2::DFGF_T2(double sVals, int nVals, int numberTrials, RandArr gaussianArray){
	// set the parameters
	n = nVals;
	s = sVals;
	this->gaussianArray = gaussianArray;
	numTrials = numberTrials;

	// construct the eigenVals
	this->computeEigenVals();
	this->computeEigenVectors();
	this->computeCoeffs();
}

/********************************
 *      Eigenvalue Methods
 ********************************/

/**
 * @brief 
 * 
 * @param p 
 * @param q 
 * @return double 
 */
double DFGF_T2::computeEigenVal(int p, int q){
    double normalizer = pow(1.0 * n, 2.0) / (2 * pow(M_PI, 2.0));
    double arg1 = (2 * M_PI * p) / (1.0 * n); 
    double arg2 = (2 * M_PI * q) / (1.0 * n);
    return normalizer * (2 - cos(arg1) - cos(arg2));
}

/**
 * @brief 
 * 
 */
void DFGF_T2::computeEigenVals(){
    for(int p = 0; p < n; p++){
        vector<double> subEigVals;
        eigenVals.push_back(subEigVals);
        for(int q = 0; q < n; q++){
            eigenVals[p].push_back(computeEigenVal(p, q));
        }
    }
}

/**
 * @brief 
 * 
 * @return vector<vector<double>> 
 */
vector<vector<double>> DFGF_T2::getEigenVals(){
    return eigenVals;
}

/********************************
 *      Eigenvector Methods
 ********************************/

/**
 * @brief 
 * 
 */
void DFGF_T2::computeEigenVectors(){
    for(int p = 0; p < n; p++){
        vector<vector<vector<double>>> subEigVect;
        eigenVectors.push_back(subEigVect);
        for(int q = 0; q < n; q++){
            eigenVectors[p].push_back(computeEigenFunctionVector(p,q));
        }
    }
}

/**
 * @brief returns 2d vector containing f_p,q(j,k) at each point (j,k) in grid
 * 
 * @param p 
 * @param q 
 * @return vector<vector<double>> 
 */
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
    double arg = (2 * M_PI * p * j/n) + (2 * M_PI * q * k/n);

    if(p <= ceil(1.0 * n / 2.0)){
        return cos(arg);
    }
    else{
        return sin(arg);
    }
}

/**
 * @brief returns 2d vector containing f_p,q(j,k) at each point (j,k) in grid
 * 
 * @return vector<vector<vector<vector<double>>>> 
 */
vector<vector<vector<vector<double>>>>  DFGF_T2::getEigenVectors(){
    return eigenVectors;
}

/********************************
 *      Coefficient Methods
 ********************************/

/**
 * @brief 
 * 
 */
void DFGF_T2::computeCoeffs(){
    for(int p = 0; p < n; p++){
        vector<vector<vector<double>>> subCoeffs;
        coefficients.push_back(subCoeffs);
        for(int q = 0; q < n; q++){
            coefficients[p].push_back(computeCoefficientVector(p,q));
        }
    }

}

/**
 * @brief returns 2d vector containing f_p,q(j,k) at each point (j,k) in grid
 * 
 * @param p 
 * @param q 
 * @return vector<vector<double>> 
 */
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

/**
 * @brief returns f_p,q(theta_j, theta_k) / (lambda_p,q ^ s)
 * 
 * @param p 
 * @param q 
 * @param j 
 * @param k 
 * @return double 
 */
double DFGF_T2::computeCoefficientPoint(int p, int q, int j, int k){
    if(p == 0 && q == 0){
        return 0;
    }
    else{
        return eigenVectors[p][q][j][k] / pow(eigenVals[p][q], s);
    }
}

/**
 * @brief return the 4d array of all values f_p,q(j,k)
 * 
 * @return vector<vector<vector<vector<double>>>> 
 */
vector<vector<vector<vector<double>>>>  DFGF_T2::getCoefficients(){
    return coefficients;
}

/****************************************
 *          Evaluation Methods
 ****************************************/

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
 * @brief 
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

/****************************************
 *       Maxima/Simulation Methods
 ****************************************/

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
 * @brief 
 * 
 * @return double 
 */
double DFGF_T2::computeEmpMean(){
    return 0.0;
}