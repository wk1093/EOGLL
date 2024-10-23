#version 330 core

layout(location = 0) in vec3 aPos;

out vec2 TexCoords;

void main() {
    gl_Position = vec4(aPos, 1.0);
    // gl_Position of -1,-1 is TexCoord of 0,0
    // gl_Position of 1,1 is TexCoord of 1,1
    TexCoords = aPos.xy * 0.5 + 0.5;
    // TexCoords.y = 1.0 - TexCoords.y;

}