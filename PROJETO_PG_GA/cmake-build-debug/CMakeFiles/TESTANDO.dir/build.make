# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/gian/GitHub/PG_Trabalho_GA/PROJETO_PG_GA

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/gian/GitHub/PG_Trabalho_GA/PROJETO_PG_GA/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TESTANDO.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TESTANDO.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TESTANDO.dir/flags.make

CMakeFiles/TESTANDO.dir/source/main.cpp.o: CMakeFiles/TESTANDO.dir/flags.make
CMakeFiles/TESTANDO.dir/source/main.cpp.o: ../source/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gian/GitHub/PG_Trabalho_GA/PROJETO_PG_GA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TESTANDO.dir/source/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TESTANDO.dir/source/main.cpp.o -c /Users/gian/GitHub/PG_Trabalho_GA/PROJETO_PG_GA/source/main.cpp

CMakeFiles/TESTANDO.dir/source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TESTANDO.dir/source/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gian/GitHub/PG_Trabalho_GA/PROJETO_PG_GA/source/main.cpp > CMakeFiles/TESTANDO.dir/source/main.cpp.i

CMakeFiles/TESTANDO.dir/source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TESTANDO.dir/source/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gian/GitHub/PG_Trabalho_GA/PROJETO_PG_GA/source/main.cpp -o CMakeFiles/TESTANDO.dir/source/main.cpp.s

# Object files for target TESTANDO
TESTANDO_OBJECTS = \
"CMakeFiles/TESTANDO.dir/source/main.cpp.o"

# External object files for target TESTANDO
TESTANDO_EXTERNAL_OBJECTS =

TESTANDO: CMakeFiles/TESTANDO.dir/source/main.cpp.o
TESTANDO: CMakeFiles/TESTANDO.dir/build.make
TESTANDO: /usr/local/lib/libglfw.3.2.dylib
TESTANDO: /usr/local/lib/libGLEW.dylib
TESTANDO: CMakeFiles/TESTANDO.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/gian/GitHub/PG_Trabalho_GA/PROJETO_PG_GA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TESTANDO"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TESTANDO.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TESTANDO.dir/build: TESTANDO

.PHONY : CMakeFiles/TESTANDO.dir/build

CMakeFiles/TESTANDO.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TESTANDO.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TESTANDO.dir/clean

CMakeFiles/TESTANDO.dir/depend:
	cd /Users/gian/GitHub/PG_Trabalho_GA/PROJETO_PG_GA/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/gian/GitHub/PG_Trabalho_GA/PROJETO_PG_GA /Users/gian/GitHub/PG_Trabalho_GA/PROJETO_PG_GA /Users/gian/GitHub/PG_Trabalho_GA/PROJETO_PG_GA/cmake-build-debug /Users/gian/GitHub/PG_Trabalho_GA/PROJETO_PG_GA/cmake-build-debug /Users/gian/GitHub/PG_Trabalho_GA/PROJETO_PG_GA/cmake-build-debug/CMakeFiles/TESTANDO.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TESTANDO.dir/depend

