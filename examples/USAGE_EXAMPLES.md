# Example Usage Scenarios

This file demonstrates various ways to use and extend the AR Graphics Demo.

## Basic Usage

### Running the Demo

```bash
# Build the project
make

# Run the demo
./graphics-demo
```

### Keyboard Controls

```
Key '1': Switch to Performance Mode
Key '2': Switch to Balanced Mode  
Key '3': Switch to High Quality Mode
Key 'S': Toggle stats display on/off
Key 'ESC': Exit application
```

## Code Integration Examples

### Example 1: Using the Shader Class

```cpp
#include "shader.h"

// Load and compile shaders
Shader myShader("shaders/vertex.glsl", "shaders/fragment_hq.glsl");

// Use the shader
myShader.use();

// Set uniforms
myShader.setVec3("lightPos", 2.0f, 2.0f, 2.0f);
myShader.setFloat("specularStrength", 0.8f);
myShader.setInt("shininess", 64);

// Render your geometry
// ...
```

### Example 2: Creating Custom Rendering Modes

To add a new rendering mode:

1. **Create a new fragment shader** (e.g., `shaders/fragment_ultra.glsl`):

```glsl
#version 330 core

out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;

void main()
{
    // Your custom lighting calculations here
    vec3 result = objectColor;
    FragColor = vec4(result, 1.0);
}
```

2. **Add the mode to the enum** in `renderer.h`:

```cpp
enum RenderMode {
    HIGH_QUALITY,
    BALANCED,
    PERFORMANCE,
    ULTRA_QUALITY  // New mode
};
```

3. **Update the render function** in `renderer.cpp`:

```cpp
switch (currentMode) {
    case ULTRA_QUALITY:
        fragmentShader = "shaders/fragment_ultra.glsl";
        shader.setInt("qualityLevel", 4);
        // Set other parameters
        break;
    // ... other cases
}
```

4. **Add key binding** in `keyCallback`:

```cpp
case GLFW_KEY_4:
    renderer->currentMode = ULTRA_QUALITY;
    std::cout << "Switched to ULTRA_QUALITY mode" << std::endl;
    break;
```

### Example 3: Modifying Geometry

To change the torus parameters in `setupGeometry()`:

```cpp
// More detailed torus
const int segments = 64;  // Increased from 32
const int rings = 32;     // Increased from 16

// Larger torus
const float majorRadius = 0.8f;  // Increased from 0.6f
const float minorRadius = 0.3f;  // Increased from 0.2f
```

### Example 4: Adding Multiple Objects

```cpp
// In renderer.h, add:
GLuint VAO2, VBO2, EBO2;

// In setupGeometry(), create second object:
setupTorus(&VAO, &VBO, &EBO, 0.6f, 0.2f);
setupSphere(&VAO2, &VBO2, &EBO2, 0.5f);

// In render(), draw multiple objects:
// Draw first torus
mat4_rotate_y(model, rotation);
shader.setMat4("model", model);
glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, torusIndices, GL_UNSIGNED_INT, 0);

// Draw second object
mat4_translate(model, 1.5f, 0.0f, 0.0f);
shader.setMat4("model", model);
glBindVertexArray(VAO2);
glDrawElements(GL_TRIANGLES, sphereIndices, GL_UNSIGNED_INT, 0);
```

### Example 5: Adding Texture Support

1. **Load a texture**:

```cpp
#include <stb_image.h>  // Add to dependencies

GLuint loadTexture(const char* path) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, 
                     GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    return textureID;
}
```

2. **Update vertex shader** to include texture coordinates:

```glsl
layout (location = 2) in vec2 aTexCoord;
out vec2 TexCoord;

void main() {
    TexCoord = aTexCoord;
    // ... rest of shader
}
```

3. **Update fragment shader** to sample texture:

```glsl
in vec2 TexCoord;
uniform sampler2D texture1;

void main() {
    vec3 texColor = texture(texture1, TexCoord).rgb;
    // Mix with lighting calculations
}
```

## AR Integration Examples

### Example 6: AR Camera Integration

To integrate with ARCore or ARKit:

```cpp
// Set projection matrix from AR SDK
float arProjection[16];
arSession->getProjectionMatrix(arProjection);
shader.setMat4("projection", arProjection);

// Set view matrix from AR camera
float arView[16];
arSession->getViewMatrix(arView);
shader.setMat4("view", arView);

// Place object at AR anchor position
float anchorTransform[16];
arAnchor->getTransform(anchorTransform);
shader.setMat4("model", anchorTransform);
```

### Example 7: Performance Monitoring

```cpp
// Add to Renderer class:
void logPerformanceMetrics() {
    std::cout << "Frame Time: " << frameTime << "ms" << std::endl;
    std::cout << "FPS: " << fps << std::endl;
    std::cout << "GPU Memory: " << getGPUMemoryUsage() << "MB" << std::endl;
}

// Call every N frames:
if (frameCount % 100 == 0) {
    logPerformanceMetrics();
}
```

## Build System Examples

### Using CMake with Custom Options

```bash
# Build with optimizations
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make

# Build with debug symbols
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### Cross-compilation for ARM

```bash
# For ARM devices (e.g., Raspberry Pi)
cmake -DCMAKE_TOOLCHAIN_FILE=arm-toolchain.cmake ..
make
```

## Testing Performance

### Benchmarking Script

```bash
#!/bin/bash
# Save as benchmark.sh

echo "Running performance benchmark..."
for mode in 1 2 3; do
    echo "Testing mode $mode"
    # Run for 10 seconds per mode
    timeout 10 ./graphics-demo --mode=$mode --benchmark
done
```

## Troubleshooting

### Common Issues

1. **Black screen**: Check if shaders compiled correctly
2. **Low FPS**: Try Performance mode or check GPU drivers
3. **Build errors**: Ensure all dependencies are installed

```bash
# Check OpenGL support
glxinfo | grep "OpenGL version"

# Check library versions
pkg-config --modversion glfw3 glew
```
