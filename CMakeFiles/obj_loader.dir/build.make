# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\matts\Desktop\OGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\matts\Desktop\OGL

# Include any dependencies generated for this target.
include CMakeFiles/obj_loader.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/obj_loader.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/obj_loader.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/obj_loader.dir/flags.make

CMakeFiles/obj_loader.dir/codegen:
.PHONY : CMakeFiles/obj_loader.dir/codegen

CMakeFiles/obj_loader.dir/src/main.cpp.obj: CMakeFiles/obj_loader.dir/flags.make
CMakeFiles/obj_loader.dir/src/main.cpp.obj: src/main.cpp
CMakeFiles/obj_loader.dir/src/main.cpp.obj: CMakeFiles/obj_loader.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\matts\Desktop\OGL\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/obj_loader.dir/src/main.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/obj_loader.dir/src/main.cpp.obj -MF CMakeFiles\obj_loader.dir\src\main.cpp.obj.d -o CMakeFiles\obj_loader.dir\src\main.cpp.obj -c C:\Users\matts\Desktop\OGL\src\main.cpp

CMakeFiles/obj_loader.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/obj_loader.dir/src/main.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\matts\Desktop\OGL\src\main.cpp > CMakeFiles\obj_loader.dir\src\main.cpp.i

CMakeFiles/obj_loader.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/obj_loader.dir/src/main.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\matts\Desktop\OGL\src\main.cpp -o CMakeFiles\obj_loader.dir\src\main.cpp.s

# Object files for target obj_loader
obj_loader_OBJECTS = \
"CMakeFiles/obj_loader.dir/src/main.cpp.obj"

# External object files for target obj_loader
obj_loader_EXTERNAL_OBJECTS =

bin/obj_loader.exe: CMakeFiles/obj_loader.dir/src/main.cpp.obj
bin/obj_loader.exe: CMakeFiles/obj_loader.dir/build.make
bin/obj_loader.exe: CMakeFiles/obj_loader.dir/linkLibs.rsp
bin/obj_loader.exe: CMakeFiles/obj_loader.dir/objects1.rsp
bin/obj_loader.exe: CMakeFiles/obj_loader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\matts\Desktop\OGL\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin\obj_loader.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\obj_loader.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/obj_loader.dir/build: bin/obj_loader.exe
.PHONY : CMakeFiles/obj_loader.dir/build

CMakeFiles/obj_loader.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\obj_loader.dir\cmake_clean.cmake
.PHONY : CMakeFiles/obj_loader.dir/clean

CMakeFiles/obj_loader.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\matts\Desktop\OGL C:\Users\matts\Desktop\OGL C:\Users\matts\Desktop\OGL C:\Users\matts\Desktop\OGL C:\Users\matts\Desktop\OGL\CMakeFiles\obj_loader.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/obj_loader.dir/depend

