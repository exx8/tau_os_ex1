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
CMAKE_COMMAND = /home/eran/softwares/clion-2019.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/eran/softwares/clion-2019.3.4/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/eran/CLionProjects/tau_os_ex1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/eran/CLionProjects/tau_os_ex1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/tau_os_ex1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tau_os_ex1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tau_os_ex1.dir/flags.make

CMakeFiles/tau_os_ex1.dir/os.c.o: CMakeFiles/tau_os_ex1.dir/flags.make
CMakeFiles/tau_os_ex1.dir/os.c.o: ../os.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eran/CLionProjects/tau_os_ex1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tau_os_ex1.dir/os.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tau_os_ex1.dir/os.c.o   -c /home/eran/CLionProjects/tau_os_ex1/os.c

CMakeFiles/tau_os_ex1.dir/os.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tau_os_ex1.dir/os.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/eran/CLionProjects/tau_os_ex1/os.c > CMakeFiles/tau_os_ex1.dir/os.c.i

CMakeFiles/tau_os_ex1.dir/os.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tau_os_ex1.dir/os.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/eran/CLionProjects/tau_os_ex1/os.c -o CMakeFiles/tau_os_ex1.dir/os.c.s

# Object files for target tau_os_ex1
tau_os_ex1_OBJECTS = \
"CMakeFiles/tau_os_ex1.dir/os.c.o"

# External object files for target tau_os_ex1
tau_os_ex1_EXTERNAL_OBJECTS =

tau_os_ex1: CMakeFiles/tau_os_ex1.dir/os.c.o
tau_os_ex1: CMakeFiles/tau_os_ex1.dir/build.make
tau_os_ex1: CMakeFiles/tau_os_ex1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/eran/CLionProjects/tau_os_ex1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable tau_os_ex1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tau_os_ex1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tau_os_ex1.dir/build: tau_os_ex1

.PHONY : CMakeFiles/tau_os_ex1.dir/build

CMakeFiles/tau_os_ex1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tau_os_ex1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tau_os_ex1.dir/clean

CMakeFiles/tau_os_ex1.dir/depend:
	cd /home/eran/CLionProjects/tau_os_ex1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/eran/CLionProjects/tau_os_ex1 /home/eran/CLionProjects/tau_os_ex1 /home/eran/CLionProjects/tau_os_ex1/cmake-build-debug /home/eran/CLionProjects/tau_os_ex1/cmake-build-debug /home/eran/CLionProjects/tau_os_ex1/cmake-build-debug/CMakeFiles/tau_os_ex1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tau_os_ex1.dir/depend

