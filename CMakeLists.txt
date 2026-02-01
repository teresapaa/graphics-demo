cmake_minimum_required(VERSION 3.10)
project(GraphicsDemo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenGL REQUIRED)

# --- GLFW (vendored) ---
# Disable extras to keep build fast and clean
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

# ---- GLAD (OpenGL loader) ----
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/shared_sources/glad/gl_core_33.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/shared_sources)

# Add executable
add_executable(graphics_demo main.cpp)

#making it explicit to avoid Visual Studio issues
target_include_directories(graphics_demo PRIVATE ${CMAKE_SOURCE_DIR}/shared_sources)

# Link libraries
target_link_libraries(graphics_demo 
    OpenGL::GL
    glad
    glfw
)

# Copy shaders to build directory
#configure_file(shaders/vertex.glsl vertex.glsl COPYONLY)
#configure_file(shaders/fragment.glsl fragment.glsl COPYONLY)

file(GLOB SHADER_FILES "${CMAKE_SOURCE_DIR}/shaders/*.glsl")

foreach(shader ${SHADER_FILES})
    add_custom_command(TARGET graphics_demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${shader}
        $<TARGET_FILE_DIR:graphics_demo>)
endforeach()