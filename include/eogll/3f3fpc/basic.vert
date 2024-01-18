#define GLSL(src) "#version 330 core\n" #src
GLSL(

layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1

out vec3 ourColor; // output a color to the fragment shader

void main() {
gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
ourColor = aColor; // set ourColor to the input color we got from the vertex data
}

);