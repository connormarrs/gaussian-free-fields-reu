#Author: Trent Rabe

cmake_minimum_required(VERSION 3.14)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
	GIT_REPOSITORY    https://github.com/google/googletest.git
	GIT_TAG           release-1.12.1
	SOURCE_DIR        "/home/elevensor/test/gff/gaussian-free-fields-reu/simulations/build/googletest-src"
	BINARY_DIR        "/home/elevensor/test/gff/gaussian-free-fields-reu/simulations/build/googletest-build"
	CONFIGURE_COMMAND ""
	BUILD_COMMAND     ""
	INSTALL_COMMAND   ""
	TEST_COMMAND      ""
)
