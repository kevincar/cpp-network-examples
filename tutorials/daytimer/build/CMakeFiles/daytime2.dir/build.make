# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.18.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.18.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/kevindavis/Documents/Computer-Projects/C++-Projects/cpp-network-examples/tutorials/daytimer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kevindavis/Documents/Computer-Projects/C++-Projects/cpp-network-examples/tutorials/daytimer/build

# Include any dependencies generated for this target.
include CMakeFiles/daytime2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/daytime2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/daytime2.dir/flags.make

CMakeFiles/daytime2.dir/src/daytime2.cpp.o: CMakeFiles/daytime2.dir/flags.make
CMakeFiles/daytime2.dir/src/daytime2.cpp.o: ../src/daytime2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kevindavis/Documents/Computer-Projects/C++-Projects/cpp-network-examples/tutorials/daytimer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/daytime2.dir/src/daytime2.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/daytime2.dir/src/daytime2.cpp.o -c /Users/kevindavis/Documents/Computer-Projects/C++-Projects/cpp-network-examples/tutorials/daytimer/src/daytime2.cpp

CMakeFiles/daytime2.dir/src/daytime2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/daytime2.dir/src/daytime2.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kevindavis/Documents/Computer-Projects/C++-Projects/cpp-network-examples/tutorials/daytimer/src/daytime2.cpp > CMakeFiles/daytime2.dir/src/daytime2.cpp.i

CMakeFiles/daytime2.dir/src/daytime2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/daytime2.dir/src/daytime2.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kevindavis/Documents/Computer-Projects/C++-Projects/cpp-network-examples/tutorials/daytimer/src/daytime2.cpp -o CMakeFiles/daytime2.dir/src/daytime2.cpp.s

# Object files for target daytime2
daytime2_OBJECTS = \
"CMakeFiles/daytime2.dir/src/daytime2.cpp.o"

# External object files for target daytime2
daytime2_EXTERNAL_OBJECTS =

daytime2: CMakeFiles/daytime2.dir/src/daytime2.cpp.o
daytime2: CMakeFiles/daytime2.dir/build.make
daytime2: CMakeFiles/daytime2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kevindavis/Documents/Computer-Projects/C++-Projects/cpp-network-examples/tutorials/daytimer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable daytime2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/daytime2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/daytime2.dir/build: daytime2

.PHONY : CMakeFiles/daytime2.dir/build

CMakeFiles/daytime2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/daytime2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/daytime2.dir/clean

CMakeFiles/daytime2.dir/depend:
	cd /Users/kevindavis/Documents/Computer-Projects/C++-Projects/cpp-network-examples/tutorials/daytimer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kevindavis/Documents/Computer-Projects/C++-Projects/cpp-network-examples/tutorials/daytimer /Users/kevindavis/Documents/Computer-Projects/C++-Projects/cpp-network-examples/tutorials/daytimer /Users/kevindavis/Documents/Computer-Projects/C++-Projects/cpp-network-examples/tutorials/daytimer/build /Users/kevindavis/Documents/Computer-Projects/C++-Projects/cpp-network-examples/tutorials/daytimer/build /Users/kevindavis/Documents/Computer-Projects/C++-Projects/cpp-network-examples/tutorials/daytimer/build/CMakeFiles/daytime2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/daytime2.dir/depend
