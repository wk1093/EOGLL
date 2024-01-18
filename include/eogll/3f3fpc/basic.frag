#define GLSL(src) "#version 330 core\n" #src
GLSL(

out vec4 FragColor;
in vec3 ourColor;

void main() {
FragColor = vec4(ourColor, 1.0f);
}

);