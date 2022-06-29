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
      int len;                                          //
      default_random_engine generator;                  //
      unsigned generate_seed();                         //
    Public:
      vector<vector<double>> parallelSampler();         //
      vector<double> gen_rand_vec();                    //

## DFGF (Abstract)

---
**Description of what is going on.**

    Private:
        int n;                                          // comment here
        double s;                                       //
        int numTrials;                                  //
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
        vector<double> eigVals;                         //
        vector<vector<double>> coeffs;                  //
        RandVec gaussianVector;                         //
        vector<vector<double>> gaussSamples;            //
        vector<vector<double>> eigenFuncs;              // 
        vector<double> computeFullEigenVector(int r)    //
        vector<double> computeFullEigenFunction(int r)  //
    Public:
        DFGF_S1(n,s,randVec, numTrials);                //
        DFGF_S1();                                      //
        double evaluatePoint(int k);                    //
        vector<double> evaluate();                      //
        vector<vector<double>> runTrials();             //
        double getMax;                                  //
        double emperialMean();                          //

### Naming Conventions

---
- camelCase
- Abbreviations lowercase
- Classes capitalized
