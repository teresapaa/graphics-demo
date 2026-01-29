cmake_minimum_required(VERSION 3.10)
project(GraphicsDemo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Add executable
add_executable(graphics_demo main.cpp)

# Link libraries
target_link_libraries(graphics_demo 
    OpenGL::GL
    GLEW::GLEW
    glfw
)

# Copy shaders to build directory
configure_file(vertex.glsl vertex.glsl COPYONLY)
configure_file(fragment.glsl fragment.glsl COPYONLY)
