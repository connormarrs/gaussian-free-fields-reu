#ifndef DFGF_H
#define DFGF_H

#include "RandVec.hpp"
#include "tools.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

/**
 * DFGF: Abstract class that allows one to simulate a discrete
 *  fractional field on some space. Requires methods to compute the mean and
 *  the empirical mean for a large number of trials.
 */
class DFGF {
    public:
        virtual double getEmpMean()=0;
    protected:
        int n;
        double s;
        int numTrials;
};

#endif