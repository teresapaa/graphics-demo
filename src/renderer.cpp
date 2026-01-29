#include "renderer.h"
#include "shader.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

// Simple matrix operations for transformations
void mat4_identity(float* m) {
    for (int i = 0; i < 16; i++) m[i] = 0.0f;
    m[0] = m[5] = m[10] = m[15] = 1.0f;
}

void mat4_perspective(float* m, float fov, float aspect, float near, float far) {
    float f = 1.0f / tan(fov * 0.5f);
    mat4_identity(m);
    m[0] = f / aspect;
    m[5] = f;
    m[10] = (far + near) / (near - far);
    m[11] = -1.0f;
    m[14] = (2.0f * far * near) / (near - far);
    m[15] = 0.0f;
}

void mat4_rotate_y(float* m, float angle) {
    mat4_identity(m);
    m[0] = cos(angle);
    m[2] = sin(angle);
    m[8] = -sin(angle);
    m[10] = cos(angle);
}

void mat4_translate(float* m, float x, float y, float z) {
    mat4_identity(m);
    m[12] = x;
    m[13] = y;
    m[14] = z;
}

Renderer::Renderer() : window(nullptr), currentMode(BALANCED), showStats(true), 
                       windowWidth(800), windowHeight(600),
                       VAO(0), VBO(0), EBO(0), indexCount(0), rotation(0.0f), 
                       lastTime(0.0), frameCount(0), fps(0.0), cleanedUp(false) {
}

Renderer::~Renderer() {
    cleanup();
}

bool Renderer::initialize(int width, int height, const std::string& title) {
    windowWidth = width;
    windowHeight = height;
    
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    
    // Set OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // Create window
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    
    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }
    
    // Configure viewport
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    
    // Setup geometry and shaders
    setupGeometry();
    setupShaders();
    
    lastTime = glfwGetTime();
    
    return true;
}

void Renderer::setupGeometry() {
    // Create a simple torus-like shape (simplified for AR demo)
    const int segments = 32;
    const int rings = 16;
    const float majorRadius = 0.6f;
    const float minorRadius = 0.2f;
    
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
    // Generate torus vertices
    for (int i = 0; i <= rings; i++) {
        float v = (float)i / rings;
        float phi = v * 2.0f * 3.14159265359f;
        
        for (int j = 0; j <= segments; j++) {
            float u = (float)j / segments;
            float theta = u * 2.0f * 3.14159265359f;
            
            float x = (majorRadius + minorRadius * cos(phi)) * cos(theta);
            float y = minorRadius * sin(phi);
            float z = (majorRadius + minorRadius * cos(phi)) * sin(theta);
            
            // Normal calculation
            float cx = majorRadius * cos(theta);
            float cy = 0.0f;
            float cz = majorRadius * sin(theta);
            
            float nx = x - cx;
            float ny = y - cy;
            float nz = z - cz;
            
            float len = sqrt(nx*nx + ny*ny + nz*nz);
            if (len > 0.0001f) {
                nx /= len; ny /= len; nz /= len;
            }
            
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);
        }
    }
    
    // Generate indices
    for (int i = 0; i < rings; i++) {
        for (int j = 0; j < segments; j++) {
            int first = i * (segments + 1) + j;
            int second = first + segments + 1;
            
            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);
            
            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
    
    indexCount = indices.size();
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
}

void Renderer::setupShaders() {
    // Pre-compile all shaders
    perfShader = std::unique_ptr<Shader>(new Shader("shaders/vertex.glsl", "shaders/fragment_perf.glsl"));
    balancedShader = std::unique_ptr<Shader>(new Shader("shaders/vertex.glsl", "shaders/fragment_balanced.glsl"));
    hqShader = std::unique_ptr<Shader>(new Shader("shaders/vertex.glsl", "shaders/fragment_hq.glsl"));
}

void Renderer::calculateFPS() {
    double currentTime = glfwGetTime();
    frameCount++;
    
    if (currentTime - lastTime >= 1.0) {
        fps = frameCount / (currentTime - lastTime);
        frameCount = 0;
        lastTime = currentTime;
    }
}

void Renderer::render() {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Select shader based on mode (use pre-compiled shaders)
    Shader* shader = nullptr;
    switch (currentMode) {
        case HIGH_QUALITY:
            shader = hqShader.get();
            break;
        case BALANCED:
            shader = balancedShader.get();
            break;
        case PERFORMANCE:
            shader = perfShader.get();
            break;
    }
    
    if (!shader) return;
    
    shader->use();
    
    // Set up matrices
    float projection[16], model[16], view[16];
    float aspectRatio = (float)windowWidth / (float)windowHeight;
    mat4_perspective(projection, 0.785f, aspectRatio, 0.1f, 100.0f);
    mat4_translate(view, 0.0f, 0.0f, -3.0f);
    mat4_rotate_y(model, rotation);
    
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    shader->setMat4("model", model);
    
    // Set lighting parameters
    shader->setVec3("lightPos", 2.0f, 2.0f, 2.0f);
    shader->setVec3("viewPos", 0.0f, 0.0f, 3.0f);
    shader->setVec3("objectColor", 0.2f, 0.6f, 0.9f);
    shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    
    // Quality-specific parameters (only set for modes that use them)
    if (currentMode != PERFORMANCE) {
        switch (currentMode) {
            case HIGH_QUALITY:
                shader->setInt("qualityLevel", 3);
                shader->setFloat("specularStrength", 0.8f);
                shader->setInt("shininess", 64);
                break;
            case BALANCED:
                shader->setInt("qualityLevel", 2);
                shader->setFloat("specularStrength", 0.5f);
                shader->setInt("shininess", 32);
                break;
            default:
                break;
        }
    }
    
    // Render torus
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    // Update rotation with wrapping
    rotation = fmod(rotation + 0.01f, 2.0f * 3.14159265359f);
}

void Renderer::updateUI() {
    // Display stats in window title
    if (showStats) {
        std::string modeStr;
        switch (currentMode) {
            case HIGH_QUALITY:
                modeStr = "High Quality";
                break;
            case BALANCED:
                modeStr = "Balanced";
                break;
            case PERFORMANCE:
                modeStr = "Performance";
                break;
        }
        
        char title[256];
        snprintf(title, sizeof(title), "AR Graphics Demo - %s Mode | FPS: %.1f", 
                 modeStr.c_str(), fps);
        glfwSetWindowTitle(window, title);
    }
}

void Renderer::handleInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Renderer::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
        
        switch (key) {
            case GLFW_KEY_1:
                renderer->currentMode = PERFORMANCE;
                std::cout << "Switched to PERFORMANCE mode" << std::endl;
                break;
            case GLFW_KEY_2:
                renderer->currentMode = BALANCED;
                std::cout << "Switched to BALANCED mode" << std::endl;
                break;
            case GLFW_KEY_3:
                renderer->currentMode = HIGH_QUALITY;
                std::cout << "Switched to HIGH_QUALITY mode" << std::endl;
                break;
            case GLFW_KEY_S:
                renderer->showStats = !renderer->showStats;
                break;
        }
    }
}

void Renderer::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    renderer->windowWidth = width;
    renderer->windowHeight = height;
    glViewport(0, 0, width, height);
}

void Renderer::run() {
    std::cout << "\n=== AR Graphics Demo ===\n";
    std::cout << "Controls:\n";
    std::cout << "  1 - Performance Mode (optimized for AR devices)\n";
    std::cout << "  2 - Balanced Mode (good quality/performance trade-off)\n";
    std::cout << "  3 - High Quality Mode (maximum visual quality)\n";
    std::cout << "  S - Toggle stats display\n";
    std::cout << "  ESC - Exit\n\n";
    
    while (!glfwWindowShouldClose(window)) {
        handleInput();
        calculateFPS();
        render();
        updateUI();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Renderer::cleanup() {
    if (cleanedUp) return;  // Prevent double cleanup
    
    if (VAO) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    if (VBO) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (EBO) {
        glDeleteBuffers(1, &EBO);
        EBO = 0;
    }
    
    // Reset shader pointers
    perfShader.reset();
    balancedShader.reset();
    hqShader.reset();
    
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
        glfwTerminate();
    }
    
    cleanedUp = true;
}
