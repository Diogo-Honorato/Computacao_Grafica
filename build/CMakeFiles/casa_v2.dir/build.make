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
CMAKE_SOURCE_DIR = /home/diogo/Documentos/uni/CG/Computacao_Grafica

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/diogo/Documentos/uni/CG/Computacao_Grafica/build

# Include any dependencies generated for this target.
include CMakeFiles/casa_v2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/casa_v2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/casa_v2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/casa_v2.dir/flags.make

CMakeFiles/casa_v2.dir/source/Circle.cpp.o: CMakeFiles/casa_v2.dir/flags.make
CMakeFiles/casa_v2.dir/source/Circle.cpp.o: ../source/Circle.cpp
CMakeFiles/casa_v2.dir/source/Circle.cpp.o: CMakeFiles/casa_v2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diogo/Documentos/uni/CG/Computacao_Grafica/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/casa_v2.dir/source/Circle.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/casa_v2.dir/source/Circle.cpp.o -MF CMakeFiles/casa_v2.dir/source/Circle.cpp.o.d -o CMakeFiles/casa_v2.dir/source/Circle.cpp.o -c /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/Circle.cpp

CMakeFiles/casa_v2.dir/source/Circle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/casa_v2.dir/source/Circle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/Circle.cpp > CMakeFiles/casa_v2.dir/source/Circle.cpp.i

CMakeFiles/casa_v2.dir/source/Circle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/casa_v2.dir/source/Circle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/Circle.cpp -o CMakeFiles/casa_v2.dir/source/Circle.cpp.s

CMakeFiles/casa_v2.dir/source/EBO.cpp.o: CMakeFiles/casa_v2.dir/flags.make
CMakeFiles/casa_v2.dir/source/EBO.cpp.o: ../source/EBO.cpp
CMakeFiles/casa_v2.dir/source/EBO.cpp.o: CMakeFiles/casa_v2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diogo/Documentos/uni/CG/Computacao_Grafica/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/casa_v2.dir/source/EBO.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/casa_v2.dir/source/EBO.cpp.o -MF CMakeFiles/casa_v2.dir/source/EBO.cpp.o.d -o CMakeFiles/casa_v2.dir/source/EBO.cpp.o -c /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/EBO.cpp

CMakeFiles/casa_v2.dir/source/EBO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/casa_v2.dir/source/EBO.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/EBO.cpp > CMakeFiles/casa_v2.dir/source/EBO.cpp.i

CMakeFiles/casa_v2.dir/source/EBO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/casa_v2.dir/source/EBO.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/EBO.cpp -o CMakeFiles/casa_v2.dir/source/EBO.cpp.s

CMakeFiles/casa_v2.dir/source/Shader.cpp.o: CMakeFiles/casa_v2.dir/flags.make
CMakeFiles/casa_v2.dir/source/Shader.cpp.o: ../source/Shader.cpp
CMakeFiles/casa_v2.dir/source/Shader.cpp.o: CMakeFiles/casa_v2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diogo/Documentos/uni/CG/Computacao_Grafica/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/casa_v2.dir/source/Shader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/casa_v2.dir/source/Shader.cpp.o -MF CMakeFiles/casa_v2.dir/source/Shader.cpp.o.d -o CMakeFiles/casa_v2.dir/source/Shader.cpp.o -c /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/Shader.cpp

CMakeFiles/casa_v2.dir/source/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/casa_v2.dir/source/Shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/Shader.cpp > CMakeFiles/casa_v2.dir/source/Shader.cpp.i

CMakeFiles/casa_v2.dir/source/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/casa_v2.dir/source/Shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/Shader.cpp -o CMakeFiles/casa_v2.dir/source/Shader.cpp.s

CMakeFiles/casa_v2.dir/source/Square.cpp.o: CMakeFiles/casa_v2.dir/flags.make
CMakeFiles/casa_v2.dir/source/Square.cpp.o: ../source/Square.cpp
CMakeFiles/casa_v2.dir/source/Square.cpp.o: CMakeFiles/casa_v2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diogo/Documentos/uni/CG/Computacao_Grafica/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/casa_v2.dir/source/Square.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/casa_v2.dir/source/Square.cpp.o -MF CMakeFiles/casa_v2.dir/source/Square.cpp.o.d -o CMakeFiles/casa_v2.dir/source/Square.cpp.o -c /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/Square.cpp

CMakeFiles/casa_v2.dir/source/Square.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/casa_v2.dir/source/Square.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/Square.cpp > CMakeFiles/casa_v2.dir/source/Square.cpp.i

CMakeFiles/casa_v2.dir/source/Square.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/casa_v2.dir/source/Square.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/Square.cpp -o CMakeFiles/casa_v2.dir/source/Square.cpp.s

CMakeFiles/casa_v2.dir/source/Triangle.cpp.o: CMakeFiles/casa_v2.dir/flags.make
CMakeFiles/casa_v2.dir/source/Triangle.cpp.o: ../source/Triangle.cpp
CMakeFiles/casa_v2.dir/source/Triangle.cpp.o: CMakeFiles/casa_v2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diogo/Documentos/uni/CG/Computacao_Grafica/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/casa_v2.dir/source/Triangle.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/casa_v2.dir/source/Triangle.cpp.o -MF CMakeFiles/casa_v2.dir/source/Triangle.cpp.o.d -o CMakeFiles/casa_v2.dir/source/Triangle.cpp.o -c /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/Triangle.cpp

CMakeFiles/casa_v2.dir/source/Triangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/casa_v2.dir/source/Triangle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/Triangle.cpp > CMakeFiles/casa_v2.dir/source/Triangle.cpp.i

CMakeFiles/casa_v2.dir/source/Triangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/casa_v2.dir/source/Triangle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/Triangle.cpp -o CMakeFiles/casa_v2.dir/source/Triangle.cpp.s

CMakeFiles/casa_v2.dir/source/VAO.cpp.o: CMakeFiles/casa_v2.dir/flags.make
CMakeFiles/casa_v2.dir/source/VAO.cpp.o: ../source/VAO.cpp
CMakeFiles/casa_v2.dir/source/VAO.cpp.o: CMakeFiles/casa_v2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diogo/Documentos/uni/CG/Computacao_Grafica/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/casa_v2.dir/source/VAO.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/casa_v2.dir/source/VAO.cpp.o -MF CMakeFiles/casa_v2.dir/source/VAO.cpp.o.d -o CMakeFiles/casa_v2.dir/source/VAO.cpp.o -c /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/VAO.cpp

CMakeFiles/casa_v2.dir/source/VAO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/casa_v2.dir/source/VAO.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/VAO.cpp > CMakeFiles/casa_v2.dir/source/VAO.cpp.i

CMakeFiles/casa_v2.dir/source/VAO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/casa_v2.dir/source/VAO.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/VAO.cpp -o CMakeFiles/casa_v2.dir/source/VAO.cpp.s

CMakeFiles/casa_v2.dir/source/VBO.cpp.o: CMakeFiles/casa_v2.dir/flags.make
CMakeFiles/casa_v2.dir/source/VBO.cpp.o: ../source/VBO.cpp
CMakeFiles/casa_v2.dir/source/VBO.cpp.o: CMakeFiles/casa_v2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diogo/Documentos/uni/CG/Computacao_Grafica/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/casa_v2.dir/source/VBO.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/casa_v2.dir/source/VBO.cpp.o -MF CMakeFiles/casa_v2.dir/source/VBO.cpp.o.d -o CMakeFiles/casa_v2.dir/source/VBO.cpp.o -c /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/VBO.cpp

CMakeFiles/casa_v2.dir/source/VBO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/casa_v2.dir/source/VBO.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/VBO.cpp > CMakeFiles/casa_v2.dir/source/VBO.cpp.i

CMakeFiles/casa_v2.dir/source/VBO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/casa_v2.dir/source/VBO.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/VBO.cpp -o CMakeFiles/casa_v2.dir/source/VBO.cpp.s

CMakeFiles/casa_v2.dir/source/Window.cpp.o: CMakeFiles/casa_v2.dir/flags.make
CMakeFiles/casa_v2.dir/source/Window.cpp.o: ../source/Window.cpp
CMakeFiles/casa_v2.dir/source/Window.cpp.o: CMakeFiles/casa_v2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diogo/Documentos/uni/CG/Computacao_Grafica/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/casa_v2.dir/source/Window.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/casa_v2.dir/source/Window.cpp.o -MF CMakeFiles/casa_v2.dir/source/Window.cpp.o.d -o CMakeFiles/casa_v2.dir/source/Window.cpp.o -c /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/Window.cpp

CMakeFiles/casa_v2.dir/source/Window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/casa_v2.dir/source/Window.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/Window.cpp > CMakeFiles/casa_v2.dir/source/Window.cpp.i

CMakeFiles/casa_v2.dir/source/Window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/casa_v2.dir/source/Window.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/Window.cpp -o CMakeFiles/casa_v2.dir/source/Window.cpp.s

CMakeFiles/casa_v2.dir/source/main.cpp.o: CMakeFiles/casa_v2.dir/flags.make
CMakeFiles/casa_v2.dir/source/main.cpp.o: ../source/main.cpp
CMakeFiles/casa_v2.dir/source/main.cpp.o: CMakeFiles/casa_v2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diogo/Documentos/uni/CG/Computacao_Grafica/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/casa_v2.dir/source/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/casa_v2.dir/source/main.cpp.o -MF CMakeFiles/casa_v2.dir/source/main.cpp.o.d -o CMakeFiles/casa_v2.dir/source/main.cpp.o -c /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/main.cpp

CMakeFiles/casa_v2.dir/source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/casa_v2.dir/source/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/main.cpp > CMakeFiles/casa_v2.dir/source/main.cpp.i

CMakeFiles/casa_v2.dir/source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/casa_v2.dir/source/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diogo/Documentos/uni/CG/Computacao_Grafica/source/main.cpp -o CMakeFiles/casa_v2.dir/source/main.cpp.s

# Object files for target casa_v2
casa_v2_OBJECTS = \
"CMakeFiles/casa_v2.dir/source/Circle.cpp.o" \
"CMakeFiles/casa_v2.dir/source/EBO.cpp.o" \
"CMakeFiles/casa_v2.dir/source/Shader.cpp.o" \
"CMakeFiles/casa_v2.dir/source/Square.cpp.o" \
"CMakeFiles/casa_v2.dir/source/Triangle.cpp.o" \
"CMakeFiles/casa_v2.dir/source/VAO.cpp.o" \
"CMakeFiles/casa_v2.dir/source/VBO.cpp.o" \
"CMakeFiles/casa_v2.dir/source/Window.cpp.o" \
"CMakeFiles/casa_v2.dir/source/main.cpp.o"

# External object files for target casa_v2
casa_v2_EXTERNAL_OBJECTS =

casa_v2: CMakeFiles/casa_v2.dir/source/Circle.cpp.o
casa_v2: CMakeFiles/casa_v2.dir/source/EBO.cpp.o
casa_v2: CMakeFiles/casa_v2.dir/source/Shader.cpp.o
casa_v2: CMakeFiles/casa_v2.dir/source/Square.cpp.o
casa_v2: CMakeFiles/casa_v2.dir/source/Triangle.cpp.o
casa_v2: CMakeFiles/casa_v2.dir/source/VAO.cpp.o
casa_v2: CMakeFiles/casa_v2.dir/source/VBO.cpp.o
casa_v2: CMakeFiles/casa_v2.dir/source/Window.cpp.o
casa_v2: CMakeFiles/casa_v2.dir/source/main.cpp.o
casa_v2: CMakeFiles/casa_v2.dir/build.make
casa_v2: libglad.a
casa_v2: dep/glfw/src/libglfw3.a
casa_v2: /usr/lib/x86_64-linux-gnu/librt.a
casa_v2: /usr/lib/x86_64-linux-gnu/libm.so
casa_v2: CMakeFiles/casa_v2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/diogo/Documentos/uni/CG/Computacao_Grafica/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable casa_v2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/casa_v2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/casa_v2.dir/build: casa_v2
.PHONY : CMakeFiles/casa_v2.dir/build

CMakeFiles/casa_v2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/casa_v2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/casa_v2.dir/clean

CMakeFiles/casa_v2.dir/depend:
	cd /home/diogo/Documentos/uni/CG/Computacao_Grafica/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/diogo/Documentos/uni/CG/Computacao_Grafica /home/diogo/Documentos/uni/CG/Computacao_Grafica /home/diogo/Documentos/uni/CG/Computacao_Grafica/build /home/diogo/Documentos/uni/CG/Computacao_Grafica/build /home/diogo/Documentos/uni/CG/Computacao_Grafica/build/CMakeFiles/casa_v2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/casa_v2.dir/depend

