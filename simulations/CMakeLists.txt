#Author: Trent Rabe

cmake_minimum_required(VERSION 3.14)

# set default build to debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Release or Debug" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall" CACHE INTERNAL "")

# get folder name as project name
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

##############################################
# define cmmake variables for file locations #
##############################################
file(GLOB USER_FILES_1
"./src/DFGF_S1.cpp"
"./src/driver_s1_maxima.cpp"
"./src/RandVec.cpp"
"./src/RandArr.cpp"
"./src/tools.cpp"
"./headers/DFGF.hpp"
"./headers/DFGF_S1.hpp"
"./headers/RandVec.hpp"
"./headers/RandArr.hpp"
"./headers/tools.hpp"
)

file(GLOB USER_FILES_2
"./src/DFGF_S1.cpp"
"./src/driver_s1_trial_data.cpp"
"./src/RandVec.cpp"
"./src/RandArr.cpp"
"./src/tools.cpp"
"./headers/DFGF.hpp"
"./headers/DFGF_S1.hpp"
"./headers/RandVec.hpp"
"./headers/RandArr.hpp"
"./headers/tools.hpp"
)

file(GLOB USER_FILES_3
"./src/DFGF_T2.cpp"
"./src/driver_t2_maxima.cpp"
"./src/RandVec.cpp"
"./src/RandArr.cpp"
"./src/tools.cpp"
"./headers/DFGF.hpp"
"./headers/DFGF_T2.hpp"
"./headers/RandVec.hpp"
"./headers/RandArr.hpp"
"./headers/tools.hpp"
)

file(GLOB USER_FILES_4
"./src/DFGF_T2.cpp"
"./src/driver_t2_trial_data.cpp"
"./src/RandVec.cpp"
"./src/RandArr.cpp"
"./src/tools.cpp"
"./headers/DFGF.hpp"
"./headers/DFGF_T2.hpp"
"./headers/RandVec.hpp"
"./headers/RandArr.hpp"
"./headers/tools.hpp"
)

file(GLOB USER_FILES_5
"./src/RandVec.cpp"
"./src/RandArr.cpp"
"./src/tools.cpp"
"./headers/DFGF.hpp"
"./headers/RandVec.hpp"
"./headers/RandArr.hpp"
"./headers/tools.hpp"
)

file(GLOB RANDVEC_FILES
"./src/RandVec.cpp"
"./headers/RandVec.hpp"
)

file(GLOB TEST_FILES_DFGF_S1 
"./test_suite/DFGF_S1_test.cpp"
"./src/DFGF_S1.cpp"
"./headers/DFGF_S1.hpp"
)

file(GLOB TEST_FILES_DFGF_T2
"./test_suite/DFGF_T2_test.cpp"
"./src/DFGF_T2.cpp"
"./headers/DFGF_T2.hpp"
)

file(GLOB TEST_FILES_RANDVEC 
"./test_suite/RandVec_test.cpp"
)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
	message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
	message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()
# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
	${CMAKE_CURRENT_BINARY_DIR}/googletest-build
		EXCLUDE_FROM_ALL)

# create an executable for driver_s1_maxima 
add_executable( run_driver_s1_maxima ${USER_FILES_1} )
target_link_libraries( run_driver_s1_maxima gtest_main)

# create an executable for driver_s1_trial_data 
add_executable( run_driver_s1_trial_data ${USER_FILES_2} )
target_link_libraries( run_driver_s1_trial_data gtest_main)

# create an executable for driver_t2_maxima 
add_executable( run_driver_t2_maxima ${USER_FILES_3} )
target_link_libraries( run_driver_t2_maxima gtest_main)

# create an executable for driver_t2_trial_data 
add_executable( run_driver_t2_trial_data ${USER_FILES_4} )
target_link_libraries( run_driver_t2_trial_data gtest_main)

# create an executable for DFGF_S1 tests 
add_executable( run_DFGF_S1_tests ${TEST_FILES_DFGF_S1} ${USER_FILES_5} )
target_link_libraries( run_DFGF_S1_tests gtest_main)

# create an executable for DFGF_T2 tests 
add_executable( run_DFGF_T2_tests ${TEST_FILES_DFGF_T2} ${USER_FILES_5} )
target_link_libraries( run_DFGF_T2_tests gtest_main)

# create an executable for RandVec tests 
add_executable( run_RandVec_tests ${TEST_FILES_RANDVEC} ${RANDVEC_FILES} )
target_link_libraries( run_RandVec_tests gtest_main)

ENABLE_TESTING()
