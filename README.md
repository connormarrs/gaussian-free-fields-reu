# gaussian-free-fields-reu
**Decription of overall code here**

## driver.cpp

---
**Description of what is going on.**
    
    

## RandVec

---
**RandVec is a class with two integer attributes called 'lenVec' and 'numTrials' that is designed to generate an array of doubles called 'samples' of size 'numTrials' x 'lenVec', whose rows consist of samples of a normal distribution with mean 0 and variance 1. This will be used for computing trial data for DFGF_S1.**

**When RandVec::RandVec(maxN, NumTrials) is called by a user, it passes on its two arguments to the attributes of RandVec, respectively, and creates an array of numTrial rows, each of length maxN and consisting only of 0.0's. It then passes this array, which serves to keep track of the desired dimensions, to RandVec::threadSafe_Sample(), where multi-threading is used along with RandVec::sample_univariate_gaussian(unsigned int seed, int index) to randomly fill out 'samples'. In particular, there are lenVec threads, where the j'th thread, for j between 0 and lenVec-1, randomly fills out the j'th column of 'samples' by calling RandVec::sample_univariate_gaussian((unsigned int) j, j), before joining with the other threads and together producing the entirety of 'samples'. Randomness is ensured by the application of the Mersenne Twister algorithm mt19937.**

**RandVec::getSample(int size) takes in an integer 'size' returns a 'numTrials' x 'size' subarray of samples.**

    Public:
      RandVec(int maxN, int numTrials);                 // generates an array 'samples' of size maxN x numTrials
      RandVec() = default;                              // default constructor
      ~RandVec() = default;                             // default destructor
      vector<vector<double>> getSample(int size);       // returns the numTrials x size subarray from 'samples' 

    Private:
      int lenVec;                                       // the number of data points taken from each Gaussian
      int numTrials;                                    // the number of trials = number of Gaussians
      vector<vector<double>> samples                    // an array, whose rows are trials
      void sample_univariate_gaussian(unsigned int seed, int index); // generates in the 'index'th column of 'samples'
      void threadSafe_Sample();                         // generates all columns of 'samples' with multithreading

## RandArr

---
**RandArr is a class with two integer attributes called 'dimArray' and 'numTrials' that is designed to generate a vector 'samples' of size 'numTrials', consiting of trials that are each arrays of dimension 'dimArray' containing samples of a normal distribution with mean 0 and variance 1. This will be used for computing trial data for DFGF_T2.**

**When RandArr::RandArr(maxN, NumTrials) is called, it passes on its two arguments to the attributes of RandArr, respectively, and creates a vector of 'numTrials' arrays, each of dimension 'maxN' and consisting only of 0.0's. It then passes this vector, which serves to keep track of the desired dimensions, to RandArr::threadSafe_Sample(), where multi-threading is used along with RandArr::sample_univariate_gaussian(unsigned int seed, int index1, int index2) to randomly fill out 'samples'. In particular, there are 'dimArr'^2 threads corresponding to 0 <= j,k <= 'dimArr', where the thread corresponding to a given j and k randomly fills out the (k,j)th entry of all of all of the arrays in 'samples' by calling RandArr::sample_univariate_gaussian((unsigned int) (j*'dimArray'+k), j, k), before joining the other threads and together producing the entirety of 'samples'. Randomness is ensured by the application of the Mersenne Twister algorithm mt19937.**

**RandArr::getSample(int size) takes in an integer 'size' and returns a vector, 'subArray', consisting of the 'size'x'size' subarrays of each of the arrays in 'sample'.**

    Public:
      RandArr(int maxDim, int numTrials);         // generates a vector 'samples' of 'numTrials' arrays with dim = 'maxdim'
      RandVec() = default;                        // default constructor
      ~RandVec() = default;                       // default destructor
      vector<vector<vector<double>>> getSample(int size); // returns a vector of 'size'' x 'size' subarrays of 'samples'.

    Private:
      int dimArray;                               // the dimension of the arrays in 'samples'
      int numTrials;                              // the number of arrays in 'samples'
      vector<vector<vector<double>>> samples      // a vector of arrays that are trials
      void sample_univariate_gaussian(unsigned int seed, int index1, int index2); // generates in the ('index1', 'index2')'th entry of the arrays in'samples'
      void threadSafe_Sample();                   // generates all arrays of 'samples' with multithreading

## Tools

---

**Provides importable tools, primarily for driver. compute_max is used to compute the max of trials in DFGF_S1.**

    public:
        static double compute_max(vector<double> data)

## DFGF (Abstract)

---
**DFGF is an abstract class to set up all DFGF_* files with protected arguments. It imports RandVec and Tools for all DFGF modules.**

    Public:
        virtual double getEmpMean()=0;                  // to be defined in all DFGF modules

    Protected:
        int n;                                          // number of random variables whose mean is being taken
        double s;                                       // s parameter
        int numtrials;                                  // number of trials


## DFGF_S1:public DFGF

---
**DFGF_S1 is a class designed to get trial data for the DFGF of S1 for a given n and s. Given a double 'sVal', an int 'nVal', and a RandVec object 'randVector', DFGF_S1::DFGF_S1 takes the 'numTrials' x 'nVals' subarray of randVector::samples with the function randVector::getSample, and copies it into an array called 'gaussianVector', before calling DFGF_S1::computeEigenvals(), DFGF_S1::computeEigenVectors(), and DFGF_S1::computeCoeffs(). DFGF_S1::computeEigenvals() iterates over a parameter 0 <= r <= 'nVal', calculating the r'th eigenvalue with DFGF_S1::computeEigenVal(r), and pushes the results into a vector, 'eigenVals', that is returned by DFGF_S1::getEigenVals(). DFGF_S1::computeEigenVectors creates a vector, 'eigenVectors', of eigenvectors, where the r'th eigenvector is calculated with DFGF_S1::computeEigenFunctionVector(r) by calclating the k'th entry of the r'th eigenvector with DFGF::computeEigenFunctionPoint(r, k) and pushing it to a vector 'eigenVector'. 'eigenvectors' is returned by DFGF_S1::getEigenVectors(). Finally, DFGF_S1::DFGFS_1 calls computeCoeffs(), which uses the eigenvalues and eigenvectors to compute the coefficients and push them to a vector 'coefficients' of coeffficient vectors, where the r'th coefficient vector is calculated by computeCoefficientVector(r) by calculating the k'th entry of the r'th coefficient vector with DFGF_S1::computeCoeffPoint(r, k) and pushing it to a vector 'coefficientVector'. 'coefficients' is return by DFGF_S1::getCoeffs().**

**DFGF_S1::evaluatePoint(k, sampleVector) uses the definition of the DFGF for S1 to calculate the sum for θ_k with the values for the random variables taken from 'sampleVector'. DFGF_S1::evaluate(gaussianVector[i]) then iterates over all k < 'nVal' and creates a vector 'dfgf' of the sums for 'sampleVector' = gaussianVector[i], which is then collected by DFGF_S1::runTrials() into a vector 'trialData', for all i < 'nVal', that is returned by getTrialData(). DFGF_S1::runTrials() then initiates computeMaxVectors(), which uses Tools::compute_max to create a vector 'maxima', returned by DFGF_S1::getMaximaList(), whose j'th entry is the maximum of the j'th trial in 'trialData', and DFGF_S1::computeEmpMean(), which calculates the mean of those maxima, 'meanOfMaxima', which is returned by getEmpMean().**

    Public:
        \\ copies a subarray of a 'samples' array and calls computeEigenVals(), computeEigenVectors(), and computeCoeffs()
        DFGF_S1(double s, int n, int numberTrials, RandVec gaussianVector); 
        DFGF_S1()=default;                                      \\ default constructor
        ~DFGF_S1()=default;                                     \\ default destrutor

        vector<double> getEigenVals()                           \\ returns 'eigenVals'
        \\ computes the eigenfunction for the k'th entry of the r'th eigenvector
        double computeEigenFunctionPoint(int r, int k);         
        \\ creates a vector of eigenfunctions for the r'th eigenvector                                             
        vector<double> computeEigenFunctionVector(int r);      
        vector<vector<double>> getEigenVectors();               \\ returns 'eigenVectors'
        vector<vector<double>> getTrialData()                   \\ returns 'trialData'
        vector<double> getMaximaList();                         \\ returns 'maxima'
        double getEmpMean()                                     \\ returns 'meanOfMaxima'

        \\ computes the k'th coefficient of the r'th coefficient vector
        double computeCoeffPoint(int r, int k);                 
        vector<double> computeCoefficientVector(int r);         \\ creates the r'th coefficient vector
        vector<vector<double>> getCoeffs();                     \\ reutrns 'coefficients'

        \\ calculates the DFGF_S1 sum at θ_k with 'sampleVector' providing the values of the random variables
        double evaluatePoint(int k, vector<double> sampleVector); 
        \\ creates a vector of DFGF_S1 sums with 'sampleVector' providing the values of the random variables
        vector<double> evaluate(vector<double> sampleVector)    
        void computeMaxVectors();                               \\ fills 'maxima' with the maxima of the trialdata
        \\ calls 'evalutate' for each row of gaussianVector, appending to 'trialData', and call computeMaxVectors() and computeEmpMean()
        void runTrials();                                       
        debugRunTrials();                                       \\ same as runtrials, except does not call anything.
        void computeEmpMean();                                  \\ calculates 'meanofMaxima'

    Private:
        vector<double> eigenVals;                               \\ the eigenvalues
        vector<vector<double>> eigenVectors;                    \\ the eigen vectors
        vector<vector<double>> coefficients;                    \\ the coefficients for DFGF_S1
        vector<vector<double>> gaussianVector;                  \\ a copy of a sample array from a 'RandVec' object
        vector<vector<double>> trialData;                       \\ an array of trial data
        vector<double> maxima                                   \\ a vector of the maxima of the trial data
        double meanOfMaxima                                     \\ the mean of the elements in 'maxima'

        void computeEigenVals();                                \\ computes eigenvalues
        double computeEigenVal(int k);                          \\ computes the k'th eigenvalue 
        void computeEigenVectors();                             \\ computes eigenvectors
        void computeCoeffs();                                   \\ compute coefficients for DFGF_S1


## DFGF_T2:public DFGF

---
**DFGF_T2 is a class designed to get trial data for the DFGF of T2 for a given n and s. Given a double 'sVal', an int 'nVal', and a RandArr object 'gaussianArray', DFGF_T2::DFGF_T2 passes these arguments, to its attributes 'n', 's', and 'gaussianArray', respectively, before calling DFGF_T2::computeEigenvals(), DFGF_T2::computeEigenVectors(), and DFGF_T2::computeCoeffs(). DFGF_S2::computeEigenvals() creates a vector, 'eigenVals' of vectors 'eigenvals_p', which contain the eigenvalues associated to a given 0 <= p <= n-1, for every 0 <= q <= n-1, as calculated by DFGF_T2::computeEigenVal(p, q). 'eigenVals' is reurned by getEigenVals(). Similarly, DFGF_T2::computeEigenFunctionPoint(p, q, j, k) calculates the eigenfunction point for a given p, q, j, and k, which is used by DFGF_T2::computeEigenFunctionVector(p, q) to create a vector 'eigenVect' of vectors 'eigVect_j' containing all eigenvectors associated to that value of j and the given p and q, which is itself used by DFGF_T2::computeEigenVectors() to create a vector 'eigenVectors' of all 'eigenVect's, which is returned by DFGF_T2::getEigenVectors(). DFGF_T2::CoefficientPoint(p, q, j, k), DFGF_T2::computeCoefficientVector(p, q), and DFGF_T2::computeCoeffs() does the same thing with coefficient vectors, creating, respectively, the coefficient point associated to p, q, j, and k; the vector 'coeffs_pq' of vectors 'coeffs_pqj' containing all coefficients associated to the given p, q, and j; and the vector 'coefficients' of all 'coeffs_pqj's. 'coefficients' is returned by DFGF_T2::getCoefficients().**

**DFGF_T2::evaluatePoint(j, k, 'sampleVector') evaluates the sum of the terms of DFGF_T2 that look like c_{p,q}(θ_i, θ_j) * Z_{p, q}, where the gaussian random variables Z_{p,q} are taken from 'sampleVector', and DFGF_T2::evaluate('sampleVector') creates a vector 'dfgf' containing all vectors 'dfgfRow' that themselves contain the above sum for a fixed j and varying k. DFGF_T2::runTrials(), then runs evaluate on all of the arrays in 'gaussianArray', working with asynchronous tasks, and collects the results in a vector 'trialData'. From there, DFGF_T2::computeMaxVectors() calculates the maxima of each of these trials and collects them in a vector 'maxima', from which the mean of the maxima, 'meanOfMaxima' is calulated by DFGF_T2::computeEmpMean() and returned by DFGF_T2::getEmpMean()**

    public:
        \\ Sets the values of 'n', 's', 'gaussianArray', and 'numTrials', and calls computeEigenVals(), computeEigenVectors(), and computeCoeffs()
        DFGF_T2(double sVals, int nVals, int numberTrials, RandArr randomArray); 
        DFGF_T2()=default;                          \\ default constructor
        ~DFGF_T2()=default;                         \\ default destructor                                     
        vector<vector<double>> getEigenVals();      \\ returns eigenVals
        \\ computes the eigen function at a point associated to p, q, j, and k
        double computeEigenFunctionPoint(int p, int q, int j, int k); 
        vector<vector<double>> computeEigenFunctionVector(int p, int q); \\ computes all eigenvectors with a given p and q
        vector<vector<vector<vector<double>>>> getEigenVectors(); \\ returns 'eigenVectors'

        \\ compute coefficients at a point associated to p, q, j, and k
        double computeCoefficientPoint(int p, int q, int j, int k);
        vector<vector<double>> computeCoefficientVector(int p, int q); \\ computes all coefficeints with a given p and q
        vector<vector<vector<vector<double>>>> getCoefficients(); \\ returns 'coefficients'

        \\ sums DFGF_T2 at the point j,k with Guassian random variable points taken from 'sampleVector'
        double evaluatePoint(int j, int k, vector<vector<double>> sampleVector);
        \\ creates a vector 'dfgf' of vectors 'dfgfRow' containing the sum of DFGF_T2 with fixed j and varying k
        vector<vector<double>> evaluate(vector<vector<double>> sampleVector);

        void computeEigenVals();                    \\ computes 'eigenVals'

        void runTrials();                           \\ runs 'evaluate' on all arrays in 'randomArray'
        double computeEmpMean();                    \\ comoputes 'meanOfMaxima'
        double getEmpMean();                        \\ returns 'meanOfMaxima'
        \\ same as runtrials, except using 'testRandomArrs' instead of 'sampleVector'
        vector<vector<vector<double>>> debugRunTrials(vector<vector<vector<double>>> testRandomArrs);

    private:
        int n;                                      \\ number of random variables
        double s;                                   \\ s parameter
        vector<vector<double>> eigenVals;           \\ eigenvalues
        vector<vector<vector<vector<double>>>> eigenVectors;    \\ eigenvectors
        vector<vector<vector<vector<double>>>> coefficients;    \\ coefficients
        RandArr gaussianArray;                      \\ RandArr object containing a vector of arrays that become trials
        vector<vector<vector<double>>> trialData;   \\ the result of running 'evaluate' on 'gaussianArray'
        vector<double> maxima;                      \\ vector of the maxima of the trials
        double meanOfMaxima;                        \\ the average of the maxima of the trials

        double computeEigenVal(int p, int q);       \\ computes the eigenvalues associated to p and q
        void computeEigenVectors();                 \\ computes the eigenvectors
        void computeCoeffs();                       \\ computes the coefficients
        void computeMaxVectors();                   \\ computes the vector of maxima
### Naming Conventions

---
- camelCase
- Abbreviations lowercase
- Classes capitalized


#### Data Files
In order to keep the output data organized use the following convention.
(Month)(Day).StartVal.EndVal.NumberofPoints.NumberofTrials.TimetoComputeN.csv

For example, data generated on July 2nd, starting at 50 and ending at 1000, with 190 points, and 1500 trials per point would take the form
702.50.1000.190.1500.csv
