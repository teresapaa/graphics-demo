#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

class Shader;

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
    
    // Window dimensions
    int windowWidth;
    int windowHeight;
    
    // Cached shaders
    std::unique_ptr<Shader> perfShader;
    std::unique_ptr<Shader> balancedShader;
    std::unique_ptr<Shader> hqShader;
    
    // Rendering state
    GLuint VAO, VBO, EBO;
    unsigned int indexCount;
    float rotation;
    double lastTime;
    int frameCount;
    double fps;
    bool cleanedUp;
    
    void setupGeometry();
    void setupShaders();
    void render();
    void updateUI();
    void handleInput();
    void calculateFPS();
    
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};

#endif
