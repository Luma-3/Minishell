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
CMAKE_SOURCE_DIR = /home/jbrousse/Downloads/check-0.15.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jbrousse/Downloads/check-0.15.2/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/check_nofork.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/check_nofork.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/check_nofork.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/check_nofork.dir/flags.make

tests/CMakeFiles/check_nofork.dir/check_nofork.c.o: tests/CMakeFiles/check_nofork.dir/flags.make
tests/CMakeFiles/check_nofork.dir/check_nofork.c.o: ../tests/check_nofork.c
tests/CMakeFiles/check_nofork.dir/check_nofork.c.o: tests/CMakeFiles/check_nofork.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jbrousse/Downloads/check-0.15.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/check_nofork.dir/check_nofork.c.o"
	cd /home/jbrousse/Downloads/check-0.15.2/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/check_nofork.dir/check_nofork.c.o -MF CMakeFiles/check_nofork.dir/check_nofork.c.o.d -o CMakeFiles/check_nofork.dir/check_nofork.c.o -c /home/jbrousse/Downloads/check-0.15.2/tests/check_nofork.c

tests/CMakeFiles/check_nofork.dir/check_nofork.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/check_nofork.dir/check_nofork.c.i"
	cd /home/jbrousse/Downloads/check-0.15.2/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jbrousse/Downloads/check-0.15.2/tests/check_nofork.c > CMakeFiles/check_nofork.dir/check_nofork.c.i

tests/CMakeFiles/check_nofork.dir/check_nofork.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/check_nofork.dir/check_nofork.c.s"
	cd /home/jbrousse/Downloads/check-0.15.2/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jbrousse/Downloads/check-0.15.2/tests/check_nofork.c -o CMakeFiles/check_nofork.dir/check_nofork.c.s

# Object files for target check_nofork
check_nofork_OBJECTS = \
"CMakeFiles/check_nofork.dir/check_nofork.c.o"

# External object files for target check_nofork
check_nofork_EXTERNAL_OBJECTS =

tests/check_nofork: tests/CMakeFiles/check_nofork.dir/check_nofork.c.o
tests/check_nofork: tests/CMakeFiles/check_nofork.dir/build.make
tests/check_nofork: src/libcheck.a
tests/check_nofork: tests/CMakeFiles/check_nofork.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jbrousse/Downloads/check-0.15.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable check_nofork"
	cd /home/jbrousse/Downloads/check-0.15.2/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/check_nofork.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/check_nofork.dir/build: tests/check_nofork
.PHONY : tests/CMakeFiles/check_nofork.dir/build

tests/CMakeFiles/check_nofork.dir/clean:
	cd /home/jbrousse/Downloads/check-0.15.2/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/check_nofork.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/check_nofork.dir/clean

tests/CMakeFiles/check_nofork.dir/depend:
	cd /home/jbrousse/Downloads/check-0.15.2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jbrousse/Downloads/check-0.15.2 /home/jbrousse/Downloads/check-0.15.2/tests /home/jbrousse/Downloads/check-0.15.2/build /home/jbrousse/Downloads/check-0.15.2/build/tests /home/jbrousse/Downloads/check-0.15.2/build/tests/CMakeFiles/check_nofork.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/check_nofork.dir/depend

