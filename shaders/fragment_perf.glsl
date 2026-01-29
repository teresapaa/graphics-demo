#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    // PERFORMANCE MODE
    // Simplified lighting for maximum performance on AR devices
    // Uses only ambient and simplified diffuse (Lambert)
    
    // Ambient lighting
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;
    
    // Simplified diffuse lighting (no normalization to save GPU cycles)
    vec3 lightDir = lightPos - FragPos;
    float diff = max(dot(Normal, lightDir) * 0.1, 0.0);
    vec3 diffuse = diff * lightColor;
    
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}
