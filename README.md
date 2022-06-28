# gaussian-free-fields-reu

## RandVec

---
    Private:
      vector<distribution>;
      int len;
      default_random_engine generator;
      unsigned generate_seed();
    Public:
      vector<vector<double>> parallelSampler();
      vector<double> gen_rand_vec();

## DFGF (Abstract)

---
    Private:
        int n;
        double s;
        int numTrials;
        vector<double> maxSamples;
    Public:
        virtual void sample();
        virtual double computeMax();
        virtual double computEmpMean();

## DFGF_S1:public DFGF

---
    Private:
        vector<double> domain;
        vector<double> eigVals;
        vector<vector<double>> coeffs;
        RandVec gaussianVector;
        vector<vector<double>> gaussSamples;
        vector<vector<double>> eigenFuncs;
    Public:
        DFGF_S1(n,s,randVec, numTrials);
        DFGF_S1();
        double evaluatePoint(int k);
        vector<double> evaluate();
        vector<vector<double>> runTrials();
        double getMax;
        double emperialMean();

### Naming Conventions

---

- camelCase
- Abbreviations lowercase
- Classes capitalized
