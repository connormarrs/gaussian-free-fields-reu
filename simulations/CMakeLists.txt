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
"./src/DFGF_T2.cpp"
"./src/driver.cpp"
"./src/RandVec.cpp"
"./src/tools.cpp"
"./headers/DFGF.hpp"
"./headers/DFGF_S1.hpp"
"./headers/DFGF_T2.hpp"
"./headers/driver.hpp"
"./headers/RandVec.hpp"
"./headers/tools.hpp"
"./headers/DFGF_S1.h"
"./headers/DFGF_T2.h"
"./headers/driver.h"
"./headers/RandVec.h"
"./headers/tools.h"
"./headers/DFGF.h"
)

file(GLOB USER_FILES_2
"./src/DFGF_S1.cpp"
"./src/DFGF_T2.cpp"
"./src/RandVec.cpp"
"./src/tools.cpp"
"./headers/DFGF.hpp"
"./headers/DFGF_S1.hpp"
"./headers/DFGF_T2.hpp"
"./headers/RandVec.hpp"
"./headers/tools.hpp"
"./headers/DFGF_S1.h"
"./headers/DFGF_T2.h"
"./headers/RandVec.h"
"./headers/tools.h"
"./headers/DFGF.h"
)

file(GLOB TEST_FILES_ALL RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
"./test_suite/DFGF_S1_test.cpp"
"./test_suite/driver_test.cpp"
"./test_suite/RandVec_test.cpp"
"./test_suite/tools_test.cpp"
)

file(GLOB TEST_FILES_DFGF_S1 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
"./test_suite/DFGF_S1_test.cpp"
)

file(GLOB TEST_FILES_DFGF_T2 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
"./test_suite/DFGF_T2_test.cpp"
)

file(GLOB TEST_FILES_DRIVER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
"./test_suite/driver_test.cpp"
)

file(GLOB TEST_FILES_RANDVEC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
"./test_suite/RandVec_test.cpp"
)

file(GLOB TEST_FILES_TOOLS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
"./test_suite/tools_test.cpp"
)

# Try to Find GTest
find_package(GTest QUIET)

if(GTEST_FOUND)
	message(">> GTest was found among local libraries.")
	include_directories(${GTEST_INCLUDE_DIRS})

    # create an executable for driver 
	add_executable( run_driver ${USER_FILES_1} )
	target_link_libraries( run_driver gtest_main ${GTEST_LIBRARIES} pthread)

    # create an executable for tools tests 
	add_executable( run_tools_tests ${TEST_FILES_ALL} ${USER_FILES_2} )
	target_link_libraries( run_tools_tests gtest_main ${GTEST_LIBRARIES} pthread)

    # create an executable for RandVec tests 
	add_executable( run_RandVec_tests ${TEST_FILES_ALL} ${USER_FILES_2} )
	target_link_libraries( run_RandVec_tests gtest_main ${GTEST_LIBRARIES} pthread)

    # create an executable for DFGF_S1 tests 
	add_executable( run_DFGF_S1_tests ${TEST_FILES_ALL} ${USER_FILES_2} )
	target_link_libraries( run_DFGF_S1_tests gtest_main ${GTEST_LIBRARIES} pthread)

	# create an executable for DFGF_T2 tests 
	add_executable( run_DFGF_T2_tests ${TEST_FILES_ALL} ${USER_FILES_2} )
	target_link_libraries( run_DFGF_T2_tests gtest_main ${GTEST_LIBRARIES} pthread)

    # create an executable for driver tests 
	add_executable( run_driver_tests ${TEST_FILES_ALL} ${USER_FILES_1} )
	target_link_libraries( run_driver_tests gtest_main ${GTEST_LIBRARIES} pthread)

    # create an executable for all tests 
	add_executable( run_all_tests ${TEST_FILES_ALL} ${USER_FILES_1} )
	target_link_libraries( run_all_tests gtest_main ${GTEST_LIBRARIES} pthread)

else()
	message(">> Couldn't find Local GTest library, Downloading one instead ...")

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

    # create an executable for driver 
	add_executable( run_driver ${USER_FILES_1} )
	target_link_libraries( run_driver gtest_main)

    # create an executable for DFGF_S1 tests 
	add_executable( run_DFGF_S1_tests ${TEST_FILES_ALL} ${USER_FILES_2} )
	target_link_libraries( run_DFGF_S1_tests gtest_main)

	# create an executable for DFGF_T2 tests 
	add_executable( run_DFGF_T2_tests ${TEST_FILES_ALL} ${USER_FILES_2} )
	target_link_libraries( run_DFGF_T2_tests gtest_main)

    # create an executable for driver tests 
	add_executable( run_driver_tests ${TEST_FILES_ALL} ${USER_FILES_1} )
	target_link_libraries( run_driver_tests gtest_main)

    # create an executable for RandVec tests 
	add_executable( run_RandVec_tests ${TEST_FILES_ALL} ${USER_FILES_2} )
	target_link_libraries( run_RandVec_tests gtest_main)

    # create an executable for tools tests 
	add_executable( run_tools_tests ${TEST_FILES_ALL} ${USER_FILES_2} )
	target_link_libraries( run_tools_tests gtest_main)

	# create an executable for all tests 
	add_executable( run_all_tests ${TEST_FILES_ALL} ${USER_FILES_1} )
	target_link_libraries( run_all_tests gtest_main)

endif()

ENABLE_TESTING()