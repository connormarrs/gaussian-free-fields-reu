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
 * @brief computes an individual eigenvalue of discrete laplacian
 * 
 * @param p first index of eigenvalue
 * @param q first eigenvalue
 * @return double 
 */
double DFGF_T2::computeEigenVal(int p, int q){
    /* n^2/2pi^2 normalizes discrete laplacian so it acts like second derivative*/
    double normalizer = pow(1.0 * n, 2.0) / (2 * pow(M_PI, 2.0));
    
    double arg1 = (2 * M_PI * p) / (1.0 * n); 
    double arg2 = (2 * M_PI * q) / (1.0 * n);
    return normalizer * (2 - cos(arg1) - cos(arg2));
}

/**
 * @brief makes vector of all eigenvalues of discrete laplacian
 * 
 */
void DFGF_T2::computeEigenVals(){
    for(int p = 0; p < n; p++){
        /* vector to store all eigenvalues of the form lambda_p,- */
        vector<double> eigVals_p;
        eigenVals.push_back(eigVals_p);
        for(int q = 0; q < n; q++){
            eigenVals[p].push_back(computeEigenVal(p, q));
        }
    }
}

/**
 * @brief returns 2d vector of all eigenvalues lambda_p,q of discrete laplacian
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
 * @brief computes eigenvectors of discrete laplacian on torus
 * 
 */
void DFGF_T2::computeEigenVectors(){
    for(int p = 0; p < n; p++){
        /* stores all eigenvectors with index p, i.e. of the form f_p,-(-,-)*/
        vector<vector<vector<double>>> eigVects_p;
        eigenVectors.push_back(eigVects_p);
        for(int q = 0; q < n; q++){
            eigenVectors[p].push_back(computeEigenFunctionVector(p,q));
        }
    }
}

/**
 * @brief returns 2d vector containing f_p,q(theta_j,theta_k) at each point (theta_j,theta_k) in grid
 *
 * @param p first index for eigenvector
 * @param q second index for eigenvector
 * @return vector<vector<double>> 
 */
vector<vector<double>> DFGF_T2::computeEigenFunctionVector(int p, int q){
    /* instantiates a single eigenvector f_p,q*/
    vector<vector<double>> eigenVect;

    for(int j = 0; j < n; j++){
        /* stores all entries of eigenvector of the form f_p,q(theta_j, -)*/
        vector<double> eigVect_j;
        eigenVect.push_back(eigVect_j);
        for(int k = 0; k < n; k++){
            eigenVect[j].push_back(computeEigenFunctionPoint(p, q, j, k));
        }
    }

    return eigenVect;
}

/**
 * @brief returns f_p,q(theta_j, theta_k)
 * 
 * @param p first index for eigenvector
 * @param q second index for eigenvector
 * @param j index of first angle
 * @param k index of second angle
 * @return double 
 */
double DFGF_T2::computeEigenFunctionPoint(int p, int q, int j, int k){
    double arg = (2 * M_PI * p * j/n) + (2 * M_PI * q * k/n);

    /* We use cosine to define the p,q-th eigenvector if p <= n/2, and sine otherwise */
    if(p <= floor(1.0 * n / 2.0)){
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
 * @brief computes coefficients c_p,q for each term c_p,q * Z_p,q in DFGF
 * 
 */
void DFGF_T2::computeCoeffs(){

    for(int p = 0; p < n; p++){
        /* vector to store all coefficients with index p, i.e. of the form c_p,-(-,-) */
        vector<vector<vector<double>>> coeffs_p;
        coefficients.push_back(coeffs_p);
        for(int q = 0; q < n; q++){
            coefficients[p].push_back(computeCoefficientVector(p,q));
        }
    }

}

/**
 * @brief returns 2d vector containing c_p,q(theta_j,theta_k) at each point (theta_j,theta_k) in grid
 * 
 * @param p first index for coefficient
 * @param q second index for coefficient
 * @return vector<vector<double>> 
 */
vector<vector<double>> DFGF_T2::computeCoefficientVector(int p, int q){
    /* vector to store all coefficients of the form c_p,q(-,-) */
    vector<vector<double>> coeffs_pq;

    for(int j = 0; j < n; j++){
        /* vector of coefficients of the form c_p,q(theta_j, -)*/
        vector<double> coeffs_pqj;
        coeffs_pq.push_back(coeffs_pqj);
        for(int k = 0; k < n; k++){
            coeffs_pq[j].push_back(computeCoefficientPoint(p,q,j,k));
        }
    }

    return coeffs_pq;
}

/**
 * @brief returns c_p,q(theta_j, theta_k) = f_p,q(theta_j, theta_k) / (lambda_p,q ^ s)
 * 
 * @param p first index for coefficient
 * @param q second index for coefficient
 * @param j index of first angle
 * @param k index of second angle
 * @return double 
 */
double DFGF_T2::computeCoefficientPoint(int p, int q, int j, int k){

    /* we do not sum over the first eigenvector which has eigenvalue 0, so we make this coefficient 0 */
    if(p == 0 and q == 0){
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
 * @brief returns value of DFGF at point (theta_j,theta_k) in grid
 * 
 * @param j index of first angle
 * @param k index of second angle
 * @param sampleVector vector of normal random variables Z_p,q
 * @return double 
 */
double DFGF_T2::evaluatePoint(int j, int k, vector<vector<double>> sampleVector){
    double sum = 0;
    //make sure this works with the dummy zero coefficients
    /* sum over all terms of DFGF, which look like c_p,q(theta_i, theta_j) * Z_p,q */
    for(int p=0; p<n; p++){
        for(int q=0; q<n; q++){
            sum += coefficients[p][q][j][k]*sampleVector[p][q];
        }
    }
    return sum;
    
}

/**
 * @brief computes vector of values of DFGF at each point (theta_j, theta_k) in grid 
 * 
 * @param sampleVector vector of normal random variables Z_p,q
 * @return vector<vector<double>> 
 */
vector<vector<double>> DFGF_T2::evaluate(vector<vector<double>> sampleVector){
    /* vector to store values of DFGF instance */
    vector<vector<double>> dfgf;

    for(int j=0; j<n; j++){
        vector<double> dfgfRow;
        for(int k=0; k<n; k++){
            /* compute and store DFGF value at (theta_j, theta_k) */
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
 * @brief computes multiple instances of the DFGF and stores each in 'trialdata'
 * 
 */
void DFGF_T2::runTrials(){
    /* instantiate a vector of tasks */
	vector<future<vector<vector<double>>>> tasks; 
    vector<vector<vector<double>>> rand_vals = gaussianArray.getSample(this->n);

    /* start a new thread to compute the DFGF for each random array */
	for(int i = 0; i < numTrials; i++){
		tasks.push_back(
            async(&DFGF_T2::evaluate, this, rand_vals[i])
        );
	}

    /* loop through tasks array and upon completion of each task, append data to trialData array */
	for(long unsigned int i = 0; i < tasks.size(); i++){
		trialData.push_back(
            tasks[i].get()
        );
	}
}
void DFGF_T2::debugRunTrials(vector<vector<vector<double>>> testRandomArrs){
    /* instantiate a vector of tasks */
	vector<future<vector<vector<double>>>> tasks; 
    /* start a new thread to compute the DFGF for each random array */
	for(int i = 0; i < numTrials; i++){
		tasks.push_back(
            async(&DFGF_T2::evaluate, this, testRandomArrs[i])
        );
	}

    /* loop through tasks array and upon completion of each task, append data to trialData array */
	for(long unsigned int i = 0; i < tasks.size(); i++){
		trialData.push_back(
            tasks[i].get()
        );
	}
}


/**
 * @brief creates vector of maxima for each instance of DFGF generated
 * 
 */
void DFGF_T2::computeMaxVectors(){

    /* compute mmaximum for each instance generated */
    for(unsigned long int i = 0; i < trialData.size(); i++){
        int max = trialData[i][0][0];

        /* keep track of largest value found among grid points */
        for(unsigned long int j = 0; j < trialData[i].size(); j++){
            for(unsigned long int k = 0; k < trialData[i][j].size(); k++){
                if(trialData[i][j][k] > max){
                    max=trialData[i][j][k];
                }
            }
        }
        maxima.push_back(max);
    }
}

/**
 * @brief Computes the average of the maxima among all trials
 * 
 * @return double 
 */
double DFGF_T2::computeEmpMean(){
    double sum = 0;
    for (long unsigned int j=0; j<maxima.size(); j++){
        sum += maxima[j];
    }
    meanOfMaxima = sum/maxima.size();
    return meanOfMaxima;
}