#Makefile for simulations code. 
#Attempted by Alexander Neuschotz; refined by others.

CXX = clang++

CXXFLAGS = -g -Wall -std=c++11

#driver = executable main
driver: driver.o DFGF_S1.o RandVec.o tools.o
	$(CXX) $(CXXFLAGS) -o driver driver.o DFGF_S1.o RandVec.o tools.o

driver.o: ../src/driver.cpp ../headers/DFGF_S1.hpp ../headers/RandVec.hpp ../headers/tools.hpp
	$(CXX) $(CXXFLAGS) -c ../src/driver.cpp -o driver.o

DFGF_S1.o: ../headers/DFGF_S1.hpp ../headers/RandVec.hpp
	$(CXX) $(CXXFLAGS) -c ../headers/DFGF_S1.hpp ../headers/RandVec.hpp -o DFGF_S1.o

RandVec.o: ../headers/RandVec.hpp
	$(CXX)  $(CXXFLAGS) -c ../headers/RandVec.hpp -o RandVec.o

tools.o: ../headers/tools.hpp
	$(CXX)  $(CXXFLAGS) -c ../headers/tools.hpp -o tools.o

clean:
	rm -rf ./out/*