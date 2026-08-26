cmake_minimum_required(VERSION 3.10.0)
project(engine VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#GLAD
add_library(glad STATIC dep/glad/src/glad.c)
target_include_directories(glad PUBLIC dep/glad/include)

#GLFW
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
add_subdirectory(dep/glfw)

#IMGUI
set(IMGUI_DIR dep/imgui)
add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    dep/glfw/include
)
target_link_libraries(imgui PUBLIC glfw)

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
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

#LINK
target_link_libraries(engine PRIVATE glad glfw imgui)