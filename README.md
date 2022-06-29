# gaussian-free-fields-reu
**Decription of overall code here**

## driver.cpp

---
**Description of what is going on.**

    Add in functions here
    

## RandVec

---
**Description of what is going on.**

    Private:
      vector<distribution>;                             // comment here
      int len;                                          // gives the length of random sequences generated by this object
      default_random_engine generator;                  //
      unsigned generate_seed();                         // used to generate a seed to ensure independence for multithreaded sampling
    Public:
      vector<vector<double>> parallelSampler();         // creates an array of independent gaussian random variables
      vector<double> sample();                          // samples a vector of standard normal of length n

## DFGF (Abstract)

---
**Description of what is going on.**

    Private:
        int n;                                          // degree of DFGF
        double s;                                       // parameter of DFGF
        int numTrials;                                  // number of trals to be ran
        vector<double> maxSamples;                      //
    Public:
        virtual void sample();                          //
        virtual double computeMax();                    //
        virtual double computEmpMean();                 //

## DFGF_S1:public DFGF

---
**Description of waht is going on**

    Private:
        vector<double> domain;                          // comment here
        vector<double> eigVals;                         // computes the vector of eigen values associated with the field of degree n
        vector<vector<double>> coeffs;                  // computes the coefficients for evaluating the fields
        RandVec gaussianVector;                         // a random vector that will be sampled
        vector<vector<double>> gaussSamples;            // an n by trials array of standard normal gaussian random variables
        vector<vector<double>> eigenFuncs;              // array of eigen vectors
        vector<double> computeFullEigenVector(int r)    // 
        vector<double> computeFullEigenFunction(int r)  //
    Public:
        DFGF_S1(n,s,randVec, numTrials);                // constructor
        DFGF_S1();                                      //
        double evaluatePoint(int k);                    // evaluates a point of the dfgf
        vector<double> evaluate();                      // evaluates the whole field
        vector<vector<double>> runTrials();             // runs the trials using multi threading
        double getMax;                                  // gets the maxima of each resulting thread and pushes it back to the maxima vector
        double emperialMean();                          // returns the means

### Naming Conventions

---
- camelCase
- Abbreviations lowercase
- Classes capitalized
