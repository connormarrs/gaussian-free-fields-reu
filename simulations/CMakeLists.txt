cmake_minimum_required(VERSION 3.22)

set(This Gaussian-Free-Fields-REU)

project(Gaussian-Free-Fields-REU C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDPENDENT_CODE ON)

enable_testing()

add_subdirectory(test_suite)

set(headers
    ./headers/DFGF_S1.hpp
    ./headers/DFGF.hpp
    ./headers/RandVec.hpp
    ./headers/tools.hpp
)
set(Sources
    DFGF_S1.cpp
    driver.cpp
    RandVec.cpp
    tools.cpp
)
# set(test-suite
#     DFGF_S1_test.cpp
#     RandVec.cpp
# )

add_library(Gaussian-Free-Fields-REU STATIC ./src/DFGF_S1.cpp
./src/driver.cpp
./src/RandVec.cpp
./src/tools.cpp
./headers/DFGF_S1.hpp
./headers/DFGF.hpp
./headers/RandVec.hpp
./headers/tools.hpp
)

# add_subdirectory(test-suite)