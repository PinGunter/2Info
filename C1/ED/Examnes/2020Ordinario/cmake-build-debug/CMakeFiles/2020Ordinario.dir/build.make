# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/salva/clion-2020.3.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/salva/clion-2020.3.1/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/salva/Uni/2Info/ED/Examnes/2020Ordinario

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/salva/Uni/2Info/ED/Examnes/2020Ordinario/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/2020Ordinario.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/2020Ordinario.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2020Ordinario.dir/flags.make

CMakeFiles/2020Ordinario.dir/main.cpp.o: CMakeFiles/2020Ordinario.dir/flags.make
CMakeFiles/2020Ordinario.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/salva/Uni/2Info/ED/Examnes/2020Ordinario/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/2020Ordinario.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/2020Ordinario.dir/main.cpp.o -c /home/salva/Uni/2Info/ED/Examnes/2020Ordinario/main.cpp

CMakeFiles/2020Ordinario.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2020Ordinario.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/salva/Uni/2Info/ED/Examnes/2020Ordinario/main.cpp > CMakeFiles/2020Ordinario.dir/main.cpp.i

CMakeFiles/2020Ordinario.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2020Ordinario.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/salva/Uni/2Info/ED/Examnes/2020Ordinario/main.cpp -o CMakeFiles/2020Ordinario.dir/main.cpp.s

# Object files for target 2020Ordinario
2020Ordinario_OBJECTS = \
"CMakeFiles/2020Ordinario.dir/main.cpp.o"

# External object files for target 2020Ordinario
2020Ordinario_EXTERNAL_OBJECTS =

2020Ordinario: CMakeFiles/2020Ordinario.dir/main.cpp.o
2020Ordinario: CMakeFiles/2020Ordinario.dir/build.make
2020Ordinario: CMakeFiles/2020Ordinario.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/salva/Uni/2Info/ED/Examnes/2020Ordinario/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 2020Ordinario"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2020Ordinario.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2020Ordinario.dir/build: 2020Ordinario

.PHONY : CMakeFiles/2020Ordinario.dir/build

CMakeFiles/2020Ordinario.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/2020Ordinario.dir/cmake_clean.cmake
.PHONY : CMakeFiles/2020Ordinario.dir/clean

CMakeFiles/2020Ordinario.dir/depend:
	cd /home/salva/Uni/2Info/ED/Examnes/2020Ordinario/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/salva/Uni/2Info/ED/Examnes/2020Ordinario /home/salva/Uni/2Info/ED/Examnes/2020Ordinario /home/salva/Uni/2Info/ED/Examnes/2020Ordinario/cmake-build-debug /home/salva/Uni/2Info/ED/Examnes/2020Ordinario/cmake-build-debug /home/salva/Uni/2Info/ED/Examnes/2020Ordinario/cmake-build-debug/CMakeFiles/2020Ordinario.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/2020Ordinario.dir/depend

