# Technical Documentation

## AR Graphics Quality vs Performance Trade-offs

This document provides technical details about the rendering optimizations implemented in this demo and their relevance to AR (Augmented Reality) devices.

## Performance Optimization Strategies

### 1. Performance Mode

**Target**: Low-end AR devices, extended battery life scenarios

**Optimizations**:
- **Simplified Lighting Model**: Uses basic Lambert diffuse only
- **Reduced Math Operations**: Skips expensive normalization when possible
- **No Specular Highlights**: Removes pow() calculations
- **Higher Ambient**: Compensates for reduced lighting complexity

**GLSL Details**:
```glsl
// No normalization of vectors (saves cycles)
vec3 lightDir = lightPos - FragPos;
float diff = max(dot(Normal, lightDir) * 0.1, 0.0);

// No specular component
// No Fresnel or rim lighting
```

**Expected Performance**: ~2-3x faster than High Quality mode on mobile GPUs

### 2. Balanced Mode

**Target**: Mid-range AR devices, general use

**Optimizations**:
- **Standard Blinn-Phong**: Industry-standard lighting
- **Moderate Specular**: Shininess = 32
- **No Extra Effects**: Removes rim lighting and Fresnel

**GLSL Details**:
```glsl
// Standard Blinn-Phong with halfway vector
vec3 halfwayDir = normalize(lightDir + viewDir);
float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
```

**Expected Performance**: ~1.5x faster than High Quality mode

### 3. High Quality Mode

**Target**: High-end AR devices, demos, screenshots

**Features**:
- **Full Blinn-Phong Lighting**: With high shininess (64)
- **Rim Lighting**: Edge enhancement for AR occlusion effects
- **Fresnel Effect**: View-dependent reflections
- **Higher Specular Strength**: More pronounced highlights

**GLSL Details**:
```glsl
// Blinn-Phong with high shininess
float spec = pow(max(dot(norm, halfwayDir), 0.0), 64.0);

// Rim lighting for AR-style edge enhancement
float rim = 1.0 - max(dot(viewDir, norm), 0.0);
rim = pow(rim, 3.0);
vec3 rimLight = rimStrength * rim * vec3(0.3, 0.5, 0.8);

// Fresnel effect
float fresnel = pow(1.0 - max(dot(viewDir, norm), 0.0), 2.0);
```

## AR Device Constraints

### Mobile GPU Considerations

1. **Fill Rate**: Mobile GPUs have lower fill rates than desktop GPUs
   - Solution: Reduce per-fragment calculations

2. **Power Consumption**: Battery-powered devices need efficiency
   - Solution: Simplified shaders reduce GPU utilization

3. **Thermal Throttling**: Sustained high GPU usage causes throttling
   - Solution: Performance mode maintains lower thermals

4. **Memory Bandwidth**: Mobile devices have limited bandwidth
   - Solution: Fewer texture fetches (none in this demo)

### Real-World AR Scenarios

1. **Outdoor Use**: High ambient light requires visible rendering
   - Performance mode maintains visibility with higher ambient

2. **Extended Sessions**: AR apps run for extended periods
   - Performance mode optimizes for battery life

3. **Multi-tasking**: AR often runs alongside other apps
   - Balanced mode provides good quality without monopolizing GPU

## Performance Metrics

### Approximate GPU Instruction Counts

| Mode | Fragment Shader Instructions | Relative Cost |
|------|------------------------------|---------------|
| Performance | ~15 | 1x |
| Balanced | ~25 | 1.7x |
| High Quality | ~40 | 2.7x |

### Mobile GPU Power Draw Estimates

| Mode | Relative Power | Battery Impact |
|------|----------------|----------------|
| Performance | 1x | Minimal |
| Balanced | 1.5x | Moderate |
| High Quality | 2.5x | Significant |

## Implementation Notes

### Shader Compilation

The demo loads different fragment shaders at runtime based on the selected mode. This demonstrates:

- Runtime shader switching (common in games)
- Quality settings implementation
- Shader hot-swapping techniques

### Geometry

The demo uses a torus geometry because:

- **Curved Surfaces**: Show lighting effects clearly
- **Continuous Normals**: Good for testing Fresnel/rim effects
- **Moderate Complexity**: 512 triangles - typical for AR objects
- **No Textures**: Focuses on lighting performance

### Matrix Math

Simple matrix operations are implemented inline to:

- Minimize dependencies
- Show transformation concepts
- Keep the demo self-contained

In production, use a math library like GLM.

## Further Optimizations

Additional techniques not demonstrated but relevant to AR:

1. **Level of Detail (LOD)**: Switch geometry complexity by distance
2. **Occlusion Culling**: Don't render hidden objects
3. **Instancing**: Render multiple objects efficiently
4. **Deferred Rendering**: Optimize multiple lights
5. **Mobile-specific Features**: PowerVR TBDR optimizations

## Profiling Tips

To measure actual performance differences:

```bash
# Run with vsync disabled for FPS measurement
LIBGL_ALWAYS_SOFTWARE=0 ./graphics-demo

# Use GPU profiling tools
# - ARM Mali Graphics Debugger (ARM GPUs)
# - Qualcomm Snapdragon Profiler (Adreno GPUs)
# - RenderDoc (Desktop testing)
```

## References

- [Khronos OpenGL ES Best Practices](https://www.khronos.org/opengl/wiki/OpenGL_ES)
- [ARM Mali GPU Best Practices](https://developer.arm.com/documentation/)
- [Real-Time Rendering, 4th Edition](http://www.realtimerendering.com/)
