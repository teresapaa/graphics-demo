#!/bin/bash

# Example script to build and run the graphics demo

echo "=== AR Graphics Demo Build Script ==="
echo ""

# Clean previous build
if [ -f "graphics-demo" ]; then
    echo "Cleaning previous build..."
    make clean
fi

# Build the project
echo "Building project..."
if make; then
    echo ""
    echo "Build successful!"
    echo ""
    echo "To run the demo, execute:"
    echo "  ./graphics-demo"
    echo ""
    echo "Make sure you have an X display available (DISPLAY environment variable set)"
    echo ""
else
    echo "Build failed!"
    exit 1
fi
