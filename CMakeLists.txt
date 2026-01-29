cmake_minimum_required(VERSION 3.10)
project(graphics-demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW
find_package(glfw3 REQUIRED)

# Find GLEW
find_package(GLEW REQUIRED)

# Add include directories
include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

# Add source files
set(SOURCES
    src/main.cpp
    src/shader.cpp
    src/renderer.cpp
)

# Create executable
add_executable(graphics-demo ${SOURCES})

# Link libraries
target_link_libraries(graphics-demo
    ${OPENGL_LIBRARIES}
    glfw
    GLEW::GLEW
)

# Copy shaders to build directory
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})
