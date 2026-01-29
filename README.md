# graphics-demo
A small OpenGL/GLSL demo exploring real-time rendering quality vs performance trade-offs, motivated by constraints relevant to AR devices.

## Overview

This demo showcases different rendering quality levels to illustrate the trade-offs between visual fidelity and performance in real-time graphics, particularly relevant for AR (Augmented Reality) devices where both battery life and rendering quality matter.

The demo renders a 3D torus with three different shader implementations:

1. **High Quality Mode** - Full Blinn-Phong lighting with rim lighting and Fresnel effects
2. **Balanced Mode** - Standard Blinn-Phong shading (good for most AR devices)
3. **Performance Mode** - Simplified lighting optimized for maximum performance

## Features

- Real-time 3D rendering with OpenGL 3.3
- Three shader quality levels demonstrating different optimization strategies
- Live FPS counter to measure performance impact
- Interactive controls to switch between modes
- Example of AR-relevant rendering optimizations

## Building

### Prerequisites

- C++11 compatible compiler (GCC, Clang, MSVC)
- OpenGL 3.3 or higher
- GLFW3
- GLEW

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential cmake libglfw3-dev libglew-dev
```

#### macOS
```bash
brew install cmake glfw glew
```

#### Windows
Install via vcpkg or download libraries manually:
```bash
vcpkg install glfw3 glew
```

### Compilation

Using Make:
```bash
make
./graphics-demo
```

Using CMake:
```bash
mkdir build
cd build
cmake ..
make
./graphics-demo
```

## Controls

- **1** - Switch to Performance Mode (optimized for AR devices)
- **2** - Switch to Balanced Mode (good quality/performance trade-off)
- **3** - Switch to High Quality Mode (maximum visual quality)
- **S** - Toggle stats display
- **ESC** - Exit application

## Technical Details

### Rendering Modes Comparison

| Feature | Performance | Balanced | High Quality |
|---------|-------------|----------|--------------|
| Ambient Lighting | ✓ | ✓ | ✓ |
| Diffuse Lighting | Simplified | Full | Full |
| Specular Highlights | ✗ | ✓ | ✓ (Enhanced) |
| Rim Lighting | ✗ | ✗ | ✓ |
| Fresnel Effect | ✗ | ✗ | ✓ |
| Specular Shininess | - | 32 | 64 |
| GPU Cost | Low | Medium | High |

### Performance Considerations

The demo illustrates several optimization techniques relevant to AR:

1. **Shader Complexity**: Performance mode uses fewer calculations per fragment
2. **Lighting Model**: Simplified Lambert vs. full Blinn-Phong
3. **Visual Effects**: Trade-off between rim lighting/Fresnel and frame rate
4. **AR Device Constraints**: Mobile GPUs benefit greatly from reduced shader complexity

### Project Structure

```
graphics-demo/
├── CMakeLists.txt       # CMake build configuration
├── Makefile             # Simple make build configuration
├── README.md            # This file
├── include/
│   ├── shader.h         # Shader class header
│   └── renderer.h       # Renderer class header
├── src/
│   ├── main.cpp         # Application entry point
│   ├── shader.cpp       # Shader loading and compilation
│   └── renderer.cpp     # Main rendering logic
└── shaders/
    ├── vertex.glsl           # Vertex shader
    ├── fragment_hq.glsl      # High quality fragment shader
    ├── fragment_balanced.glsl # Balanced fragment shader
    └── fragment_perf.glsl    # Performance fragment shader
```

## License

MIT License - Feel free to use this demo for learning and portfolio purposes.
