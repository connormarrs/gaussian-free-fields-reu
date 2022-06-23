#ifndef TOOLS_H
#define TOOLS_H

#define _USE_MATH_DEFINES

#include <float.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <fstream>

using namespace std;

class Tools {
    public:
        static vector<int> linspace(int start_in, int end_in, int num_in);
};

#endif