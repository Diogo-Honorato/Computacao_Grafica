cmake_minimum_required(VERSION 3.0.0)
project(engine VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#GLAD
add_library(glad STATIC dep/glad/src/glad.c)
target_include_directories(glad PUBLIC dep/glad/include)

#GLFW
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
add_subdirectory(dep/glfw)

#SOURCES
file(GLOB SOURCES "source/*.cpp")

#Executable
add_executable(engine ${SOURCES})

#INCLUDES
target_include_directories(
    engine PRIVATE  
    include 
    dep/glad/include 
    dep/glfw/include
    dep/glm
)

#LINK
target_link_libraries(engine PRIVATE glad glfw)

