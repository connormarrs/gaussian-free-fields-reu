cmake_minimum_required(VERSION 3.22)

set(This2 DFGF_S1_test)

set(src
    DFGF_S1_test.cpp
    # RandVec_test.cpp
)

add_library(DFGF_S1_test DFGF_S1_test.cpp)
target_link_libraries(DFGF_S1_test PUBLIC
    gtest_main
    Gaussian-Free-Fields-REU
)

add_test(
    NAME $(This2)
    COMMAND $(This2)
)