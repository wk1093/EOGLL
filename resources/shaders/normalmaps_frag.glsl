#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D tex;
uniform sampler2D normalmap;
uniform vec3 viewPos;

void main() {
    vec3 nrm = normalize(texture(normalmap, TexCoord).rgb * 2.0 - 1.0);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightPos = vec3(0.0, 5.0, 1.0);
    // ambient
    vec3 ambient = 0.5 * lightColor;

    // diffuse
    vec3 norm = normalize(nrm+Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = 0.9 * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * texture(tex, TexCoord).rgb;


    FragColor = vec4(result, 1.0);

}