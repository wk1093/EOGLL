#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in ivec4 aBoneIDs;
layout (location = 4) in vec4 aWeights;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main() {
    FragPos = vec3(model*vec4(aPos, 1.0));
    gl_Position = projection*view*model*vec4(aPos, 1.0);
    Normal = mat3(transpose(inverse(model)))*aNormal;
    TexCoord = aTexCoord;


    




}