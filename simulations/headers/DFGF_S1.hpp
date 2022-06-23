#ifndef DFGF_S1_H
#define DFGF_S1_H

#include "RandVec.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

class DFGF_S1 {
    private:
        double s; //paramater for the discrete fractional gaussian field (this generally stays fixed so we can observe the limiting behaviors)
        int n;
        vector<double> k_vals;
        RandVec z_vars;

    public:
        DFGF_S1(double s, int n, RandVec rand_vector);
        double eigval(int r);
        double eigfcn(int r, int k);
        double dfgf(int k);
        double compute_max();
};

#endif