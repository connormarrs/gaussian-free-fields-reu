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
#include <chrono>
#include <cstdint>
#include <future>
using namespace std;

class Tools {
    public:
        static vector<int> linspace(int start_in, int end_in, int num_in);
		static vector<double> fracpowers(int start_in, int end_in, int num_in,double s, int thread_num);
		static vector<double> joinVecs(vector<double> A, vector<double> B);
		static vector<double> exponentiate(vector<int> A, double s, int start, int stop);
		static void printVector(vector<double> input);
		static double sampleMean(vector<double> data);
		static double compute_max(vector<double> data);
		static void prINTVector(vector<int> input);
		static bool vectComparison(vector<double> x, vector<double> y);
};
#endif
