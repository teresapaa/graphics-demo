# Graphics Demo

<div align="center">

![OpenGL](https://img.shields.io/badge/OpenGL-3.3-5586A4.svg)
![C](https://img.shields.io/badge/C%2B%2B-11-00599C.svg)
![CMake](https://img.shields.io/badge/CMake-3.10+-064F8C.svg)
![Status](https://img.shields.io/badge/Status-Early%20Development-yellow.svg)

**A small OpenGL/GLSL demo exploring real-time rendering quality vs performance trade-offs.**

</div>

---

## 📋 Overview

This project is a lightweight OpenGL graphics demo built to explore the relationship between rendering quality and performance in real-time applications. It serves as a testbed for experimenting with shader techniques, rendering optimizations, and performance profiling.

### 🎯 Goals

- **Benchmark rendering performance** using FPS measurements and profiling
- **Explore shader optimization techniques** for mobile/AR constraints
- **Compare quality vs. performance trade-offs** with different rendering approaches
- **Build a modular foundation** for future graphics experiments

---

## ✨ Current Features

- ✅ **OpenGL 3.3 Core Profile** rendering pipeline
- ✅ **GLSL shader support** with hot-reloadable vertex and fragment shaders
- ✅ **Real-time FPS counter** (VSync disabled for max performance testing)
- ✅ **Self-contained build system** with vendored dependencies (GLFW, GLAD)
- ✅ **CMake-based** cross-platform build configuration

---

## 🛠️ Tech Stack

| Component | Technology |
|-----------|------------|
| **Graphics API** | OpenGL 3.3 Core |
| **Shading Language** | GLSL 330 |
| **Windowing/Input** | GLFW 3.x |
| **OpenGL Loader** | GLAD (gl_core_33) |
| **Build System** | CMake 3.10+ |
| **Language** | C++11 |

---

## 🚀 Getting Started

### Prerequisites

- **CMake** 3.10 or higher
- **C++11 compatible compiler** (GCC, Clang, MSVC)
- **OpenGL 3.3 capable GPU**

All other dependencies (GLFW, GLAD) are vendored and included in the repository.

### Build Instructions

**1. Clone with submodules:**
```bash
git clone --recurse-submodules https://github.com/teresapaa/graphics-demo.git
cd graphics-demo
```

**2. Configure and build:**
```bash
cmake -S . -B build
cmake --build build
```

**3. Run:**
```bash
# On Linux/macOS
./build/graphics_demo

# On Windows
.\build\Debug\graphics_demo.exe
```

---

## 📂 Project Structure

```
graphics-demo/
├── main.cpp                  # Main application and rendering loop
├── shaders/
│   ├── vertex.glsl           # Vertex shader (basic passthrough)
│   └── fragment.glsl         # Fragment shader (solid color output)
├── shared_sources/
│   └── glad/                 # OpenGL loader (GLAD)
├── external/
│   └── glfw/                 # GLFW windowing library (submodule)
├── CMakeLists.txt            # Build configuration
└── README.md
```

---

## 🎨 Current Rendering

The demo currently renders:
- A **simple colored triangle** (lavender: `rgb(0.914, 0.816, 1.0)`)
- **Dark gray background** (`rgb(0.1, 0.1, 0.1)`)
- **Real-time FPS display** in the window title

**Why a triangle?**  
The classic "hello world" of graphics programming—simple enough to validate the pipeline, yet foundational for all complex geometry.

---

## 🔧 Shader Development

Shaders are located in the `shaders/` directory and automatically copied to the build directory at compile time.

### Vertex Shader (`shaders/vertex.glsl`)
```glsl
#version 330 core
layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
```

### Fragment Shader (`shaders/fragment.glsl`)
```glsl
#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(0.914, 0.816, 1.0, 1.0); // Lavender
}
```

**To modify shaders:**
1. Edit `.glsl` files in the `shaders/` directory
2. Rebuild the project (`cmake --build build`)
3. Shaders are automatically copied to the executable directory

---

## 📊 Performance Testing

The demo includes FPS measurement with VSync disabled to measure raw GPU performance:

```cpp
glfwSwapInterval(0);  // 0 = VSync off, 1 = VSync on
```

**FPS is displayed in the window title** and updates every second.

**Why disable VSync?**  
VSync locks the frame rate to the monitor's refresh rate (typically 60 Hz), which prevents measuring the GPU's true maximum throughput.

---

## 🚧 Planned Features

This project is in early development. Planned extensions include:

### 📌 Next Steps
- [ ] **Advanced shading** (Phong/PBR lighting models)
- [ ] **Texture mapping** and sampler management
- [ ] **Performance profiling tools** (GPU timers, frame time graphs)
- [ ] **Dynamic resolution scaling** for quality/performance trade-offs

### 🎯 AR/Mobile Optimizations
- [ ] **Level-of-detail (LOD)** switching based on FPS
- [ ] **Shader complexity variants** (high-quality vs. performance modes)
- [ ] **Draw call batching** and instancing
- [ ] **GPU profiling** (render pass timing)

### 🧪 Experimental Features
- [ ] **Custom post-processing effects** (bloom, DOF, chromatic aberration)
- [ ] **Deferred rendering** pipeline comparison
- [ ] **Compute shaders** for GPU-accelerated effects

---


---


<div align="center">

**⭐ Exploring real-time graphics one frame at a time**

</div>
