cmake_minimum_required(VERSION 3.0.0)
project(casa_v2 VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#GLAD
add_library(glad STATIC dep/glad/src/glad.c)
target_include_directories(glad PUBLIC dep/glad/include)

#GLFW
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
add_subdirectory(dep/glfw)

file(GLOB SOURCES "source/*.cpp")

#Executable
add_executable(casa_v2 ${SOURCES})

#Link
target_include_directories(casa_v2 PRIVATE  include dep/glad/include dep/glfw/include)
target_link_libraries(casa_v2 PRIVATE glad glfw)

