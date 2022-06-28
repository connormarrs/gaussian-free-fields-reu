# Author: Trent Rabe

output: driver.o DFGF_S1.o RandVec.o tools.o
	g++ -std=c++11 -pthread driver.o DFGF_S1.o RandVec.o tools.o -o output

driver.o: ./src/driver.cpp ./headers/DFGF_S1.hpp
	g++ -std=c++11 -c ./src/driver.cpp -o driver.o

DFGF_S1.o: ./src/DFGF_S1.cpp ./headers/DFGF_S1.hpp ./headers/RandVec.hpp ./headers/tools.hpp
	g++ -std=c++11 -c ./src/DFGF_S1.cpp -o DFGF_S1.o

RandVec.o: ./src/RandVec.cpp ./headers/RandVec.hpp
	g++ -std=c++11 -c ./src/RandVec.cpp -o RandVec.o

tools.o: ./src/tools.cpp ./headers/tools.hpp
	g++ -std=c++11 -c ./src/tools.cpp

clean:
	rm *.o