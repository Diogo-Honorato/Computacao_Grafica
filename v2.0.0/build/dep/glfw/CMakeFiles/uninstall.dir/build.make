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
CMAKE_SOURCE_DIR = /home/diogo/Documentos/projetos/Computacao_Grafica/v2.0.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/diogo/Documentos/projetos/Computacao_Grafica/v2.0.0/build

# Utility rule file for uninstall.

# Include any custom commands dependencies for this target.
include dep/glfw/CMakeFiles/uninstall.dir/compiler_depend.make

# Include the progress variables for this target.
include dep/glfw/CMakeFiles/uninstall.dir/progress.make

dep/glfw/CMakeFiles/uninstall:
	cd /home/diogo/Documentos/projetos/Computacao_Grafica/v2.0.0/build/dep/glfw && /usr/bin/cmake -P /home/diogo/Documentos/projetos/Computacao_Grafica/v2.0.0/build/dep/glfw/cmake_uninstall.cmake

uninstall: dep/glfw/CMakeFiles/uninstall
uninstall: dep/glfw/CMakeFiles/uninstall.dir/build.make
.PHONY : uninstall

# Rule to build all files generated by this target.
dep/glfw/CMakeFiles/uninstall.dir/build: uninstall
.PHONY : dep/glfw/CMakeFiles/uninstall.dir/build

dep/glfw/CMakeFiles/uninstall.dir/clean:
	cd /home/diogo/Documentos/projetos/Computacao_Grafica/v2.0.0/build/dep/glfw && $(CMAKE_COMMAND) -P CMakeFiles/uninstall.dir/cmake_clean.cmake
.PHONY : dep/glfw/CMakeFiles/uninstall.dir/clean

dep/glfw/CMakeFiles/uninstall.dir/depend:
	cd /home/diogo/Documentos/projetos/Computacao_Grafica/v2.0.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/diogo/Documentos/projetos/Computacao_Grafica/v2.0.0 /home/diogo/Documentos/projetos/Computacao_Grafica/v2.0.0/dep/glfw /home/diogo/Documentos/projetos/Computacao_Grafica/v2.0.0/build /home/diogo/Documentos/projetos/Computacao_Grafica/v2.0.0/build/dep/glfw /home/diogo/Documentos/projetos/Computacao_Grafica/v2.0.0/build/dep/glfw/CMakeFiles/uninstall.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : dep/glfw/CMakeFiles/uninstall.dir/depend

