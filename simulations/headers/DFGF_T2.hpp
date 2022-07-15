#ifndef DFGF_T2_H
#define DFGF_T2_H

#include "RandVec.hpp"
#include "DFGF.hpp"
#include "tools.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

/**
 * Class that implements DFGF for the FGF on a circle
 */
class DFGF_T2: public DFGF {
    private:
        vector<vector<double>> eigenVals;
        // 2d vector to hold the values of the eigenfunctions at each point in the domain
        vector<vector<vector<vector<double>>>> eigenVectors;  /* eigenVector[r-1][k] = f_r(theta_k) */
        // 2d vector to hold the values of the eigenfunctions at each point in the domain
        // multiplied by 1/eigenfunction^s
        vector<vector<vector<vector<double>>>> coefficients;
        // RandVec to generate samples of random vectors
        RandVec gaussianVector;
        // 2d vector to hold the many samples of the random vector; allows for multithreading
        vector<vector<vector<vector<double>>>> trialData;
        // vector where the nth entry represents the maximum of the DFGF computed for that nth trial.
        vector<double> maxima;
        double meanOfMaxima;

        void computeEigenVals();
        double computeEigenVal(int k);
        void computeEigenVectors();
        void computeCoeffs();
        void computeMaxVectors();

    public:
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
};

#endif