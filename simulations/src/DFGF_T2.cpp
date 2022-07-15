#include "../headers/DFGF_T2.hpp"
        void computeEigenVals();
        double computeEigenVal(int k);
        void computeEigenVectors();
        void computeCoeffs();
        void computeMaxVectors();

        // constructors
        DFGF_T2(double s, int n, int numberTrials, RandVec gaussianVector);
		DFGF_T2()=default;
        ~DFGF_T2()=default;

        vector<vector<double>> getEigenVals();
        /* returns f_p,q(theta_j, theta_k) */
        double computeEigenFunctionPoint(int p, int q, int j, int k);
        /* returns 2d vector containing f_p,q(j,k) at each point (j,k) in grid */
        vector<vector<double>> computeEigenFunctionVector(int p, int q);
        /* return the 4d array of all values f_p,q(j,k )*/
        vector<vector<vector<vector<double>>>>  getEigenVectors();

        /* returns f_p,q(theta_j, theta_k) */
        double computeCoefficientPoint(int p, int q, int j, int k);
        /* returns 2d vector containing f_p,q(j,k) at each point (j,k) in grid */
        vector<vector<double>> computeCoefficientVector(int p, int q);
        /* return the 4d array of all values f_p,q(j,k )*/
        vector<vector<vector<vector<double>>>>  getCoefficients();

        /* returns value of DFGF at point (j,k) in grid */
        double evaluatePoint(int j, int k, vector<double> sampleVector);
        /* returns 2d array containing values of DFGF at each point given the sample random vector*/
        vector<vector<double>> evaluate(vector<double> sampleVector);

        void runTrials();
        double computeEmpMean();