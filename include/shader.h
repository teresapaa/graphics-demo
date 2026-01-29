#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

class Shader {
public:
    GLuint programID;
    
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setMat4(const std::string &name, const float* value) const;
    
private:
    GLuint compileShader(const char* source, GLenum type);
    std::string loadShaderSource(const char* path);
};

#endif
