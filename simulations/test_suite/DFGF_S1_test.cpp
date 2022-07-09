#include "gtest/gtest.h"
#include "../headers/DFGF_S1.hpp"

TEST (DFGF_S1___Test, checkEigenvalues){
    int n =5;
    ASSERT_EQ(n,5);
}

// #include "randvecs.h"
// #include "sample_max_class.h"
// using namespace std;
// // test eigval
// // test eigfcn
// // test dfgf
// // test compute_max 
// // need mocking
// vector<double> case0{};
// vector<double> case1{};
// vector<double> case2{};
// vector<double> case3{};
// vector<double> case4{};
// vector<double> case6{};
// vector<double> case7{};
// vector<double> case8{};
// vector<double> case9{};
// TEST(MaxTests, test_compute_max){
//     SampleMax m(0,0,0,0)    
//     EXPECTED_EQ(,case0{})
//     EXPECTED_EQ(,case1{})
//     EXPECTED_EQ(,case2{})
//     EXPECTED_EQ(,case3{})
//     EXPECTED_EQ(,case4{})
//     EXPECTED_EQ(,case5{})
//     EXPECTED_EQ(,case6{})
//     EXPECTED_EQ(,case7{})
//     EXPECTED_EQ(,case8{})
//     EXPECTED_EQ(,case9{})
            
// }


// test gen_rand_vec
// test linspaced

// void test_rand_vec(){
// 	int n = 12;
// 	vector<double> random = gen_rand_vec(n);
// 	cout << "Random Vector Sample" << '\n';
// 	for(int k=0; k<n; k++) {
// 		cout << random[k] << ',';
// 	}
// }

// void test_arithmetic(){
// 	int n = 10;
// 	vector<double> V = { 0.0, 3.4, .69, .72, .85, .43, -.43, -1.2, -1.16, 0.8 };
// 	//gen_rand_vec(num_vals);

// 	cout << "Vector Sample" << '\n';

// 	for(int k=0; k<n; k++) {
// 		cout << V[k] << ',';
// 	}

// 	cout << '\n' << "3rd Eigenfunction" << '\n';
	
// 	for(int k=0; k<n; k++) {
// 		cout << eigfcn(3.0,n,1.0*k)  << ',';
// 	}

// 	cout << '\n' << "5rd Eigenfunction" << '\n';
	
// 	for(int k=0; k<n; k++) {
// 		cout << eigfcn(5.0,n,1.0*k)  << ',';
// 	}

// 	cout << '\n' << "7th Eigenfunction" << '\n';
	
// 	for(int k=0; k<n; k++) {
// 		cout << eigfcn(7.0,n,1.0*k)  << ',';
// 	}

// 	cout <<'\n' << "Eigenvalues" << '\n';
	
// 	for(int r=0; r<n; r++) {
// 		cout << eigval(r,1.0*n)  << ',';
// 	}

// 	cout <<'\n' << "Eigenvalues to -.25" << '\n';
	
// 	for(int r=0; r<n; r++) {
// 		cout << pow(eigval(1.0*r,n),-1.0*s)  << ',';
// 	}

// 	cout << '\n' << "Values of DFGF(s)" << '\n';
	
// 	for(int k=0; k<n; k++) {
// 		cout << dfgf(s,n,1.0*k,V)  << ',';
// 	}
// }

// void test_linspace() {
// 	int start_ind = 10;
// 	int end_ind = 160;
// 	int num_ind = 32;

// 	linspace(start_ind, end_ind, num_ind);
// }