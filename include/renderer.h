#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

enum RenderMode {
    HIGH_QUALITY,
    BALANCED,
    PERFORMANCE
};

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    bool initialize(int width, int height, const std::string& title);
    void run();
    void cleanup();
    
private:
    GLFWwindow* window;
    RenderMode currentMode;
    bool showStats;
    
    // Rendering state
    GLuint VAO, VBO, EBO;
    float rotation;
    double lastTime;
    int frameCount;
    double fps;
    
    void setupGeometry();
    void render();
    void updateUI();
    void handleInput();
    void calculateFPS();
    
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif
