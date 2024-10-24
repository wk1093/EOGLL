#version 330 core

in vec2 TexCoords;

uniform sampler2D sandTexture;
uniform float time;
uniform float radius;

out vec4 color;

const vec4 BLACK = vec4(0.0, 0.0, 0.0, 1.0);
// FFC90E
const vec4 SAND = vec4(1.0, 201.0 / 255.0, 14.0 / 255.0, 1.0);
const vec4 SAND_D = vec4(1.0, 201.0 / 255.0, 13.0 / 255.0, 1.0);
const vec4 SAND_LD = vec4(1.0, 201.0 / 255.0, 12.0 / 255.0, 1.0);
const vec4 SAND_RD = vec4(1.0, 201.0 / 255.0, 11.0 / 255.0, 1.0);
const vec4 WATER = vec4(0.0, 0.0, 1.0, 1.0);
const vec4 WATER_D = vec4(1.0/255.0, 0.0, 1.0, 1.0);
const vec4 WATER_LD = vec4(2.0/255.0, 0.0, 1.0, 1.0);
const vec4 WATER_RD = vec4(3.0/255.0, 0.0, 1.0, 1.0);
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
uniform int mouseNum; // 0 means no click, 1 means erase, 2 means draw sand, 3 means draw water

bool sand_occupied(vec2 pos) {
    vec4 up = getPixel(pos.x, pos.y + 1);
    if (up == SAND_D && pos.y + 1 < HEIGHT) {
        return true;
    }
    vec4 lu = getPixel(pos.x - 1, pos.y + 1);
    vec4 ru = getPixel(pos.x + 1, pos.y + 1);
    if (lu == SAND_RD && pos.x - 1 >= 0 && pos.y + 1 < HEIGHT) {
        return true;
    }
    if (ru == SAND_LD && pos.x + 1 < WIDTH && pos.y + 1 < HEIGHT) {
        return true;
    }
    return false;
}

bool water_occupied(vec2 pos) {
    vec4 up = getPixel(pos.x, pos.y + 1);
    if (up == WATER_D && pos.y + 1 < HEIGHT) {
        return true;
    }
    vec4 lu = getPixel(pos.x - 1, pos.y + 1);
    vec4 ru = getPixel(pos.x + 1, pos.y + 1);
    if (lu == WATER_RD && pos.x - 1 >= 0 && pos.y + 1 < HEIGHT) {
        return true;
    }
    if (ru == WATER_LD && pos.x + 1 < WIDTH && pos.y + 1 < HEIGHT) {
        return true;
    }
    return false;
}

bool is_occupied(vec2 pos) {
    vec4 pixel = getPixel(pos.x, pos.y);
    if (pixel == SAND || pixel == WATER) {
        return true;
    }
    if (sand_occupied(pos)) {
        return true;
    }
    if (water_occupied(pos)) {
        return true;
    }
    return false;
}

void main() {
    vec4 curColor = getPixel(gl_FragCoord.x, gl_FragCoord.y);

    if (curColor == BLACK) {
        if (water_occupied(gl_FragCoord.xy)) {
            color = WATER;
            return;
        }

        if (sand_occupied(gl_FragCoord.xy)) {
            color = SAND;
            return;
        }
    }
    
    if (curColor == SAND_D) {
        color = BLACK;
        return;
    }
    if (curColor == SAND_LD) {
        color = BLACK;
        return;
    }
    if (curColor == SAND_RD) {
        color = BLACK;
        return;
    }
    if (curColor == WATER_D) {
        color = BLACK;
        return;
    }
    if (curColor == WATER_LD) {
        color = BLACK;
        return;
    }
    if (curColor == WATER_RD) {
        color = BLACK;
        return;
    }


    if (curColor == SAND) {
        vec4 down = getPixel(gl_FragCoord.x, gl_FragCoord.y - 1);
        if (down == BLACK && gl_FragCoord.y - 1 >= 0 && !is_occupied(vec2(gl_FragCoord.x, gl_FragCoord.y - 1))) {
            color = SAND_D;
            return;
        }
        vec4 ld = getPixel(gl_FragCoord.x - 1, gl_FragCoord.y - 1);
        vec4 rd = getPixel(gl_FragCoord.x + 1, gl_FragCoord.y - 1);
        bool biasLeft = rand_bool();
        if (biasLeft) {
            if (ld == BLACK && gl_FragCoord.x - 1 >= 0 && gl_FragCoord.y - 1 >= 0 && !is_occupied(vec2(gl_FragCoord.x - 1, gl_FragCoord.y - 1))) {
                color = SAND_LD;
                return;
            } else if (rd == BLACK && gl_FragCoord.x + 1 < WIDTH && gl_FragCoord.y - 1 >= 0 && !is_occupied(vec2(gl_FragCoord.x + 1, gl_FragCoord.y - 1))) {
                color = SAND_RD;
                return;
            }
        } else {
            if (rd == BLACK && gl_FragCoord.x + 1 < WIDTH && gl_FragCoord.y - 1 >= 0 && !is_occupied(vec2(gl_FragCoord.x + 1, gl_FragCoord.y - 1))) {
                color = SAND_RD;
                return;
            } else if (ld == BLACK && gl_FragCoord.x - 1 >= 0 && gl_FragCoord.y - 1 >= 0 && !is_occupied(vec2(gl_FragCoord.x - 1, gl_FragCoord.y - 1))) {
                color = SAND_LD;
                return;
            }
        }
    }

    if (curColor == WATER) {
        vec4 down = getPixel(gl_FragCoord.x, gl_FragCoord.y - 1);
        if (down == BLACK && gl_FragCoord.y - 1 >= 0 && !is_occupied(vec2(gl_FragCoord.x, gl_FragCoord.y - 1))) {
            color = WATER_D;
            return;
        }
        vec4 ld = getPixel(gl_FragCoord.x - 1, gl_FragCoord.y - 1);
        vec4 rd = getPixel(gl_FragCoord.x + 1, gl_FragCoord.y - 1);
        bool biasLeft = rand_bool();
        if (biasLeft) {
            if (ld == BLACK && gl_FragCoord.x - 1 >= 0 && gl_FragCoord.y - 1 >= 0 && !is_occupied(vec2(gl_FragCoord.x - 1, gl_FragCoord.y - 1))) {
                color = WATER_LD;
                return;
            } else if (rd == BLACK && gl_FragCoord.x + 1 < WIDTH && gl_FragCoord.y - 1 >= 0 && !is_occupied(vec2(gl_FragCoord.x + 1, gl_FragCoord.y - 1))) {
                color = WATER_RD;
                return;
            }
        } else {
            if (rd == BLACK && gl_FragCoord.x + 1 < WIDTH && gl_FragCoord.y - 1 >= 0 && !is_occupied(vec2(gl_FragCoord.x + 1, gl_FragCoord.y - 1))) {
                color = WATER_RD;
                return;
            } else if (ld == BLACK && gl_FragCoord.x - 1 >= 0 && gl_FragCoord.y - 1 >= 0 && !is_occupied(vec2(gl_FragCoord.x - 1, gl_FragCoord.y - 1))) {
                color = WATER_LD;
                return;
            }
        }
        
    }

    if (mouseClick.x >= 0 && mouseClick.y >= 0) {
        float tol = radius;
        if (abs(gl_FragCoord.x - mouseClick.x) < tol && abs(gl_FragCoord.y - (600-mouseClick.y)) < tol) {
            if (mouseNum == 1) {
                color = BLACK;
                return;
            }
            if (mouseNum == 2) {
                color = SAND;
                return;
            }
            if (mouseNum == 3) {
                color = WATER;
                return;
            }
        }
    }

    color = curColor;
}