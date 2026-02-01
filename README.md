# graphics-demo
A small OpenGL/GLSL demo exploring real-time rendering quality vs performance trade-offs.


#Build instructions
This project is self-contained and uses vendored dependencies (GLFW and GLAD). Recommended to clone with submodules (git clone --recurse-submodules <repo-url>).

Build: cmake -S . -B build && cmake --build build
Run: ./build/graphics-demo
