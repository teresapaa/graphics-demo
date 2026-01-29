#include "renderer.h"
#include <iostream>

int main() {
    std::cout << "AR Graphics Quality vs Performance Demo\n";
    std::cout << "========================================\n\n";
    
    Renderer renderer;
    
    if (!renderer.initialize(800, 600, "AR Graphics Demo")) {
        std::cerr << "Failed to initialize renderer" << std::endl;
        return -1;
    }
    
    renderer.run();
    // cleanup() is called in destructor, no need to call explicitly
    
    return 0;
}
