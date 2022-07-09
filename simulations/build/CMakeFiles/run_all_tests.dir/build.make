# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/felix-klein/gaussian-free-fields-reu/simulations

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/felix-klein/gaussian-free-fields-reu/simulations/build

# Include any dependencies generated for this target.
include CMakeFiles/run_all_tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/run_all_tests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/run_all_tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/run_all_tests.dir/flags.make

CMakeFiles/run_all_tests.dir/test_suite/DFGF_S1_test.cpp.o: CMakeFiles/run_all_tests.dir/flags.make
CMakeFiles/run_all_tests.dir/test_suite/DFGF_S1_test.cpp.o: ../test_suite/DFGF_S1_test.cpp
CMakeFiles/run_all_tests.dir/test_suite/DFGF_S1_test.cpp.o: CMakeFiles/run_all_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/felix-klein/gaussian-free-fields-reu/simulations/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/run_all_tests.dir/test_suite/DFGF_S1_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run_all_tests.dir/test_suite/DFGF_S1_test.cpp.o -MF CMakeFiles/run_all_tests.dir/test_suite/DFGF_S1_test.cpp.o.d -o CMakeFiles/run_all_tests.dir/test_suite/DFGF_S1_test.cpp.o -c /home/felix-klein/gaussian-free-fields-reu/simulations/test_suite/DFGF_S1_test.cpp

CMakeFiles/run_all_tests.dir/test_suite/DFGF_S1_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run_all_tests.dir/test_suite/DFGF_S1_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/felix-klein/gaussian-free-fields-reu/simulations/test_suite/DFGF_S1_test.cpp > CMakeFiles/run_all_tests.dir/test_suite/DFGF_S1_test.cpp.i

CMakeFiles/run_all_tests.dir/test_suite/DFGF_S1_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run_all_tests.dir/test_suite/DFGF_S1_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/felix-klein/gaussian-free-fields-reu/simulations/test_suite/DFGF_S1_test.cpp -o CMakeFiles/run_all_tests.dir/test_suite/DFGF_S1_test.cpp.s

CMakeFiles/run_all_tests.dir/test_suite/RandVec_test.cpp.o: CMakeFiles/run_all_tests.dir/flags.make
CMakeFiles/run_all_tests.dir/test_suite/RandVec_test.cpp.o: ../test_suite/RandVec_test.cpp
CMakeFiles/run_all_tests.dir/test_suite/RandVec_test.cpp.o: CMakeFiles/run_all_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/felix-klein/gaussian-free-fields-reu/simulations/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/run_all_tests.dir/test_suite/RandVec_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run_all_tests.dir/test_suite/RandVec_test.cpp.o -MF CMakeFiles/run_all_tests.dir/test_suite/RandVec_test.cpp.o.d -o CMakeFiles/run_all_tests.dir/test_suite/RandVec_test.cpp.o -c /home/felix-klein/gaussian-free-fields-reu/simulations/test_suite/RandVec_test.cpp

CMakeFiles/run_all_tests.dir/test_suite/RandVec_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run_all_tests.dir/test_suite/RandVec_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/felix-klein/gaussian-free-fields-reu/simulations/test_suite/RandVec_test.cpp > CMakeFiles/run_all_tests.dir/test_suite/RandVec_test.cpp.i

CMakeFiles/run_all_tests.dir/test_suite/RandVec_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run_all_tests.dir/test_suite/RandVec_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/felix-klein/gaussian-free-fields-reu/simulations/test_suite/RandVec_test.cpp -o CMakeFiles/run_all_tests.dir/test_suite/RandVec_test.cpp.s

CMakeFiles/run_all_tests.dir/test_suite/driver_test.cpp.o: CMakeFiles/run_all_tests.dir/flags.make
CMakeFiles/run_all_tests.dir/test_suite/driver_test.cpp.o: ../test_suite/driver_test.cpp
CMakeFiles/run_all_tests.dir/test_suite/driver_test.cpp.o: CMakeFiles/run_all_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/felix-klein/gaussian-free-fields-reu/simulations/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/run_all_tests.dir/test_suite/driver_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run_all_tests.dir/test_suite/driver_test.cpp.o -MF CMakeFiles/run_all_tests.dir/test_suite/driver_test.cpp.o.d -o CMakeFiles/run_all_tests.dir/test_suite/driver_test.cpp.o -c /home/felix-klein/gaussian-free-fields-reu/simulations/test_suite/driver_test.cpp

CMakeFiles/run_all_tests.dir/test_suite/driver_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run_all_tests.dir/test_suite/driver_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/felix-klein/gaussian-free-fields-reu/simulations/test_suite/driver_test.cpp > CMakeFiles/run_all_tests.dir/test_suite/driver_test.cpp.i

CMakeFiles/run_all_tests.dir/test_suite/driver_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run_all_tests.dir/test_suite/driver_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/felix-klein/gaussian-free-fields-reu/simulations/test_suite/driver_test.cpp -o CMakeFiles/run_all_tests.dir/test_suite/driver_test.cpp.s

CMakeFiles/run_all_tests.dir/test_suite/tools_test.cpp.o: CMakeFiles/run_all_tests.dir/flags.make
CMakeFiles/run_all_tests.dir/test_suite/tools_test.cpp.o: ../test_suite/tools_test.cpp
CMakeFiles/run_all_tests.dir/test_suite/tools_test.cpp.o: CMakeFiles/run_all_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/felix-klein/gaussian-free-fields-reu/simulations/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/run_all_tests.dir/test_suite/tools_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run_all_tests.dir/test_suite/tools_test.cpp.o -MF CMakeFiles/run_all_tests.dir/test_suite/tools_test.cpp.o.d -o CMakeFiles/run_all_tests.dir/test_suite/tools_test.cpp.o -c /home/felix-klein/gaussian-free-fields-reu/simulations/test_suite/tools_test.cpp

CMakeFiles/run_all_tests.dir/test_suite/tools_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run_all_tests.dir/test_suite/tools_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/felix-klein/gaussian-free-fields-reu/simulations/test_suite/tools_test.cpp > CMakeFiles/run_all_tests.dir/test_suite/tools_test.cpp.i

CMakeFiles/run_all_tests.dir/test_suite/tools_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run_all_tests.dir/test_suite/tools_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/felix-klein/gaussian-free-fields-reu/simulations/test_suite/tools_test.cpp -o CMakeFiles/run_all_tests.dir/test_suite/tools_test.cpp.s

CMakeFiles/run_all_tests.dir/src/DFGF_S1.cpp.o: CMakeFiles/run_all_tests.dir/flags.make
CMakeFiles/run_all_tests.dir/src/DFGF_S1.cpp.o: ../src/DFGF_S1.cpp
CMakeFiles/run_all_tests.dir/src/DFGF_S1.cpp.o: CMakeFiles/run_all_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/felix-klein/gaussian-free-fields-reu/simulations/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/run_all_tests.dir/src/DFGF_S1.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run_all_tests.dir/src/DFGF_S1.cpp.o -MF CMakeFiles/run_all_tests.dir/src/DFGF_S1.cpp.o.d -o CMakeFiles/run_all_tests.dir/src/DFGF_S1.cpp.o -c /home/felix-klein/gaussian-free-fields-reu/simulations/src/DFGF_S1.cpp

CMakeFiles/run_all_tests.dir/src/DFGF_S1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run_all_tests.dir/src/DFGF_S1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/felix-klein/gaussian-free-fields-reu/simulations/src/DFGF_S1.cpp > CMakeFiles/run_all_tests.dir/src/DFGF_S1.cpp.i

CMakeFiles/run_all_tests.dir/src/DFGF_S1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run_all_tests.dir/src/DFGF_S1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/felix-klein/gaussian-free-fields-reu/simulations/src/DFGF_S1.cpp -o CMakeFiles/run_all_tests.dir/src/DFGF_S1.cpp.s

CMakeFiles/run_all_tests.dir/src/RandVec.cpp.o: CMakeFiles/run_all_tests.dir/flags.make
CMakeFiles/run_all_tests.dir/src/RandVec.cpp.o: ../src/RandVec.cpp
CMakeFiles/run_all_tests.dir/src/RandVec.cpp.o: CMakeFiles/run_all_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/felix-klein/gaussian-free-fields-reu/simulations/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/run_all_tests.dir/src/RandVec.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run_all_tests.dir/src/RandVec.cpp.o -MF CMakeFiles/run_all_tests.dir/src/RandVec.cpp.o.d -o CMakeFiles/run_all_tests.dir/src/RandVec.cpp.o -c /home/felix-klein/gaussian-free-fields-reu/simulations/src/RandVec.cpp

CMakeFiles/run_all_tests.dir/src/RandVec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run_all_tests.dir/src/RandVec.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/felix-klein/gaussian-free-fields-reu/simulations/src/RandVec.cpp > CMakeFiles/run_all_tests.dir/src/RandVec.cpp.i

CMakeFiles/run_all_tests.dir/src/RandVec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run_all_tests.dir/src/RandVec.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/felix-klein/gaussian-free-fields-reu/simulations/src/RandVec.cpp -o CMakeFiles/run_all_tests.dir/src/RandVec.cpp.s

CMakeFiles/run_all_tests.dir/src/driver.cpp.o: CMakeFiles/run_all_tests.dir/flags.make
CMakeFiles/run_all_tests.dir/src/driver.cpp.o: ../src/driver.cpp
CMakeFiles/run_all_tests.dir/src/driver.cpp.o: CMakeFiles/run_all_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/felix-klein/gaussian-free-fields-reu/simulations/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/run_all_tests.dir/src/driver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run_all_tests.dir/src/driver.cpp.o -MF CMakeFiles/run_all_tests.dir/src/driver.cpp.o.d -o CMakeFiles/run_all_tests.dir/src/driver.cpp.o -c /home/felix-klein/gaussian-free-fields-reu/simulations/src/driver.cpp

CMakeFiles/run_all_tests.dir/src/driver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run_all_tests.dir/src/driver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/felix-klein/gaussian-free-fields-reu/simulations/src/driver.cpp > CMakeFiles/run_all_tests.dir/src/driver.cpp.i

CMakeFiles/run_all_tests.dir/src/driver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run_all_tests.dir/src/driver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/felix-klein/gaussian-free-fields-reu/simulations/src/driver.cpp -o CMakeFiles/run_all_tests.dir/src/driver.cpp.s

CMakeFiles/run_all_tests.dir/src/tools.cpp.o: CMakeFiles/run_all_tests.dir/flags.make
CMakeFiles/run_all_tests.dir/src/tools.cpp.o: ../src/tools.cpp
CMakeFiles/run_all_tests.dir/src/tools.cpp.o: CMakeFiles/run_all_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/felix-klein/gaussian-free-fields-reu/simulations/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/run_all_tests.dir/src/tools.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run_all_tests.dir/src/tools.cpp.o -MF CMakeFiles/run_all_tests.dir/src/tools.cpp.o.d -o CMakeFiles/run_all_tests.dir/src/tools.cpp.o -c /home/felix-klein/gaussian-free-fields-reu/simulations/src/tools.cpp

CMakeFiles/run_all_tests.dir/src/tools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run_all_tests.dir/src/tools.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/felix-klein/gaussian-free-fields-reu/simulations/src/tools.cpp > CMakeFiles/run_all_tests.dir/src/tools.cpp.i

CMakeFiles/run_all_tests.dir/src/tools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run_all_tests.dir/src/tools.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/felix-klein/gaussian-free-fields-reu/simulations/src/tools.cpp -o CMakeFiles/run_all_tests.dir/src/tools.cpp.s

# Object files for target run_all_tests
run_all_tests_OBJECTS = \
"CMakeFiles/run_all_tests.dir/test_suite/DFGF_S1_test.cpp.o" \
"CMakeFiles/run_all_tests.dir/test_suite/RandVec_test.cpp.o" \
"CMakeFiles/run_all_tests.dir/test_suite/driver_test.cpp.o" \
"CMakeFiles/run_all_tests.dir/test_suite/tools_test.cpp.o" \
"CMakeFiles/run_all_tests.dir/src/DFGF_S1.cpp.o" \
"CMakeFiles/run_all_tests.dir/src/RandVec.cpp.o" \
"CMakeFiles/run_all_tests.dir/src/driver.cpp.o" \
"CMakeFiles/run_all_tests.dir/src/tools.cpp.o"

# External object files for target run_all_tests
run_all_tests_EXTERNAL_OBJECTS =

run_all_tests: CMakeFiles/run_all_tests.dir/test_suite/DFGF_S1_test.cpp.o
run_all_tests: CMakeFiles/run_all_tests.dir/test_suite/RandVec_test.cpp.o
run_all_tests: CMakeFiles/run_all_tests.dir/test_suite/driver_test.cpp.o
run_all_tests: CMakeFiles/run_all_tests.dir/test_suite/tools_test.cpp.o
run_all_tests: CMakeFiles/run_all_tests.dir/src/DFGF_S1.cpp.o
run_all_tests: CMakeFiles/run_all_tests.dir/src/RandVec.cpp.o
run_all_tests: CMakeFiles/run_all_tests.dir/src/driver.cpp.o
run_all_tests: CMakeFiles/run_all_tests.dir/src/tools.cpp.o
run_all_tests: CMakeFiles/run_all_tests.dir/build.make
run_all_tests: lib/libgtest_main.a
run_all_tests: lib/libgtest.a
run_all_tests: CMakeFiles/run_all_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/felix-klein/gaussian-free-fields-reu/simulations/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable run_all_tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/run_all_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/run_all_tests.dir/build: run_all_tests
.PHONY : CMakeFiles/run_all_tests.dir/build

CMakeFiles/run_all_tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/run_all_tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/run_all_tests.dir/clean

CMakeFiles/run_all_tests.dir/depend:
	cd /home/felix-klein/gaussian-free-fields-reu/simulations/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/felix-klein/gaussian-free-fields-reu/simulations /home/felix-klein/gaussian-free-fields-reu/simulations /home/felix-klein/gaussian-free-fields-reu/simulations/build /home/felix-klein/gaussian-free-fields-reu/simulations/build /home/felix-klein/gaussian-free-fields-reu/simulations/build/CMakeFiles/run_all_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/run_all_tests.dir/depend

