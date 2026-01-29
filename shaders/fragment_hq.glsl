#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float specularStrength;
uniform int shininess;

void main()
{
    // HIGH QUALITY MODE
    // Uses Blinn-Phong shading with multiple quality features
    
    // Ambient lighting
    float ambientStrength = 0.15;
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular lighting (Blinn-Phong)
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), float(shininess));
    vec3 specular = specularStrength * spec * lightColor;
    
    // Rim lighting for AR-style edge enhancement
    float rimStrength = 0.5;
    float rim = 1.0 - max(dot(viewDir, norm), 0.0);
    rim = pow(rim, 3.0);
    vec3 rimLight = rimStrength * rim * vec3(0.3, 0.5, 0.8);
    
    // Fresnel effect
    float fresnel = pow(1.0 - max(dot(viewDir, norm), 0.0), 2.0);
    vec3 fresnelColor = fresnel * vec3(0.2, 0.4, 0.6);
    
    vec3 result = (ambient + diffuse + specular + rimLight + fresnelColor) * objectColor;
    FragColor = vec4(result, 1.0);
}
