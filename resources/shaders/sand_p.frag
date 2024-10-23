#version 330 core

in vec2 TexCoords;

uniform sampler2D sandTexture;
uniform float time;
uniform float radius;

out vec4 color;

const vec4 BLACK = vec4(0.0, 0.0, 0.0, 1.0);
// FFC90E
const vec4 SAND = vec4(1.0, 201.0 / 255.0, 14.0 / 255.0, 1.0);
const vec4 DOWN = vec4(1.0, 201.0 / 255.0, 13.0 / 255.0, 1.0);
const vec4 LEFTDOWN = vec4(1.0, 201.0 / 255.0, 12.0 / 255.0, 1.0);
const vec4 RIGHTDOWN = vec4(1.0, 201.0 / 255.0, 11.0 / 255.0, 1.0);
const int WIDTH = 800;
const int HEIGHT = 600;

vec4 getPixel(float x, float y) {
    return texture(sandTexture, vec2(x / WIDTH, y / HEIGHT));
}

float pseudo(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

bool rand_bool() {
    return pseudo(vec2(time)) > 0.5;
}

uniform vec2 mouseClick; // - values means no click


void main() {
    vec2 curPixel = vec2(gl_FragCoord.x, gl_FragCoord.y);

    vec4 curColor = getPixel(curPixel.x, curPixel.y);

    if (curColor == BLACK) {
        vec4 up = getPixel(curPixel.x, curPixel.y + 1);
        if (up == DOWN && curPixel.y + 1 < HEIGHT) {
            color = SAND;
            return;
        }
        vec4 lu = getPixel(curPixel.x - 1, curPixel.y + 1);
        vec4 ru = getPixel(curPixel.x + 1, curPixel.y + 1);
        if (lu == RIGHTDOWN && curPixel.x - 1 >= 0 && curPixel.y + 1 < HEIGHT) {
            color = SAND;
            return;
        } else if (ru == LEFTDOWN && curPixel.x + 1 < WIDTH && curPixel.y + 1 < HEIGHT) {
            color = SAND;
            return;
        }
    }
    if (curColor == DOWN) {
        color = BLACK;
        return;
    }
    if (curColor == LEFTDOWN) {
        color = BLACK;
        return;
    }
    if (curColor == RIGHTDOWN) {
        color = BLACK;
        return;
    }

    if (curColor == SAND) {
        vec4 down = getPixel(curPixel.x, curPixel.y - 1);
        if (down == BLACK && curPixel.y - 1 >= 0) {
            color = DOWN;
            return;
        } else {
            vec4 ld = getPixel(curPixel.x - 1, curPixel.y - 1);
            vec4 rd = getPixel(curPixel.x + 1, curPixel.y - 1);
            bool biasLeft = rand_bool();
            if (biasLeft) {
                if (ld == BLACK && curPixel.x - 1 >= 0 && curPixel.y - 1 >= 0) {
                    color = LEFTDOWN;
                    return;
                } else if (rd == BLACK && curPixel.x + 1 < WIDTH && curPixel.y - 1 >= 0) {
                    color = RIGHTDOWN;
                    return;
                }
            } else {
                if (rd == BLACK && curPixel.x + 1 < WIDTH && curPixel.y - 1 >= 0) {
                    color = RIGHTDOWN;
                    return;
                } else if (ld == BLACK && curPixel.x - 1 >= 0 && curPixel.y - 1 >= 0) {
                    color = LEFTDOWN;
                    return;
                }
            }
        }
    }

    if (mouseClick.x >= 0 && mouseClick.y >= 0) {
        float tol = radius;
        if (abs(gl_FragCoord.x - mouseClick.x) < tol && abs(gl_FragCoord.y - (600-mouseClick.y)) < tol) {
            color = SAND;
            return;
        }
    }

    color = curColor;
}