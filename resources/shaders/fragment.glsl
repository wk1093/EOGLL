#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

void main() {
    // Super simple lighting
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightPos = vec3(0.0, 5.0, 0.0);
    vec3 ambient = 0.1 * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 result = (ambient + diffuse) * vec3(1.0, 0.5, 0.31);
    FragColor = vec4(result, 1.0);

}