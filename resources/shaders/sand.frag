#version 330 core

in vec2 TexCoords;

uniform sampler2D sandTexture;

out vec4 color;

void main() {
    color = texture(sandTexture, TexCoords);
    // color.a = 1.0;
}