#include "gtest/gtest.h"
#include "../headers/DFGF_S1.hpp"
#include "../headers/RandVec.hpp"
#include "../headers/tools.hpp"

using namespace std;

/**
 * @brief Fixture to Set Up DFGF for testing
 * 
 * @details We fix s=1/4 and then mock up DFGF_S1 with n=10 and m=15
 * We then generated control eigenvalues, eigenfunctions, coefficients, etc.
 * for these functions using both Wolfram Mathematica and Python.
 * Finally, we verify that our code reproduces these results to at least
 * precision of 1e-6, which is what Python created.
 * 
 */
class DFGF_S1_Fixture: public ::testing::Test {
    protected:
        DFGF_S1_Fixture( ) { }
        ~DFGF_S1_Fixture( )  { }

        /* instantiate two DFGF objects */
        double s = .25;
        int n = 10;
        int m = 15;
        int numTrials = 30; 

        RandVec gauss_vector_m = RandVec(m, numTrials);
        DFGF_S1 sample_field_m = DFGF_S1(s,m,numTrials, gauss_vector_m); 
        RandVec gauss_vector_n = RandVec(n, numTrials);
        DFGF_S1 sample_field_n = DFGF_S1(s,n,numTrials, gauss_vector_n);

        vector<double> known_eigvals_n = {
            0.0,
            0.9675312092750789,
            3.500560800333523,
            6.631557563900254,
            9.1645871549587,
            10.132118364233778,
            9.1645871549587,
            6.631557563900254,
            3.5005608003335245,
            0.9675312092750794
        };
        vector<double> known_eigvals_m = {
            0,
            0.9854636133271846,
            3.7714588419085953,
            7.876261800750427,
            12.59011476730474,
            17.0979497396445,
            20.620321098657072,
            22.54817883663,
            22.54817883663,
            20.620321098657072,
            17.097949739644505,
            12.590114767304751,
            7.87626180075043,
            3.771458841908593,
            0.9854636133271834
        };

        vector<vector<double>> known_eigenvectors_n = {
            // cosine case
            { 0.70710678, 0.5720614, 0.21850801, -0.21850801, -0.5720614, -0.70710678, -0.5720614, -0.21850801, 0.21850801, 0.5720614 }, // r=1
            { 0.70710678, 0.21850801, -0.5720614, -0.5720614, 0.21850801, 0.70710678, 0.21850801, -0.5720614, -0.5720614, 0.21850801 }, // r=2
            { 0.70710678, -0.21850801, -0.5720614, 0.5720614, 0.21850801, -0.70710678, 0.21850801, 0.5720614, -0.5720614, -0.21850801 }, // r=3
            { 0.70710678, -0.5720614, 0.21850801, 0.21850801, -0.5720614, 0.70710678, -0.5720614, 0.21850801, 0.21850801, -0.5720614 }, // r=4
            // special case
            {0.70710678, -0.70710678, 0.70710678, -0.70710678, 0.70710678, -0.70710678, 0.70710678, -0.70710678, 0.70710678, -0.70710678}, // r=5
            // sine case
            { 0.00000000e+00, -4.15626938e-01,  6.72498512e-01, -6.72498512e-01,  4.15626938e-01, -5.19573634e-16, -4.15626938e-01,  6.72498512e-01, -6.72498512e-01, 4.15626938e-01},
            { 0.00000000e+00, -6.72498512e-01,  4.15626938e-01,
             4.15626938e-01, -6.72498512e-01,  6.06169239e-16,
             6.72498512e-01, -4.15626938e-01, -4.15626938e-01,
             6.72498512e-01},
            { 0.00000000e+00, -6.72498512e-01, -4.15626938e-01,
             4.15626938e-01,  6.72498512e-01, -6.92764845e-16,
            -6.72498512e-01, -4.15626938e-01,  4.15626938e-01,
             6.72498512e-01},
            { 0.00000000e+00, -4.15626938e-01, -6.72498512e-01,
            -6.72498512e-01, -4.15626938e-01,  7.79360451e-16,
             4.15626938e-01,  6.72498512e-01,  6.72498512e-01,
             4.15626938e-01}
        };
        vector<vector<double>> known_eigenvectors_m = {
            // cosine values
            { 0.70710678,  0.64597419,  0.47314679,  0.21850801, -0.07391279,
            -0.35355339, -0.5720614 , -0.6916548 , -0.6916548 , -0.5720614 ,
            -0.35355339, -0.07391279,  0.21850801,  0.47314679,  0.64597419},
            { 0.70710678,  0.47314679, -0.07391279, -0.5720614 , -0.6916548 ,
            -0.35355339,  0.21850801,  0.64597419,  0.64597419,  0.21850801,
            -0.35355339, -0.6916548 , -0.5720614 , -0.07391279,  0.47314679},
            { 0.70710678,  0.21850801, -0.5720614 , -0.5720614 ,  0.21850801,
             0.70710678,  0.21850801, -0.5720614 , -0.5720614 ,  0.21850801,
             0.70710678,  0.21850801, -0.5720614 , -0.5720614 ,  0.21850801},
            { 0.70710678, -0.07391279, -0.6916548 ,  0.21850801,  0.64597419,
            -0.35355339, -0.5720614 ,  0.47314679,  0.47314679, -0.5720614 ,
            -0.35355339,  0.64597419,  0.21850801, -0.6916548 , -0.07391279},
            { 0.70710678, -0.35355339, -0.35355339,  0.70710678, -0.35355339,
            -0.35355339,  0.70710678, -0.35355339, -0.35355339,  0.70710678,
            -0.35355339, -0.35355339,  0.70710678, -0.35355339, -0.35355339},
            { 0.70710678, -0.5720614 ,  0.21850801,  0.21850801, -0.5720614 ,
             0.70710678, -0.5720614 ,  0.21850801,  0.21850801, -0.5720614 ,
             0.70710678, -0.5720614 ,  0.21850801,  0.21850801, -0.5720614 },
            { 0.70710678, -0.6916548 ,  0.64597419, -0.5720614 ,  0.47314679,
            -0.35355339,  0.21850801, -0.07391279, -0.07391279,  0.21850801,
            -0.35355339,  0.47314679, -0.5720614 ,  0.64597419, -0.6916548 },
            // sine values
            { 0.00000000e+00, -1.47015766e-01,  2.87606238e-01,
            -4.15626938e-01,  5.25482745e-01, -6.12372436e-01,
             6.72498512e-01, -7.03233176e-01,  7.03233176e-01,
            -6.72498512e-01,  6.12372436e-01, -5.25482745e-01,
             4.15626938e-01, -2.87606238e-01,  1.47015766e-01},
            { 0.00000000e+00, -4.15626938e-01,  6.72498512e-01,
            -6.72498512e-01,  4.15626938e-01, -5.19573634e-16,
            -4.15626938e-01,  6.72498512e-01, -6.72498512e-01,
             4.15626938e-01, -1.03914727e-15, -4.15626938e-01,
             6.72498512e-01, -6.72498512e-01,  4.15626938e-01},
            { 0.00000000e+00, -6.12372436e-01,  6.12372436e-01,
            -1.60245639e-15, -6.12372436e-01,  6.12372436e-01,
            -3.20491278e-15, -6.12372436e-01,  6.12372436e-01,
            -1.03914727e-15, -6.12372436e-01,  6.12372436e-01,
            -6.40982556e-15, -6.12372436e-01,  6.12372436e-01},
            { 0.00000000e+00, -7.03233176e-01,  1.47015766e-01,
             6.72498512e-01, -2.87606238e-01, -6.12372436e-01,
             4.15626938e-01,  5.25482745e-01, -5.25482745e-01,
            -4.15626938e-01,  6.12372436e-01,  2.87606238e-01,
            -6.72498512e-01, -1.47015766e-01,  7.03233176e-01},
            { 0.00000000e+00, -6.72498512e-01, -4.15626938e-01,
             4.15626938e-01,  6.72498512e-01, -3.20491278e-15,
            -6.72498512e-01, -4.15626938e-01,  4.15626938e-01,
             6.72498512e-01, -6.40982556e-15, -6.72498512e-01,
            -4.15626938e-01,  4.15626938e-01,  6.72498512e-01},
            { 0.00000000e+00, -5.25482745e-01, -7.03233176e-01,
            -4.15626938e-01,  1.47015766e-01,  6.12372436e-01,
             6.72498512e-01,  2.87606238e-01, -2.87606238e-01,
            -6.72498512e-01, -6.12372436e-01, -1.47015766e-01,
             4.15626938e-01,  7.03233176e-01,  5.25482745e-01},
            { 0.00000000e+00, -2.87606238e-01, -5.25482745e-01,
            -6.72498512e-01, -7.03233176e-01, -6.12372436e-01,
            -4.15626938e-01, -1.47015766e-01,  1.47015766e-01,
             4.15626938e-01,  6.12372436e-01,  7.03233176e-01,
             6.72498512e-01,  5.25482745e-01,  2.87606238e-01}
        };
};

/**
 * @brief Test if the computeEigenVector method properly computes values
 * with error at most 1e-8
 * 
 */
TEST_F (DFGF_S1_Fixture, checkEigenValues){
    vector<double> tested_eigvals_n = sample_field_n.getEigenVals();
    vector<double> tested_eigvals_m = sample_field_m.getEigenVals();

    for(int j=0; j<n; j++) {
        ASSERT_DOUBLE_EQ(known_eigvals_n[j],tested_eigvals_n[j]);
    }

    for(int j=0; j<m; j++) {
        ASSERT_NEAR(known_eigvals_m[j],tested_eigvals_m[j], 1e-08);
    }
}

/**
 * @brief Using fixture above, we test if the DFGF computeEigenVector
 * reproduces the control output within 1e-6. Namely, this isolates
 * the formula for the value of an eigenfunction at a point and tests that
 * it is implemented correctly.
 * 
 */
TEST_F(DFGF_S1_Fixture, testEigenFunctionPoint) {
    for(int r=1; r<n; r++){
        for(int k=0; k<n; k++){
            /* We subtract one from the index of known_eigenvectors since these only store eigenvectors
            starting at index r=1; in other words known_eigenvectors_n[r-1] if f_r */
            SCOPED_TRACE("N=10: Iteration ["+to_string(r)+"]["+to_string(k)+"]");
            ASSERT_NEAR(sample_field_n.computeEigenFunctionPoint(r,k), known_eigenvectors_n[r-1][k], 1e-6);
        }
    }

    for(int r=1; r<m; r++){
        for(int k=0; k<m; k++){
            /* We subtract one from the index of known_eigenvectors since these only store eigenvectors
            starting at index r=1; in other words known_eigenvectors_n[r-1] if f_r */
            SCOPED_TRACE("M=15: Iteration ["+to_string(r)+"]["+to_string(k)+"]");
            ASSERT_NEAR(sample_field_m.computeEigenFunctionPoint(r,k), known_eigenvectors_m[r-1][k], 1e-6);
        }
    }
}

/**
 * @brief Using fixture above, we test if the DFGF computeFullEigenVector
 * reproduces the control output within 1e-6. This differs from the above
 * in that we ensure that the function successfully formats the data from
 * computeEigenFunction
 * 
 */
TEST_F(DFGF_S1_Fixture, testEigenFunctionVector) {
    for(int r=1; r<n; r++){
        vector<double> testVector = sample_field_n.computeEigenFunctionVector(r);
        bool result = Tools::vectComparison(testVector, known_eigenvectors_n[r-1]);
        if(result){
            SUCCEED();
        } else {
            cout << "known_eigenvectors_n: ";
            for(int i=0; i < n; i++) {
                cout << known_eigenvectors_n[r-1][i] << ' ';
            }
            cout << endl;

            cout << "testVector: ";
            for(long unsigned int j=0; j < testVector.size(); j++){
                cout << testVector[j] << ' ';
            }
            cout << endl;

            SCOPED_TRACE("N=10: Iteration r="+to_string(r));
            
            FAIL();
        }
    }

    for(int r=1; r<m; r++){
        vector<double> testVector = sample_field_m.computeEigenFunctionVector(r);
        bool result = Tools::vectComparison(testVector, known_eigenvectors_m[r-1]);
        if(result){
            SUCCEED();
        } else {
            cout << "known_eigenvectors_m: ";
            for(int i=0; i < n; i++) {
                cout << known_eigenvectors_m[r-1][i] << ' ';
            }
            cout << endl;

            cout << "testVector: ";
            for(long unsigned int j=0; j < testVector.size(); j++){
                cout << testVector[j] << ' ';
            }
            cout << endl;

            SCOPED_TRACE("N=10: Iteration r="+to_string(r));
            
            FAIL();
        }
    }
}

/**
 * @brief Using fixture above, we test if the DFGF computeEigenVectors
 * reproduces the control output within 1e-6. This differs from the above
 * in that we ensure that the function successfully formats the data from
 * computeFullEigenVector.
 * 
 */
TEST_F(DFGF_S1_Fixture, checkEigenFunctions) {
    vector<vector<double>> tested_eigvectors_n = sample_field_n.getEigenVectors();
    vector<vector<double>> tested_eigvectors_m = sample_field_m.getEigenVectors();

    for(int r=1; r<n; r++) {
        for (int k=0; k<n; k++) {
            SCOPED_TRACE("N=10: Iteration ["+to_string(r)+"]["+to_string(k)+"]");
            ASSERT_NEAR(known_eigenvectors_n[r-1][k], tested_eigvectors_n[r-1][k], 1e-08);
        }
    } 

    for(int r=1; r<m; r++) {
        for (int k=0; k<m; k++) {
            SCOPED_TRACE("M=15: Iteration ["+to_string(r)+"]["+to_string(k)+"]");
            ASSERT_NEAR(known_eigenvectors_m[r-1][k], tested_eigvectors_m[r-1][k], 1e-08);
        }
    } 
}