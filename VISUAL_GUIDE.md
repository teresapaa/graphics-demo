# Graphics Demo Visual Overview

## What This Demo Shows

The AR Graphics Demo is a real-time 3D rendering application that displays a rotating torus (donut shape) with three different quality levels of lighting and shading.

## Application Window

```
┌─────────────────────────────────────────────────────────────┐
│ AR Graphics Demo - Balanced Mode | FPS: 60.0                │
├─────────────────────────────────────────────────────────────┤
│                                                               │
│                          ██████                               │
│                      ████░░░░░░████                           │
│                    ██░░░░░░░░░░░░░░██                         │
│                  ██░░░░░░░░░░░░░░░░░░██                       │
│                ██░░░░░░░░░░░░░░░░░░░░░░██                     │
│               ██░░░░░░░░░░░░░░░░░░░░░░░░██                    │
│              ██░░░░░░░░░░░░░░░░░░░░░░░░░░██                   │
│             ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░██                  │
│            ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██                 │
│            ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██                 │
│           ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██                │
│           ██░░░░░░░░░░░░████████░░░░░░░░░░░░██                │
│           ██░░░░░░░░████        ████░░░░░░░░██                │
│           ██░░░░░░██                ██░░░░░░██                │
│            ██░░░░██                  ██░░░░██                 │
│            ██░░░░██                  ██░░░░██                 │
│             ██░░░░██                ██░░░░██                  │
│              ██░░░░░██            ██░░░░░██                   │
│               ██░░░░░░████    ████░░░░░░██                    │
│                ██░░░░░░░░████████░░░░░░██                     │
│                  ██░░░░░░░░░░░░░░░░░░██                       │
│                    ██░░░░░░░░░░░░░░██                         │
│                      ████░░░░░░████                           │
│                          ██████                               │
│                                                               │
│                                                               │
└─────────────────────────────────────────────────────────────┘

         < Rotating 3D Torus with Lighting Effects >
```

## Rendering Mode Differences

### Mode 1: Performance Mode (Press '1')
- **Lighting**: Simple ambient + basic diffuse
- **Visual**: Flat shading appearance
- **FPS**: Highest (90+ FPS on mobile)
- **Use Case**: Battery-critical AR scenarios

```
Simple, flat appearance:
   ████████
  ██░░░░░░██
 ██░░░░░░░░██
██░░░░░░░░░░██
```

### Mode 2: Balanced Mode (Press '2')
- **Lighting**: Blinn-Phong with specular highlights
- **Visual**: Good 3D appearance with moderate highlights
- **FPS**: Good (60+ FPS on mobile)
- **Use Case**: Standard AR applications

```
Smooth shading with highlights:
   ████████
  ██▓▓░░░░██
 ██░░░░░░░░██
██░░░░░░░░░░██
```

### Mode 3: High Quality Mode (Press '3')
- **Lighting**: Full Blinn-Phong + rim lighting + Fresnel
- **Visual**: Rich appearance with edge highlights and reflections
- **FPS**: Lower (30-45 FPS on mobile)
- **Use Case**: Demos, high-end devices

```
Enhanced with rim lighting and Fresnel:
   ▓▓████▓▓
  ██▓▓▓▓▓▓██
 ██▓▓░░░░▓▓██
██▓░░░░░░░░▓██
```

## Console Output

When running the demo, you'll see:

```
AR Graphics Quality vs Performance Demo
========================================

=== AR Graphics Demo ===
Controls:
  1 - Performance Mode (optimized for AR devices)
  2 - Balanced Mode (good quality/performance trade-off)
  3 - High Quality Mode (maximum visual quality)
  S - Toggle stats display
  ESC - Exit

Switched to BALANCED mode
```

## Key Features Visualized

1. **Real-time Rotation**: The torus continuously rotates
2. **Dynamic Lighting**: Light source positioned at (2, 2, 2)
3. **Interactive Controls**: Switch modes with number keys
4. **Performance Metrics**: FPS displayed in title bar
5. **AR-Optimized**: Three quality tiers for different devices

## Technical Highlights

- **Geometry**: 512 triangles (typical AR object complexity)
- **Shaders**: Three fragment shader variants
- **Color**: Blue torus (0.2, 0.6, 0.9) with white light
- **Background**: Dark blue-gray (0.1, 0.1, 0.15)

## Expected Performance

| Device Type | Performance | Balanced | High Quality |
|-------------|-------------|----------|--------------|
| High-end Mobile | 90 FPS | 60 FPS | 45 FPS |
| Mid-range Mobile | 60 FPS | 45 FPS | 30 FPS |
| Low-end Mobile | 45 FPS | 30 FPS | 20 FPS |
| Desktop | 500+ FPS | 400+ FPS | 300+ FPS |

*Note: Actual FPS depends on hardware capabilities*
