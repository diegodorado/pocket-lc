# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/diegodorado/Code/c/pocketLC/build/libsoundio-prefix/src/libsoundio

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/diegodorado/Code/c/pocketLC/build/libsoundio-prefix/src/libsoundio-build

# Include any dependencies generated for this target.
include CMakeFiles/underflow.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/underflow.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/underflow.dir/flags.make

CMakeFiles/underflow.dir/test/underflow.c.o: CMakeFiles/underflow.dir/flags.make
CMakeFiles/underflow.dir/test/underflow.c.o: /home/diegodorado/Code/c/pocketLC/build/libsoundio-prefix/src/libsoundio/test/underflow.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diegodorado/Code/c/pocketLC/build/libsoundio-prefix/src/libsoundio-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/underflow.dir/test/underflow.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/underflow.dir/test/underflow.c.o   -c /home/diegodorado/Code/c/pocketLC/build/libsoundio-prefix/src/libsoundio/test/underflow.c

CMakeFiles/underflow.dir/test/underflow.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/underflow.dir/test/underflow.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/diegodorado/Code/c/pocketLC/build/libsoundio-prefix/src/libsoundio/test/underflow.c > CMakeFiles/underflow.dir/test/underflow.c.i

CMakeFiles/underflow.dir/test/underflow.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/underflow.dir/test/underflow.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/diegodorado/Code/c/pocketLC/build/libsoundio-prefix/src/libsoundio/test/underflow.c -o CMakeFiles/underflow.dir/test/underflow.c.s

CMakeFiles/underflow.dir/test/underflow.c.o.requires:

.PHONY : CMakeFiles/underflow.dir/test/underflow.c.o.requires

CMakeFiles/underflow.dir/test/underflow.c.o.provides: CMakeFiles/underflow.dir/test/underflow.c.o.requires
	$(MAKE) -f CMakeFiles/underflow.dir/build.make CMakeFiles/underflow.dir/test/underflow.c.o.provides.build
.PHONY : CMakeFiles/underflow.dir/test/underflow.c.o.provides

CMakeFiles/underflow.dir/test/underflow.c.o.provides.build: CMakeFiles/underflow.dir/test/underflow.c.o


# Object files for target underflow
underflow_OBJECTS = \
"CMakeFiles/underflow.dir/test/underflow.c.o"

# External object files for target underflow
underflow_EXTERNAL_OBJECTS =

underflow: CMakeFiles/underflow.dir/test/underflow.c.o
underflow: CMakeFiles/underflow.dir/build.make
underflow: libsoundio.so.1.1.0
underflow: /usr/lib/x86_64-linux-gnu/libjack.so
underflow: /usr/lib/x86_64-linux-gnu/libpulse.so
underflow: /usr/lib/x86_64-linux-gnu/libasound.so
underflow: CMakeFiles/underflow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/diegodorado/Code/c/pocketLC/build/libsoundio-prefix/src/libsoundio-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable underflow"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/underflow.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/underflow.dir/build: underflow

.PHONY : CMakeFiles/underflow.dir/build

CMakeFiles/underflow.dir/requires: CMakeFiles/underflow.dir/test/underflow.c.o.requires

.PHONY : CMakeFiles/underflow.dir/requires

CMakeFiles/underflow.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/underflow.dir/cmake_clean.cmake
.PHONY : CMakeFiles/underflow.dir/clean

CMakeFiles/underflow.dir/depend:
	cd /home/diegodorado/Code/c/pocketLC/build/libsoundio-prefix/src/libsoundio-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/diegodorado/Code/c/pocketLC/build/libsoundio-prefix/src/libsoundio /home/diegodorado/Code/c/pocketLC/build/libsoundio-prefix/src/libsoundio /home/diegodorado/Code/c/pocketLC/build/libsoundio-prefix/src/libsoundio-build /home/diegodorado/Code/c/pocketLC/build/libsoundio-prefix/src/libsoundio-build /home/diegodorado/Code/c/pocketLC/build/libsoundio-prefix/src/libsoundio-build/CMakeFiles/underflow.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/underflow.dir/depend
