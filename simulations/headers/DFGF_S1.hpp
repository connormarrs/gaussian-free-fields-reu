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
        vector<vector<double>> eigenVectors; 
        // 2d vector to hold the values of the eigenfunctions at each point in the domain
        // multiplied by 1/eigenfunction^s
        vector<vector<double>> coefficients;
        // RandVec to generate samples of random vectors
        RandVec gaussianVector;
        // 2d vector to hold the many samples of the random vector; allows for multithreading
        vector<vector<double>> trialData;
        // vector where the nth entry represents the maximum of the DFGF computed for that nth trial.
        vector<double> maxima;
        double meanOfMaxima;

        void computeEigenVals();
        double computeEigenVal(int k);
        void computeEigenVectors();
        double computeEigenVector(int r, int k);
        double computeCoeff(int r, int k);
        void computeCoefficients();
        vector<double> computeFullEigenVector(int r);
        vector<double> computeFullCoefficients(int r);

        void computeMaxVectors();

    public:
        // constructors
        DFGF_S1(double s, int n, int numberTrials, RandVec gaussianVector);
		DFGF_S1()=default;
        ~DFGF_S1()=default;
        double evaluatePoint(int k, vector<double> sampleVector);
        vector<double> evaluate(vector<double> sampleVector);

        void runTrials();
        void parallelMean();
        double computeEmpMean();
};

#endif