#ifndef DFGF_S1_H
#define DFGF_S1_H

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
class DFGF_S1: public DFGF {
    private:
        vector<double> eigenVals;
        // 2d vector to hold the values of the eigenfunctions at each point in the domain
        vector<vector<double>> eigenVectors;  /* eigenVector[r-1][k] = f_r(theta_k) */
        // 2d vector to hold the values of the eigenfunctions at each point in the domain
        // multiplied by 1/eigenfunction^s
        vector<vector<double>> coefficients;
        // RandVec to generate samples of random vectors
        vector<vector<double>> gaussianVector;
        // 2d vector to hold the many samples of the random vector; allows for multithreading
        vector<vector<double>> trialData;
        // vector where the nth entry represents the maximum of the DFGF computed for that nth trial.
        vector<double> maxima;
        double meanOfMaxima;

        bool isDirichlet;

        void computeEigenVals();
        double computeEigenVal(int k);
        void computeEigenVectors();
        void computeCoeffs();

    public:
        // constructors
        DFGF_S1(double s, int n, int numberTrials, RandVec gaussianVector, bool dirichlet);
		DFGF_S1()=default;
        ~DFGF_S1()=default;

        vector<double> getEigenVals();

        double computeEigenFunctionPoint(int r, int k);
        vector<double> computeEigenFunctionVector(int r);
        vector<vector<double>> getEigenVectors();

	    vector<vector<double>> getTrialData();
	    vector<double> getMaximaList();
	    double getEmpMean();

        double computeCoeffPoint(int r, int k);
        vector<double> computeCoefficientVector(int r);
        vector<vector<double>> getCoeffs(); 

        double evaluatePoint(int k, vector<double> sampleVector);
        vector<double> evaluate(vector<double> sampleVector);
        void computeMaxVectors();
        void runTrials();
        void computeEmpMean();

        vector<vector<double>> debugRunTrials();
};

#endif
