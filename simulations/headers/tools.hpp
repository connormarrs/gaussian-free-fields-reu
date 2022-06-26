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

//pasting this cause im having importing problems 
vector<int> Tools::linspace(int start_in, int end_in, int num_in) {
	vector<int> linspaced;
	
	int start = static_cast<int>(start_in);
	int end = static_cast<int>(end_in);
	int num = static_cast<int>(num_in);
	
	if (num == 0) { 
		return linspaced; 
	}
	if (num == 1) {
		linspaced.push_back(start);
		return linspaced;
	}
	
	int delta = (end - start) / (num - 1);
	
	for(int i=0; i < num-1; ++i) {
		linspaced.push_back(start + delta * i);
	}
	
	return linspaced;
}


#endif