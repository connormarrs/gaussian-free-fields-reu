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
        RandVec rand_vec_m_trials = RandVec(m, 100);
        vector<vector<double>>test_n_vec_trials = rand_vec_m_trials.getSample(n);
        vector<vector<double>>test_m_vec_trials = rand_vec_m_trials.getSample(m);
         
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
            0.0,
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
            { 0.70710678, -0.70710678, 0.70710678, -0.70710678, 0.70710678, -0.70710678, 0.70710678, -0.70710678, 0.70710678, -0.70710678}, // r=5
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

        vector<vector<double>> known_coefficients_n = {
            /* cosine vectors*/
            { 0.7129659 ,  0.57680153,  0.22031858, -0.22031858, -0.57680153,
        -0.7129659 , -0.57680153, -0.22031858,  0.22031858,  0.57680153},
       { 0.51695245,  0.15974709, -0.41822332, -0.41822332,  0.15974709,
         0.51695245,  0.15974709, -0.41822332, -0.41822332,  0.15974709},
       { 0.44063716, -0.13616437, -0.35648295,  0.35648295,  0.13616437,
        -0.44063716,  0.13616437,  0.35648295, -0.35648295, -0.13616437},
       { 0.40640288, -0.32878684,  0.1255854 ,  0.1255854 , -0.32878684,
         0.40640288, -0.32878684,  0.1255854 ,  0.1255854 , -0.32878684},
            /* alternating vector */
            { 0.39633273, -0.39633273,  0.39633273, -0.39633273,  0.39633273,
       -0.39633273,  0.39633273, -0.39633273,  0.39633273, -0.39633273 },
            /* sine vector */
            { 0.00000000e+00, -2.38877619e-01,  3.86512106e-01,
        -3.86512106e-01,  2.38877619e-01, -2.98619991e-16,
        -2.38877619e-01,  3.86512106e-01, -3.86512106e-01,
         2.38877619e-01},
       { 0.00000000e+00, -4.19070839e-01,  2.59000022e-01,
         2.59000022e-01, -4.19070839e-01,  3.77737418e-16,
         4.19070839e-01, -2.59000022e-01, -2.59000022e-01,
         4.19070839e-01},
       { 0.00000000e+00, -4.91650994e-01, -3.03857025e-01,
         3.03857025e-01,  4.91650994e-01, -5.06467328e-16,
        -4.91650994e-01, -3.03857025e-01,  3.03857025e-01,
         4.91650994e-01},
       { 0.00000000e+00, -4.19070839e-01, -6.78070862e-01,
        -6.78070862e-01, -4.19070839e-01,  7.85818262e-16,
         4.19070839e-01,  6.78070862e-01,  6.78070862e-01,
         4.19070839e-01}
        };
        vector<vector<double>> known_coefficients_m = {
            /* cosine coefficients */
            { 0.70970008,  0.64834328,  0.47488204,  0.21930939, -0.07418386,
        -0.35485004, -0.57415943, -0.69419143, -0.69419143, -0.57415943,
        -0.35485004, -0.07418386,  0.21930939,  0.47488204,  0.64834328},
       { 0.50740841,  0.3395225 , -0.05303862, -0.41050202, -0.49632032,
        -0.2537042 ,  0.15679782,  0.46354065,  0.46354065,  0.15679782,
        -0.2537042 , -0.49632032, -0.41050202, -0.05303862,  0.3395225 },
       { 0.42208991,  0.13043295, -0.34147791, -0.34147791,  0.13043295,
         0.42208991,  0.13043295, -0.34147791, -0.34147791,  0.13043295,
         0.42208991,  0.13043295, -0.34147791, -0.34147791,  0.13043295},
       { 0.37538558, -0.03923848, -0.3671825 ,  0.11600052,  0.34293179,
        -0.18769279, -0.30369331,  0.25118198,  0.25118198, -0.30369331,
        -0.18769279,  0.34293179,  0.11600052, -0.3671825 , -0.03923848},
       { 0.34773547, -0.17386774, -0.17386774,  0.34773547, -0.17386774,
        -0.17386774,  0.34773547, -0.17386774, -0.17386774,  0.34773547,
        -0.17386774, -0.17386774,  0.34773547, -0.17386774, -0.17386774},
       { 0.33182656, -0.26845333,  0.10254005,  0.10254005, -0.26845333,
         0.33182656, -0.26845333,  0.10254005,  0.10254005, -0.26845333,
         0.33182656, -0.26845333,  0.10254005,  0.10254005, -0.26845333},
       { 0.32449435, -0.31740337,  0.29644034, -0.26252144,  0.2171291 ,
        -0.16224717,  0.10027427, -0.0339189 , -0.0339189 ,  0.10027427,
        -0.16224717,  0.2171291 , -0.26252144,  0.29644034, -0.31740337},
            /* sine coefficients */
            { 0.00000000e+00, -6.74661682e-02,  1.31983741e-01,
        -1.90732991e-01,  2.41146294e-01, -2.81020347e-01,
         3.08612463e-01, -3.22716732e-01,  3.22716732e-01,
        -3.08612463e-01,  2.81020347e-01, -2.41146294e-01,
         1.90732991e-01, -1.31983741e-01,  6.74661682e-02},
       { 0.00000000e+00, -1.95042759e-01,  3.15585813e-01,
        -3.15585813e-01,  1.95042759e-01, -2.43822202e-16,
        -1.95042759e-01,  3.15585813e-01, -3.15585813e-01,
         1.95042759e-01, -4.87644403e-16, -1.95042759e-01,
         3.15585813e-01, -3.15585813e-01,  1.95042759e-01},
       { 0.00000000e+00, -3.01147751e-01,  3.01147751e-01,
        -7.88043534e-16, -3.01147751e-01,  3.01147751e-01,
        -1.57608707e-15, -3.01147751e-01,  3.01147751e-01,
        -5.11023757e-16, -3.01147751e-01,  3.01147751e-01,
        -3.15217414e-15, -3.01147751e-01,  3.01147751e-01},
       { 0.00000000e+00, -3.73329174e-01,  7.80470496e-02,
         3.57012897e-01, -1.52683069e-01, -3.25093444e-01,
         2.20646105e-01,  2.78965848e-01, -2.78965848e-01,
        -2.20646105e-01,  3.25093444e-01,  1.52683069e-01,
        -3.57012897e-01, -7.80470496e-02,  3.73329174e-01},
       { 0.00000000e+00, -4.01431355e-01, -2.48098222e-01,
         2.48098222e-01,  4.01431355e-01, -1.91309342e-15,
        -4.01431355e-01, -2.48098222e-01,  2.48098222e-01,
         4.01431355e-01, -3.82618685e-15, -4.01431355e-01,
        -2.48098222e-01,  2.48098222e-01,  4.01431355e-01},
       { 0.00000000e+00, -3.77077932e-01, -5.04628771e-01,
        -2.98247179e-01,  1.05496140e-01,  4.39428571e-01,
         4.82574072e-01,  2.06381592e-01, -2.06381592e-01,
        -4.82574072e-01, -4.39428571e-01, -1.05496140e-01,
         2.98247179e-01,  5.04628771e-01,  3.77077932e-01},
       { 0.00000000e+00, -2.88661028e-01, -5.27409942e-01,
        -6.74964885e-01, -7.05812268e-01, -6.14618298e-01,
        -4.17151240e-01, -1.47554943e-01,  1.47554943e-01,
         4.17151240e-01,  6.14618298e-01,  7.05812268e-01,
         6.74964885e-01,  5.27409942e-01,  2.88661028e-01}
        };

        /* fake random vector data to pass into evaluate in otder to compute */
        vector<double> mock_random_vector_n = {
            8.7, 99.523, 0.678, 1.0, 6.9, 8.889, 4.567, 3.149, 26.5833, 17.0
        };
        vector<double> mock_random_vector_m = {
            8.7, 99.523, 0.678, 1.0, 6.9, 8.889, 4.567, 3.149, 26.5833, 17.0, 1.242, 5.2724, 2.174, 8.83, 3.457
        };

        vector<double> known_dfgf_values_n = {78.0748173088461, 28.98101338954303, 8.652333151467037, -28.909592652006197, -50.18937134277107, -71.76547006146117, -61.62297456349108, -20.111008817502803, 42.70020362015893, 74.19004996721715};
        vector<double> known_dfgf_values_m = {79.6160594815281, 48.19213489121333, 47.04751831594366, 11.75910725331913, 0.6007689707582622, -43.95674356531519, -48.82218175552337, -69.91031226967027, -67.221839524213, -64.81792326264747, -29.8466904850396, -15.222049313659415, 37.720041280672554, 41.366419857473645, 73.49569012515968};
};

/**
 * @brief Test if the computeEigenVector method properly computes values
 * with error at most 1e-8
 * 
 */
TEST_F (DFGF_S1_Fixture, checkEigenValues){
    vector<double> test_eigvals_n = sample_field_n.getEigenVals();
    vector<double> test_eigvals_m = sample_field_m.getEigenVals();

    for(int j=0; j<n; j++) {
        ASSERT_DOUBLE_EQ(known_eigvals_n[j],test_eigvals_n[j]);
    }

    for(int j=0; j<m; j++) {
        ASSERT_NEAR(known_eigvals_m[j],test_eigvals_m[j], 1e-08);
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
TEST_F(DFGF_S1_Fixture, testEigenFunctions) {
    vector<vector<double>> test_eigvectors_n = sample_field_n.getEigenVectors();
    vector<vector<double>> test_eigvectors_m = sample_field_m.getEigenVectors();

    for(int r=1; r<n; r++) {
        for (int k=0; k<n; k++) {
            SCOPED_TRACE("N=10: Iteration ["+to_string(r)+"]["+to_string(k)+"]");
            ASSERT_NEAR(known_eigenvectors_n[r-1][k], test_eigvectors_n[r-1][k], 1e-08);
        }
    } 

    for(int r=1; r<m; r++) {
        for (int k=0; k<m; k++) {
            SCOPED_TRACE("M=15: Iteration ["+to_string(r)+"]["+to_string(k)+"]");
            ASSERT_NEAR(known_eigenvectors_m[r-1][k], test_eigvectors_m[r-1][k], 1e-08);
        }
    } 
}

/**
 * @brief Using fixture above, we test if the DFGF computeCoeffs method successfully
 * computes the coefficients the way we want it to.
 * 
 */
TEST_F(DFGF_S1_Fixture, testCoefficientsPoint){
    for(int r=1; r<n; r++) {
        for (int k=0; k<n; k++) {
            SCOPED_TRACE("N=10: Iteration ["+to_string(r)+"]["+to_string(k)+"]");
            ASSERT_NEAR(known_coefficients_n[r-1][k], sample_field_n.computeCoeffPoint(r,k), 1e-08);
        }
    }

    for(int r=1; r<m; r++) {
        for (int k=0; k<m; k++) {
            SCOPED_TRACE("M=15: Iteration ["+to_string(r)+"]["+to_string(k)+"]");
            ASSERT_NEAR(known_coefficients_m[r-1][k], sample_field_m.computeCoeffPoint(r,k), 1e-08);
        }
    }
}

/**
 * @brief Using fixture above, we test if the DFGF computeCoeffs method successfully
 * computes the coefficients the way we want it to.
 * 
 */
TEST_F(DFGF_S1_Fixture, testCoefficientsVector){
    for(int r=1; r<n; r++){
        vector<double> testVector = sample_field_n.computeCoefficientVector(r);
        bool result = Tools::vectComparison(testVector, known_coefficients_n[r-1]);
        if(result){
            SUCCEED();
        } else {
            cout << "known_eigenvectors_n: ";
            for(int i=0; i < n; i++) {
                cout << known_coefficients_n[r-1][i] << ' ';
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
        vector<double> testVector = sample_field_m.computeCoefficientVector(r);
        bool result = Tools::vectComparison(testVector, known_coefficients_m[r-1]);
        if(result){
            SUCCEED();
        } else {
            cout << "known_eigenvectors_m: ";
            for(int i=0; i < n; i++) {
                cout << known_coefficients_m[r-1][i] << ' ';
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
 * @brief Using fixture above, we test if the DFGF computeCoeffs method successfully
 * computes the coefficients the way we want it to.
 * 
 */
TEST_F(DFGF_S1_Fixture, testCoefficients){
    vector<vector<double>> test_coefficients_n = sample_field_n.getCoeffs();
    vector<vector<double>> test_coefficients_m = sample_field_m.getCoeffs();
    
    for(int r=1; r<n; r++) {
        for (int k=0; k<n; k++) {
            SCOPED_TRACE("N=10: Iteration ["+to_string(r)+"]["+to_string(k)+"]");
            ASSERT_NEAR(known_coefficients_n[r-1][k], test_coefficients_n[r-1][k], 1e-08);
        }
    } 

    for(int r=1; r<m; r++) {
        for (int k=0; k<m; k++) {
            SCOPED_TRACE("M=15: Iteration ["+to_string(r)+"]["+to_string(k)+"]");
            ASSERT_NEAR(known_coefficients_m[r-1][k], test_coefficients_m[r-1][k], 1e-08);
        }
    } 
}

/**
 * @brief Construct a new test f object
 * 
 */
TEST_F(DFGF_S1_Fixture, testEvaluatePoint){
    for (int k=0; k<n; k++) {
        SCOPED_TRACE("N=10: Iteration ["+to_string(k)+"]");
        ASSERT_NEAR(known_dfgf_values_n[k], sample_field_n.evaluatePoint(k, mock_random_vector_n), 1e-08);
    }
    for (int k=0; k<m; k++) {
        SCOPED_TRACE("M=15: Iteration ["+to_string(k)+"]");
        ASSERT_NEAR(known_dfgf_values_m[k], sample_field_m.evaluatePoint(k, mock_random_vector_m), 1e-08);
    }
}

/**
 * @brief Construct a new test f object
 * 
 */
TEST_F(DFGF_S1_Fixture, testEvaluateVector){
    vector<double> testDFGFVector_n = sample_field_n.evaluate(mock_random_vector_n);
    bool result_n_comp = Tools::vectComparison(testDFGFVector_n, known_dfgf_values_n);
    if(result_n_comp) {
        SUCCEED();
    } else {
        cout << "known_dfgf_values_n: ";
        for(int i=0; i < n; i++) {
            cout << known_dfgf_values_n[i] << ' ';
        }
        cout << endl;

        cout << "testDFGFVector: ";
        for(long unsigned int j=0; j < testDFGFVector_n.size(); j++){
            cout << testDFGFVector_n[j] << ' ';
        }
        cout << endl;
        
        FAIL();
    }

    vector<double> testDFGFVector_m = sample_field_m.evaluate(mock_random_vector_m);
    bool result_m_comp = Tools::vectComparison(testDFGFVector_m, known_dfgf_values_m);
    if(result_m_comp) {
        SUCCEED();
    } else {
        cout << "known_dfgf_values_m: ";
        for(int i=0; i < m; i++) {
            cout << known_dfgf_values_m[i] << ' ';
        }
        cout << endl;

        cout << "testDFGFVector: ";
        for(long unsigned int j=0; j < testDFGFVector_m.size(); j++){
            cout << testDFGFVector_m[j] << ' ';
        }
        cout << endl;
        
        FAIL();
    }
}

TEST_F(DFGF_S1_Fixture, checkRunTrials){
    vector<vector<vector<double>>> vectorOfTrialData_n;
    vector<vector<vector<double>>> vectorOfTrialData_m;
    //increase numberOfTests for computer with more cores
    int numberOfTests=2000;
    for(int i = 0; i<numberOfTests; i++){
        vectorOfTrialData_n.push_back(sample_field_n.debugRunTrials(test_n_vec_trials));
    }
    for(unsigned int i=0; i<vectorOfTrialData_n.size();i++){
        for(unsigned int j = 0; j<vectorOfTrialData_n[i].size(); j++){
            for(unsigned int k=0; k<vectorOfTrialData_n[i][j].size(); k++){
                ASSERT_NEAR(vectorOfTrialData_n[0][j][k], vectorOfTrialData_n[i][j][k], 1e-08);
            }
        }
    }

    for(unsigned int i=0; i<vectorOfTrialData_m.size();i++){
        for(unsigned int j = 0; j<vectorOfTrialData_m[i].size(); j++){
            for(unsigned int k=0; k<vectorOfTrialData_m[i][j].size(); k++){
                ASSERT_NEAR(vectorOfTrialData_m[0][j][k], vectorOfTrialData_m[i][j][k], 1e-08);
            }
        }
    }

}