#include "eogll.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

const char* eogllGetVersionString() {
    return "EOGLL " HEDLEY_STRINGIFY(EOGLL_VERSION_MAJOR) "." HEDLEY_STRINGIFY(EOGLL_VERSION_MINOR) "." HEDLEY_STRINGIFY(EOGLL_VERSION_PATCH);
}

void eogllGLFWErrorCallback(int error, const char* description) {
    EOGLL_LOG_TRACE(stdout, "\n");
    EOGLL_LOG_ERROR(stderr, "GLFW Error %d: %s\n", error, description);
}

uint8_t eogllInit() {
    EOGLL_LOG_TRACE(stdout, "\n");
    if (!glfwInit()) {
        return EOGLL_FAILURE;
    }
    glfwSetErrorCallback(eogllGLFWErrorCallback);
    EOGLL_LOG_INFO(stdout, "%s\n", eogllGetVersionString());
    EOGLL_LOG_INFO(stdout, "GLFW %s\n", glfwGetVersionString());


    return EOGLL_SUCCESS;
}

void eogllTerminate() {
    EOGLL_LOG_TRACE(stdout, "\n");
    glfwTerminate();
    EOGLL_LOG_INFO(stdout, "Bye!\n");
}

char* eogllReadFile(const char* path) {
    EOGLL_LOG_TRACE(stdout, "%s\n", path);
    FILE* file = fopen(path, "rb");
    if (!file) {
        EOGLL_LOG_ERROR(stderr, "Failed to open file %s\n", path);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        EOGLL_LOG_ERROR(stderr, "Failed to allocate memory for file %s\n", path);
        return NULL;
    }
    fread(buffer, 1, length, file);
    fclose(file);
    buffer[length] = '\0';
    return buffer;
}

void eogllFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    EOGLL_LOG_TRACE(stdout, "\n");
    EOGLL_LOG_DEBUG(stdout, "Framebuffer size changed to %dx%d\n", width, height);
    glViewport(0, 0, width, height);

    EogllWindow* eogllWindow = (EogllWindow*)glfwGetWindowUserPointer(window);
    eogllWindow->width = (uint32_t)width;
    eogllWindow->height = (uint32_t)height;
}

void eogllWindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    EOGLL_LOG_TRACE(stdout, "%d %d %d %d\n", key, scancode, action, mods);
    EogllWindow* eogllWindow = (EogllWindow*)glfwGetWindowUserPointer(window);
    if (eogllWindow == NULL) {
        EOGLL_LOG_ERROR(stderr, "eogllWindow is NULL\n");
        return;
    }
    if (action == EOGLL_PRESS) {
        eogllWindow->press[key] = true;
        eogllWindow->isDown[key] = true;
    } else if (action == EOGLL_RELEASE) {
        eogllWindow->release[key] = true;
        eogllWindow->isDown[key] = false;
    }
}

void eogllWindowMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    EOGLL_LOG_TRACE(stdout, "%d %d %d\n", button, action, mods);
    EogllWindow* eogllWindow = (EogllWindow*)glfwGetWindowUserPointer(window);
    if (eogllWindow == NULL) {
        EOGLL_LOG_ERROR(stderr, "eogllWindow is NULL\n");
        return;
    }
    if (action == EOGLL_PRESS) {
        eogllWindow->mousePress[button] = true;
        eogllWindow->mouseIsDown[button] = true;
    } else if (action == EOGLL_RELEASE) {
        eogllWindow->mouseRelease[button] = true;
        eogllWindow->mouseIsDown[button] = false;
    }
}

void eogllWindowCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    EOGLL_LOG_TRACE(stdout, "%f %f\n", xpos, ypos);
    EogllWindow* eogllWindow = (EogllWindow*)glfwGetWindowUserPointer(window);
    if (eogllWindow == NULL) {
        EOGLL_LOG_ERROR(stderr, "eogllWindow is NULL\n");
        return;
    }

    eogllWindow->mousedx += xpos - eogllWindow->mousex; // we add to it incase there is multiple mouse movements in one frame (we want to keep track of the total movement)
    eogllWindow->mousedy += ypos - eogllWindow->mousey;
    eogllWindow->mousex = xpos;
    eogllWindow->mousey = ypos;
}

void eogllWindowScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    EOGLL_LOG_TRACE(stdout, "%f %f\n", xoffset, yoffset);
    EogllWindow* eogllWindow = (EogllWindow*)glfwGetWindowUserPointer(window);
    if (eogllWindow == NULL) {
        EOGLL_LOG_ERROR(stderr, "eogllWindow is NULL\n");
        return;
    }

    eogllWindow->mouseScrollx = xoffset;
    eogllWindow->mouseScrolly = yoffset;
}

void eogllWindowFocusCallback(GLFWwindow* window, int focused) {
    EOGLL_LOG_DEBUG(stdout, "%d\n", focused);
    EogllWindow* eogllWindow = (EogllWindow*)glfwGetWindowUserPointer(window);
    if (eogllWindow == NULL) {
        EOGLL_LOG_ERROR(stderr, "eogllWindow is NULL\n");
        return;
    }

    eogllWindow->focused = focused;
}

EogllWindowHints eogllCreateWindowHints(bool resizable, bool decorated, bool floating, bool maximized, bool visible, bool focused) {
    EogllWindowHints hints;
    hints.resizable = resizable;
    hints.decorated = decorated;
    hints.floating = floating;
    hints.maximized = maximized;
    hints.visible = visible;
    hints.focused = focused;
    return hints;
}

EogllWindowHints eogllDefaultWindowHints() {
    return eogllCreateWindowHints(true, true, false, false, true, true);
}

EogllWindow* eogllCreateWindow(uint32_t width, uint32_t height, const char* title, EogllWindowHints hints) {
    EOGLL_LOG_TRACE(stdout, "%s %dx%d %d %d %d %d %d %d\n", title, width, height, resizable, decorated, floating, maximized, visible, focused);

    EogllWindow* window = (EogllWindow*)malloc(sizeof(EogllWindow));
    if (!window) {
        EOGLL_LOG_ERROR(stderr, "Failed to allocate memory for window\n");
        return NULL;
    }
    window->width = width;
    window->height = height;
    EOGLL_LOG_TRACE(stdout, "%d keys, %d mouse buttons\n", EOGLL_KEY_LAST + 1, EOGLL_MOUSE_BUTTON_LAST + 1);
    for (int i = 0; i < EOGLL_KEY_LAST + 1; i++) {
        window->press[i] = false;
        window->release[i] = false;
        window->isDown[i] = false;
    }
    for (int i = 0; i < EOGLL_MOUSE_BUTTON_LAST + 1; i++) {
        window->mousePress[i] = false;
        window->mouseRelease[i] = false;
        window->mouseIsDown[i] = false;
    }
    window->mousedx = 0;
    window->mousedy = 0;
    window->mouseScrollx = 0;
    window->mouseScrolly = 0;
    window->focused = hints.focused;
    glfwWindowHint(GLFW_RESIZABLE, hints.resizable);
    glfwWindowHint(GLFW_DECORATED, hints.decorated);
    glfwWindowHint(GLFW_FLOATING, hints.floating);
    glfwWindowHint(GLFW_MAXIMIZED, hints.maximized);
    glfwWindowHint(GLFW_VISIBLE, hints.visible);
    glfwWindowHint(GLFW_FOCUSED, hints.focused);
    // 330 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    window->window = glfwCreateWindow((int)width, (int)height, title, NULL, NULL);
    glfwSetWindowUserPointer(window->window, window);
    glfwSetFramebufferSizeCallback(window->window, eogllFramebufferSizeCallback);

    if (!window->window) {
        EOGLL_LOG_ERROR(stderr, "Failed to create window\n");
        char* description;
        int g = glfwGetError((const char **) &description);
        EOGLL_LOG_ERROR(stderr, "GLFW Error %d: %s\n", g, description);

        return NULL;
    }
    glfwSetFramebufferSizeCallback(window->window, eogllFramebufferSizeCallback);
    glfwSetKeyCallback(window->window, eogllWindowKeyCallback);
    glfwSetMouseButtonCallback(window->window, eogllWindowMouseButtonCallback);
    glfwSetCursorPosCallback(window->window, eogllWindowCursorPosCallback);
    glfwSetScrollCallback(window->window, eogllWindowScrollCallback);
    glfwSetWindowFocusCallback(window->window, eogllWindowFocusCallback);
    glfwMakeContextCurrent(window->window);
    if (!gladLoadGL(glfwGetProcAddress)) {
        EOGLL_LOG_ERROR(stderr, "Failed to load OpenGL\n");
        return NULL;
    }
    glfwGetCursorPos(window->window, &window->mousex, &window->mousey);
    EOGLL_LOG_INFO(stdout, "%s %s\n", glGetString(GL_VENDOR), glGetString(GL_VERSION));
    EOGLL_LOG_INFO(stdout, "%s\n", glGetString(GL_RENDERER));
    int max;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max);
    EOGLL_LOG_INFO(stdout, "%d vertex attributes max\n", max);

    return window;

}

bool eogllWindowShouldClose(EogllWindow* window) {
    bool r = glfwWindowShouldClose(window->window);
    EOGLL_LOG_TRACE(stdout, "%d\n", r);
    return r;
}

void eogllSetWindowShouldClose(EogllWindow* window, bool shouldClose) {
    EOGLL_LOG_TRACE(stdout, "%d\n", shouldClose);
    glfwSetWindowShouldClose(window->window, shouldClose);
}

void eogllPollEvents(EogllWindow* window) {
    EOGLL_LOG_TRACE(stdout, "\n");

    for (int i = 0; i < EOGLL_KEY_LAST + 1; i++) {
        window->press[i] = false;
        window->release[i] = false;
    }
    for (int i = 0; i < EOGLL_MOUSE_BUTTON_LAST + 1; i++) {
        window->mousePress[i] = false;
        window->mouseRelease[i] = false;
    }
    window->mousedx = 0;
    window->mousedy = 0;
    glfwPollEvents();
}

void eogllSwapBuffers(EogllWindow* window) {
    EOGLL_LOG_TRACE(stdout, "\n");
    glfwSwapBuffers(window->window);
}

void eogllDestroyWindow(EogllWindow* window) {
    EOGLL_LOG_TRACE(stdout, "\n");
    glfwDestroyWindow(window->window);
    free(window);
}

bool eogllGetKeyPress(EogllWindow* window, int key) {
    bool r = window->press[key];
    EOGLL_LOG_TRACE(stdout, "%d %d\n", key, r);
    return r;
}

bool eogllGetKeyRelease(EogllWindow* window, int key) {
    bool r = window->release[key];
    EOGLL_LOG_TRACE(stdout, "%d %d\n", key, r);
    return r;
}

bool eogllGetKeyIsDown(EogllWindow* window, int key) {
    bool r = window->isDown[key];
    EOGLL_LOG_TRACE(stdout, "%d %d\n", key, r);
    return r;
}

bool eogllGetMousePress(EogllWindow* window, int button) {
    bool r = window->mousePress[button];
    EOGLL_LOG_TRACE(stdout, "%d %d\n", button, r);
    return r;
}

bool eogllGetMouseRelease(EogllWindow* window, int button) {
    bool r = window->mouseRelease[button];
    EOGLL_LOG_TRACE(stdout, "%d %d\n", button, r);
    return r;
}

bool eogllGetMouseIsDown(EogllWindow* window, int button) {
    bool r = window->mouseIsDown[button];
    EOGLL_LOG_TRACE(stdout, "%d %d\n", button, r);
    return r;
}

void eogllGetMousePos(EogllWindow* window, double* xpos, double* ypos) {
    *xpos = window->mousex;
    *ypos = window->mousey;
}

void eogllSetMousePos(EogllWindow* window, double xpos, double ypos) {
    EOGLL_LOG_TRACE(stdout, "%f %f\n", xpos, ypos);
    glfwSetCursorPos(window->window, xpos, ypos);
    window->mousex = xpos;
    window->mousey = ypos;
}

void eogllGetMouseScroll(EogllWindow* window, double* xscroll, double* yscroll) {
    *xscroll = window->mouseScrollx;
    *yscroll = window->mouseScrolly;
}

void eogllGetWindowSize(EogllWindow* window, uint32_t* width, uint32_t* height) {
    *width = window->width;
    *height = window->height;
}

void eogllSetWindowSize(EogllWindow* window, uint32_t width, uint32_t height) {
    EOGLL_LOG_TRACE(stdout, "%dx%d\n", width, height);
    glfwSetWindowSize(window->window, (int)width, (int)height);
    window->width = width;
    window->height = height;
}

void eogllGetWindowPos(EogllWindow* window, int* xpos, int* ypos) {
    glfwGetWindowPos(window->window, xpos, ypos);
}

void eogllSetWindowPos(EogllWindow* window, int xpos, int ypos) {
    EOGLL_LOG_TRACE(stdout, "%d %d\n", xpos, ypos);
    glfwSetWindowPos(window->window, xpos, ypos);
}

void eogllGetCursorPos(EogllWindow* window, double* xpos, double* ypos) {
    glfwGetCursorPos(window->window, xpos, ypos);
}

void eogllSetCursorPos(EogllWindow* window, double xpos, double ypos) {
    EOGLL_LOG_TRACE(stdout, "%f %f\n", xpos, ypos);
    glfwSetCursorPos(window->window, xpos, ypos);
}

static inline int max( int a , int b )
{
    return a > b ? a : b;
}

static inline int min( int a , int b )
{
    return a < b ? a : b;
}

bool glfwSetWindowCenter(GLFWwindow *window) {
    if(!window)
        return false;

    int sx = 0, sy = 0;
    int px = 0, py = 0;
    int mx = 0, my = 0;
    int monitor_count = 0;
    int best_area = 0;
    int final_x = 0, final_y = 0;

    glfwGetWindowSize(window, &sx, &sy);
    glfwGetWindowPos(window, &px, &py);

    // Iterate throug all monitors
    GLFWmonitor **m = glfwGetMonitors(&monitor_count);
    if(!m)
        return false;

    for(int j = 0; j < monitor_count; ++j) {

        glfwGetMonitorPos( m[j] , &mx, &my );
        const GLFWvidmode * mode = glfwGetVideoMode( m[j] );
        if( !mode )
            continue;

        // Get intersection of two rectangles - screen and window
        int minX = max(mx, px);
        int minY = max(my, py);

        int maxX = min(mx+mode->width, px+sx);
        int maxY = min(my+mode->height, py+sy);

        // Calculate area of the intersection
        int area = max(maxX - minX, 0) * max(maxY - minY , 0);

        // If its bigger than actual (window covers more space on this monitor)
        if(area > best_area)
        {
            // Calculate proper position in this monitor
            final_x = mx + (mode->width-sx)/2;
            final_y = my + (mode->height-sy)/2;

            best_area = area;
        }

    }

    // We found something
    if(best_area)
        glfwSetWindowPos(window, final_x, final_y);

        // Something is wrong - current window has NOT any intersection with any monitors. Move it to the default one.
    else {
        GLFWmonitor * primary = glfwGetPrimaryMonitor();
        if(primary) {
            const GLFWvidmode *desktop = glfwGetVideoMode(primary);

            if(desktop)
                glfwSetWindowPos(window, (desktop->width-sx)/2, (desktop->height-sy)/2);
            else
                return false;
        }
        else
            return false;
    }

    return true;
}

void eogllCenterWindow(EogllWindow* window) {
    glfwSetWindowCenter(window->window);
}

double eogllGetTime() {
    return (double)glfwGetTime();
}

void eogllSetCursorMode(EogllWindow* window, int mode) {
    glfwSetInputMode(window->window, GLFW_CURSOR, mode);
}

void eogllClearColor(EogllColor color) {
    EOGLL_LOG_TRACE(stdout, "%f %f %f %f\n", color.r, color.g, color.b, color.a);
    glClearColor(color.r, color.g, color.b, color.a);
}

EogllColor eogllCreateColor(float r, float g, float b, float a) {
    EogllColor color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}

bool eogllColorEqual(EogllColor a, EogllColor b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

EogllColor EOGLL_COLOR_BLACK = {0.0f, 0.0f, 0.0f, 1.0f};
EogllColor EOGLL_COLOR_WHITE = {1.0f, 1.0f, 1.0f, 1.0f};
EogllColor EOGLL_COLOR_RED = {1.0f, 0.0f, 0.0f, 1.0f};
EogllColor EOGLL_COLOR_GREEN = {0.0f, 1.0f, 0.0f, 1.0f};
EogllColor EOGLL_COLOR_BLUE = {0.0f, 0.0f, 1.0f, 1.0f};
EogllColor EOGLL_COLOR_YELLOW = {1.0f, 1.0f, 0.0f, 1.0f};
EogllColor EOGLL_COLOR_MAGENTA = {1.0f, 0.0f, 1.0f, 1.0f};
EogllColor EOGLL_COLOR_CYAN = {0.0f, 1.0f, 1.0f, 1.0f};
EogllColor EOGLL_COLOR_TRANSPARENT = {0.0f, 0.0f, 0.0f, 0.0f};

EogllShaderProgram* eogllLinkProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
    EogllShaderProgram *shader = (EogllShaderProgram *) malloc(sizeof(EogllShaderProgram));

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
        EOGLL_LOG_ERROR(stderr, "Vertex shader compilation failed: %s\n", infoLog);
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
        EOGLL_LOG_ERROR(stderr, "Fragment shader compilation failed: %s\n", infoLog);
    }


    shader->id = glCreateProgram();

    glAttachShader(shader->id, vertexShader);
    glAttachShader(shader->id, fragmentShader);
    glLinkProgram(shader->id);

    glGetProgramiv(shader->id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader->id, sizeof(infoLog), NULL, infoLog);
        EOGLL_LOG_ERROR(stderr, "Shader program linking failed: %s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader;
}

EogllShaderProgram* eogllLinkProgramFromFile(const char* vertexShaderPath, const char* fragmentShaderPath) {
    char* vertexShaderSource = eogllReadFile(vertexShaderPath);
    if (!vertexShaderSource) {
        EOGLL_LOG_ERROR(stderr, "Failed to read vertex shader source from %s\n", vertexShaderPath);
        return NULL;
    }
    char* fragmentShaderSource = eogllReadFile(fragmentShaderPath);
    if (!fragmentShaderSource) {
        EOGLL_LOG_ERROR(stderr, "Failed to read fragment shader source from %s\n", fragmentShaderPath);
        return NULL;
    }
    EogllShaderProgram* shader = eogllLinkProgram(vertexShaderSource, fragmentShaderSource);
    free(vertexShaderSource);
    free(fragmentShaderSource);
    return shader;
}

void eogllDeleteProgram(EogllShaderProgram* shader) {
    glDeleteProgram(shader->id);
    free(shader);
}

void eogllUseProgram(EogllShaderProgram* shader) {
    glUseProgram(shader->id);
}

void eogllSetUniformMatrix4fv(EogllShaderProgram* shader, const char* name, mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(shader->id, name), 1, GL_FALSE, (float*)value);
}

void eogllSetUniform4f(EogllShaderProgram* shader, const char* name, float v0, float v1, float v2, float v3) {
    glUniform4f(glGetUniformLocation(shader->id, name), v0, v1, v2, v3);
}

void eogllSetUniform4fv(EogllShaderProgram* shader, const char* name, vec4 value) {
    glUniform4fv(glGetUniformLocation(shader->id, name), 1, value);
}

void eogllSetUniform3f(EogllShaderProgram* shader, const char* name, float v0, float v1, float v2) {
    glUniform3f(glGetUniformLocation(shader->id, name), v0, v1, v2);
}

void eogllSetUniform3fv(EogllShaderProgram* shader, const char* name, vec3 value) {
    glUniform3fv(glGetUniformLocation(shader->id, name), 1, value);
}

void eogllSetUniform2f(EogllShaderProgram* shader, const char* name, float v0, float v1) {
    glUniform2f(glGetUniformLocation(shader->id, name), v0, v1);
}

void eogllSetUniform2fv(EogllShaderProgram* shader, const char* name, vec2 value) {
    glUniform2fv(glGetUniformLocation(shader->id, name), 1, value);
}

void eogllSetUniform1f(EogllShaderProgram* shader, const char* name, float v0) {
    glUniform1f(glGetUniformLocation(shader->id, name), v0);
}

void eogllSetUniform1fv(EogllShaderProgram* shader, const char* name, float* vector, GLsizei count) {
    glUniform1fv(glGetUniformLocation(shader->id, name), count, vector);
}

void eogllSetUniform1i(EogllShaderProgram* shader, const char* name, int v0) {
    glUniform1i(glGetUniformLocation(shader->id, name), v0);
}

void eogllSetUniform1iv(EogllShaderProgram* shader, const char* name, int* vector, GLsizei count) {
    glUniform1iv(glGetUniformLocation(shader->id, name), count, vector);
}

void eogllSetUniform1ui(EogllShaderProgram* shader, const char* name, unsigned int v0) {
    glUniform1ui(glGetUniformLocation(shader->id, name), v0);
}

void eogllSetUniform1uiv(EogllShaderProgram* shader, const char* name, unsigned int* vector, GLsizei count) {
    glUniform1uiv(glGetUniformLocation(shader->id, name), count, vector);
}

void eogllSetUniformMatrix2fv(EogllShaderProgram* shader, const char* name, mat2 value) {
    glUniformMatrix2fv(glGetUniformLocation(shader->id, name), 1, GL_FALSE, (float*)value);
}

void eogllSetUniformMatrix3fv(EogllShaderProgram* shader, const char* name, mat3 value) {
    glUniformMatrix3fv(glGetUniformLocation(shader->id, name), 1, GL_FALSE, (float*)value);
}



unsigned int eogllGenVertexArray() {
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    return vao;
}

unsigned int eogllGenBuffer(unsigned int vao, GLenum mode, GLsizeiptr count, const void* indices, GLenum usage) {
    glBindVertexArray(vao);
    unsigned int vo;
    glGenBuffers(1, &vo);
    glBindBuffer(mode, vo);
    glBufferData(mode, count, indices, usage);
    glBindVertexArray(0);
    return vo;
}

EogllAttribBuilder eogllCreateAttribBuilder() {
    EogllAttribBuilder builder = {{0}, 0};
    return builder;
}

GLint eogllSizeOf(GLenum type) {
    // glVertexAttribPointer or glVertexAttribIPointer: GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, and GL_UNSIGNED_INT
    // glVertexAttribPointer: GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV and GL_UNSIGNED_INT_10F_11F_11F_REV
    // glVertexAttribLPointer: GL_DOUBLE
    switch (type) {
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
            return 1;
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
        case GL_HALF_FLOAT:
            return 2;
        case GL_INT:
        case GL_UNSIGNED_INT:
        case GL_FLOAT:
        case GL_INT_2_10_10_10_REV:
        case GL_UNSIGNED_INT_2_10_10_10_REV:
        case GL_UNSIGNED_INT_10F_11F_11F_REV:
            return 4;
        case GL_DOUBLE:
            return 8;
        default:
        EOGLL_LOG_WARN(stderr, "Unknown GL type %d\n", type);
            return 0;
    }
}

void eogllAddAttribute(EogllAttribBuilder *builder, GLenum type, GLint num) {
    builder->attribs[builder->numAttribs].type = type;
    builder->attribs[builder->numAttribs].size = eogllSizeOf(type) * num;
    builder->attribs[builder->numAttribs].normalized = GL_FALSE;
    builder->numAttribs++;
}

void eogllBuildAttributes(EogllAttribBuilder *builder, GLuint vao) {
    // first we need to calculate the stride
    GLsizei stride = 0;
    for (int i = 0; i < builder->numAttribs; i++) {
        stride += builder->attribs[i].size;
    }
    // now we can build the vertex array
    glBindVertexArray(vao);
    uint64_t offset = 0;
    for (int i = 0; i < builder->numAttribs; i++) {

        glVertexAttribPointer(i, builder->attribs[i].size / eogllSizeOf(builder->attribs[i].type), builder->attribs[i].type, builder->attribs[i].normalized, stride, (void*)offset);
        glEnableVertexAttribArray(i);
        offset += builder->attribs[i].size;
    }
}

EogllBufferObject eogllConstructBufferObject(void* vertices, GLsizeiptr verticesSize, void* indices, GLsizeiptr indicesSize, EogllAttribBuilder *builder, GLenum usage, GLenum indicesType) {
    EogllBufferObject bufferObject;
    bufferObject.vao = eogllGenVertexArray();
    bufferObject.vbo = eogllGenBuffer(bufferObject.vao, GL_ARRAY_BUFFER, verticesSize, vertices, usage);
    bufferObject.ebo = eogllGenBuffer(bufferObject.vao, GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, usage);
    eogllBuildAttributes(builder, bufferObject.vao);
    bufferObject.numIndices = indicesSize / eogllSizeOf(indicesType);
    bufferObject.indicesType = indicesType;
    bufferObject.hasIndices = true;
    return bufferObject;
}

EogllBufferObject eogllCreateBufferObject(unsigned int vao, unsigned int vbo, unsigned int ebo, GLsizeiptr indicesSize, GLenum indicesType) {
    EogllBufferObject bufferObject;
    bufferObject.vao = vao;
    bufferObject.vbo = vbo;
    bufferObject.ebo = ebo;
    bufferObject.numIndices = indicesSize / eogllSizeOf(indicesType);
    bufferObject.indicesType = indicesType;
    bufferObject.hasIndices = true;
    return bufferObject;
}

EogllBufferObject eogllCreateBasicBufferObject(unsigned int vao, unsigned int vbo, GLsizeiptr numVertices) {
    EogllBufferObject bufferObject;
    bufferObject.vao = vao;
    bufferObject.vbo = vbo;
    bufferObject.ebo = 0;
    bufferObject.numIndices = numVertices;
    bufferObject.indicesType = 0;
    bufferObject.hasIndices = false;
    return bufferObject;
}

void eogllDrawBufferObject(EogllBufferObject* bufferObject, GLenum mode) {
    if (!bufferObject->hasIndices) {
        EOGLL_LOG_ERROR(stderr, "Buffer object has no indices\n");
        return;
    }
    glBindVertexArray(bufferObject->vao);
    glDrawElements(mode, (GLint)bufferObject->numIndices, bufferObject->indicesType, 0);
    glBindVertexArray(0);
}

void eogllDrawBasicBufferObject(EogllBufferObject* bufferObject, GLenum mode) {
    glBindVertexArray(bufferObject->vao);
    glDrawArrays(mode, 0, (GLint)bufferObject->numIndices);
    glBindVertexArray(0);
}

void eogllBindBufferObject(EogllBufferObject* bufferObject) {
    glBindVertexArray(bufferObject->vao);
}

void eogllDeleteBufferObject(EogllBufferObject* bufferObject) {
    glDeleteVertexArrays(1, &bufferObject->vao);
    glDeleteBuffers(1, &bufferObject->vbo);
    if (bufferObject->hasIndices)
        glDeleteBuffers(1, &bufferObject->ebo);
}

void eogllSetWireframeMode(bool enable) {
    if (enable) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}



EogllTexture *eogllCreateTexture(const char *path) {
    EogllTexture *texture = (EogllTexture *) malloc(sizeof(EogllTexture));
    if (!texture) {
        EOGLL_LOG_ERROR(stderr, "Failed to allocate memory for texture\n");
        return NULL;
    }
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (!data) {
        EOGLL_LOG_ERROR(stderr, "Failed to load texture %s\n", path);
        return NULL;
    }
    EOGLL_LOG_DEBUG(stdout, "Loaded texture %s\n", path);
    EOGLL_LOG_DEBUG(stdout, "%d %d %d\n", width, height, nrChannels);
    GLint format;
    switch (nrChannels) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            EOGLL_LOG_ERROR(stderr, "Unknown number of channels %d\n", nrChannels);
            return NULL;
    }
    texture->width = width;
    texture->height = height;
    texture->channels = nrChannels;
    texture->format = format;
    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // texture->maxTextureUnits
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture->maxTextureUnits);

    stbi_image_free(data);
    return texture;
}

void eogllBindTexture(EogllTexture *texture) {
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

void eogllDeleteTexture(EogllTexture *texture) {
    glDeleteTextures(1, &texture->id);
    free(texture);
}

void eogllBindTextureUniform(EogllTexture* texture, EogllShaderProgram* shader, const char* name, unsigned int index) {
    if (index >= texture->maxTextureUnits) {
        EOGLL_LOG_ERROR(stderr, "Texture unit %d is not supported\n", index);
        return;
    }
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    eogllSetUniform1i(shader, name, (int)index);
}

EogllView eogllCreateView() {
    EogllView view;
    glm_mat4_identity(view.view);
    return view;
}

void eogllTranslateView(EogllView *view, vec3 translation) {
    glm_translate(view->view, translation);
}

void eogllTranslateView3f(EogllView *view, float x, float y, float z) {
    glm_translate(view->view, (vec3){x, y, z});
}

void eogllRotateView(EogllView *view, float angle, vec3 axis) {
    glm_rotate(view->view, glm_rad(angle), axis);
}

void eogllRotateView3f(EogllView *view, float angle, float x, float y, float z) {
    glm_rotate(view->view, glm_rad(angle), (vec3){x, y, z});
}

void eogllScaleView(EogllView *view, vec3 scale) {
    glm_scale(view->view, scale);
}

void eogllScaleView3f(EogllView *view, float x, float y, float z) {
    glm_scale(view->view, (vec3){x, y, z});
}

void eogllUpdateViewMatrix(EogllView* view, EogllShaderProgram* shader, const char* name) {
    eogllSetUniformMatrix4fv(shader, name, view->view);
}

EogllProjection eogllPerspectiveProjection(float fov, float near, float far) {
    EogllProjection projection;
    projection.fov = glm_rad(fov);
    projection.near = near;
    projection.far = far;
    return projection;
}

void eogllUpdateProjectionMatrix(EogllProjection* projection, EogllShaderProgram* shader, const char* name, uint32_t width, uint32_t height) {
    mat4 projectionMatrix;
    glm_perspective(projection->fov, (float)width / (float)height, projection->near, projection->far, projectionMatrix);
    eogllSetUniformMatrix4fv(shader, name, projectionMatrix);
}

EogllModel eogllCreateModel() {
    EogllModel model;
    glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, model.pos);
    glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, model.rot);
    glm_vec3_copy((vec3){1.0f, 1.0f, 1.0f}, model.scale);
    return model;
}

void eogllRotateModel(EogllModel *model, vec3 axis) {
    glm_vec3_add(model->rot, axis, model->rot);
}

void eogllUpdateModelMatrix(EogllModel* model, EogllShaderProgram* shader, const char* name) {
    mat4 modelMatrix;
    glm_mat4_identity(modelMatrix);
    glm_translate(modelMatrix, model->pos);
    glm_rotate(modelMatrix, glm_rad(model->rot[0]), (vec3){1.0f, 0.0f, 0.0f});
    glm_rotate(modelMatrix, glm_rad(model->rot[1]), (vec3){0.0f, 1.0f, 0.0f});
    glm_rotate(modelMatrix, glm_rad(model->rot[2]), (vec3){0.0f, 0.0f, 1.0f});
    glm_scale(modelMatrix, model->scale);
    eogllSetUniformMatrix4fv(shader, name, modelMatrix);
}

void eogllEnableDepth() {
    glEnable(GL_DEPTH_TEST);
}

void eogllEnableTransparency() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

EogllCamera eogllCreateCamera() {
    EogllCamera camera = {
            .pos = {0.0f, 0.0f, 0.0f},
            .up = {0.0f, 1.0f, 0.0f},
            .yaw = -90.0f,
            .pitch = 0.0f,
            .front = {0.0f, 0.0f, -1.0f},
            .worldUp = {0.0f, 1.0f, 0.0f}
    };
    return camera;
}

EogllView eogllCameraMatrix(EogllCamera *camera) {
    EogllView view = eogllCreateView();
    vec3 res;
    glm_vec3_add(camera->pos, camera->front, res);
    glm_lookat(camera->pos, res, camera->up, view.view);
    return view;
}

void eogllTranslateCamera3f(EogllCamera *camera, float x, float y, float z) {
    vec3 res;
    glm_vec3_add(camera->pos, (vec3) {x, y, z}, res);
    glm_vec3_copy(res, camera->pos);
}

void eogllUpdateCameraVectors(EogllCamera *camera) {
    camera->front[0] = cosf(glm_rad(camera->yaw)) * cosf(glm_rad(camera->pitch));
    camera->front[1] = sinf(glm_rad(camera->pitch));
    camera->front[2] = sinf(glm_rad(camera->yaw)) * cosf(glm_rad(camera->pitch));
    glm_vec3_normalize(camera->front);
    glm_vec3_cross(camera->front, camera->worldUp, camera->right);
    glm_vec3_normalize(camera->right);
    glm_vec3_cross(camera->right, camera->front, camera->up);
    glm_vec3_normalize(camera->up);
}

void eogllYawCamera(EogllCamera *camera, float amount) {
    camera->yaw += amount;
    if (camera->yaw > 360.0f) {
        camera->yaw -= 360.0f;
    } else if (camera->yaw < 0.0f) {
        camera->yaw += 360.0f;
    }
    eogllUpdateCameraVectors(camera);
}

void eogllPitchCamera(EogllCamera *camera, float amount) {
    camera->pitch += amount;
    if (camera->pitch > 89.0f) {
        camera->pitch = 89.0f;
    } else if (camera->pitch < -89.0f) {
        camera->pitch = -89.0f;
    }
    eogllUpdateCameraVectors(camera);
}

void eogllMoveCamera(EogllCamera *cam, EogllCameraDirection dir, float amount) {
    switch (dir) {
        case EOGLL_FORWARD: {
            vec3 res = {0.0f, 0.0f, 0.0f};
            glm_vec3_scale(cam->front, amount, res);
            glm_vec3_add(cam->pos, res, cam->pos);
        }
            break;
        case EOGLL_BACKWARD: {
            vec3 res = {0.0f, 0.0f, 0.0f};
            glm_vec3_scale(cam->front, amount, res);
            glm_vec3_sub(cam->pos, res, cam->pos);
        }
            break;
        case EOGLL_RIGHT: {
            vec3 res = {0.0f, 0.0f, 0.0f};
            glm_vec3_cross(cam->front, cam->up, res);
            glm_vec3_normalize(res);
            glm_vec3_scale(res, amount, res);
            glm_vec3_add(cam->pos, res, cam->pos);
        }
            break;
        case EOGLL_LEFT: {
            vec3 res = {0.0f, 0.0f, 0.0f};
            glm_vec3_cross(cam->front, cam->up, res);
            glm_vec3_normalize(res);
            glm_vec3_scale(res, amount, res);
            glm_vec3_sub(cam->pos, res, cam->pos);
        }
            break;
        case EOGLL_UP: {
            vec3 res = {0.0f, 0.0f, 0.0f};
            glm_vec3_scale(cam->up, amount, res);
            glm_vec3_add(cam->pos, res, cam->pos);
        }
            break;
        case EOGLL_DOWN: {
            vec3 res = {0.0f, 0.0f, 0.0f};
            glm_vec3_scale(cam->up, amount, res);
            glm_vec3_sub(cam->pos, res, cam->pos);
        }
            break;
    }

}

void eogllUpdateCameraMatrix(EogllCamera *camera, EogllShaderProgram *program, const char *name) {
    EogllView view = eogllCameraMatrix(camera);
    eogllUpdateViewMatrix(&view, program, name);
}

EogllObjectAttrs eogllCreateObjectAttrs() {
    EogllObjectAttrs attrs = {{0}, 0, eogllCreateAttribBuilder()};
    return attrs;
}

void eogllAddObjectAttr(EogllObjectAttrs* attrs, GLenum type, GLint num, EogllObjectAttrType attrType) {
    attrs->types[attrs->numTypes++] = attrType;
    eogllAddAttribute(&attrs->builder, type, num);
}

// object file data is not in the header because it is not needed outside of this file

typedef struct {
    unsigned int geomIndex;
    unsigned int normalIndex;
    unsigned int texCoordIndex;
    bool hasNormal;
    bool hasTexCoord;
} EogllObjectIndex;

typedef struct {
    unsigned int numIndices;
    EogllObjectIndex *indices;
} EogllObjectFileFace;

typedef struct {
    float x;
    float y;
    float z;
    float w;
    bool hasW;
} EogllObjectPosition;

typedef struct {
    float x;
    float y;
    float z;
} EogllObjectNormal;

typedef struct {
    float u;
    float v;
    float w;
    bool hasV;
    bool hasW;
} EogllObjectTexCoord;

typedef struct {
    unsigned int numFaces;
    EogllObjectFileFace *faces;
    // each type of vertice data is in a seperate array
    unsigned int numPositions;
    EogllObjectPosition *positions;
    unsigned int numNormals;
    EogllObjectNormal *normals;
    unsigned int numTexCoords;
    EogllObjectTexCoord *texCoords;
} EogllObjectFileData;

uint8_t eogllParseObjectFile(FILE* file, EogllObjectFileData *data) {
    char line[256];
    data->numFaces = 0;
    data->numPositions = 0;
    data->numNormals = 0;
    data->numTexCoords = 0;
    data->faces = NULL;
    data->positions = NULL;
    data->normals = NULL;
    data->texCoords = NULL;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            data->numPositions++;
        } else if (line[0] == 'v' && line[1] == 'n') {
            data->numNormals++;
        } else if (line[0] == 'v' && line[1] == 't') {
            data->numTexCoords++;
        } else if (line[0] == 'f' && line[1] == ' ') {
            data->numFaces++;
        }
    }
    data->faces = (EogllObjectFileFace*)malloc(sizeof(EogllObjectFileFace) * data->numFaces);
    data->positions = (EogllObjectPosition*)malloc(sizeof(EogllObjectPosition) * data->numPositions);
    data->normals = (EogllObjectNormal*)malloc(sizeof(EogllObjectNormal) * data->numNormals);
    data->texCoords = (EogllObjectTexCoord*)malloc(sizeof(EogllObjectTexCoord) * data->numTexCoords);
    if (!data->faces || !data->positions || !data->normals || !data->texCoords) {
        EOGLL_LOG_ERROR(stderr, "Failed to allocate memory for object file data\n");
        return EOGLL_FAILURE;
    }
    fseek(file, 0, SEEK_SET);
    unsigned int positionIndex = 0;
    unsigned int normalIndex = 0;
    unsigned int texCoordIndex = 0;
    unsigned int faceIndex = 0;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            EogllObjectPosition position;
            sscanf(line, "v %f %f %f %f", &position.x, &position.y, &position.z, &position.w);
            position.hasW = true;
            data->positions[positionIndex++] = position;
        } else if (line[0] == 'v' && line[1] == 'n') {
            EogllObjectNormal normal;
            sscanf(line, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
            data->normals[normalIndex++] = normal;
        } else if (line[0] == 'v' && line[1] == 't') {
            EogllObjectTexCoord texCoord;
            // if there is another texture coordinate, read one
            // after that, read another one if there is one
            texCoord.hasV = false;
            texCoord.hasW = false;
            int numRead = sscanf(line, "vt %f %f %f", &texCoord.u, &texCoord.v, &texCoord.w);
            if (numRead == 2) {
                texCoord.hasV = true;
            } else if (numRead == 3) {
                texCoord.hasV = true;
                texCoord.hasW = true;
            }

            data->texCoords[texCoordIndex++] = texCoord;
        } else if (line[0] == 'f' && line[1] == ' ') {
            EogllObjectFileFace face;
            face.numIndices = 0;
            // figure out how many indices there are
            for (int i = 0; i < strlen(line); i++) {
                if (line[i] == ' ') { // TODO: better way to do this?
                    face.numIndices++;
                }
            }
            face.indices = (EogllObjectIndex*)malloc(sizeof(EogllObjectIndex) * face.numIndices);
            if (!face.indices) {
                EOGLL_LOG_ERROR(stderr, "Failed to allocate memory for object file face indices\n");
                return EOGLL_FAILURE;
            }
            // parse the indices
            char *token = strtok(line, " ");
            int index = 0;
            while (token) {
                if (token[0] == 'f') {
                    token = strtok(NULL, " ");
                    continue;
                }
                EogllObjectIndex objectIndex;
                sscanf(token, "%d/%d/%d", &objectIndex.geomIndex, &objectIndex.texCoordIndex, &objectIndex.normalIndex);
                objectIndex.hasNormal = true;
                objectIndex.hasTexCoord = true;
                face.indices[index++] = objectIndex;
                token = strtok(NULL, " ");
            }
            data->faces[faceIndex++] = face;
        }

    }
    return EOGLL_SUCCESS;
}

void eogllTriangulateObjectFileData(EogllObjectFileData *data) {
    // TODO
}

uint8_t eogllObjectFileDataToVertices(EogllObjectFileData *data, EogllObjectAttrs attrs, float** vertices, uint32_t* numVertices, unsigned int** indices, uint32_t* numIndices) {
    // since at the moment, our indices have multiple attributes, we cannot index it easily.
    // The unoptimized easiest way to do this is to not use indices at all and just duplicate vertices
    // one thing we can do is to create a map of indices to vertices, and then use that to create the indices (maps are hard in C)
    // another is to do the first method, but then optimize it by removing duplicate vertices and using indices to reference them

    // first we need to calculate the number of vertices
    *numVertices = 0;
    for (int i = 0; i < data->numFaces; i++) {
        *numVertices += data->faces[i].numIndices;
    }
    *numIndices = *numVertices;

    unsigned int numVerts = 0;
    for (int i = 0; i < attrs.numTypes; i++) {
        numVerts += attrs.builder.attribs[i].size / eogllSizeOf(attrs.builder.attribs[i].type);
    }

    *vertices = (float*)malloc(sizeof(float) * *numVertices * numVerts);
    *indices = (unsigned int*)malloc(sizeof(unsigned int) * *numIndices);
    for (int i = 0; i < *numIndices; i++) {
        (*indices)[i] = i;
    }
    unsigned int vertexIndex = 0;
    unsigned int max = *numVertices * numVerts;

    for (int i = 0; i < data->numFaces; i++) {
        for (int j = 0; j < data->faces[i].numIndices; j++) {
            EogllObjectIndex index = data->faces[i].indices[j];
            EogllObjectPosition position = data->positions[index.geomIndex - 1];
            EogllObjectNormal normal = data->normals[index.normalIndex - 1];
            EogllObjectTexCoord texCoord = data->texCoords[index.texCoordIndex - 1];
            for (int k = 0; k < attrs.numTypes; k++) {
                if (vertexIndex >= max) {
                    EOGLL_LOG_ERROR(stderr, "Vertex index %d is out of bounds\n", vertexIndex);
                    return EOGLL_FAILURE;
                }
                switch (attrs.types[k]) {
                    case EOGLL_ATTR_POSITION:
                        (*vertices)[vertexIndex++] = position.x;
                        (*vertices)[vertexIndex++] = position.y;
                        (*vertices)[vertexIndex++] = position.z;
                        break;
                    case EOGLL_ATTR_NORMAL:
                        (*vertices)[vertexIndex++] = normal.x;
                        (*vertices)[vertexIndex++] = normal.y;
                        (*vertices)[vertexIndex++] = normal.z;
                        break;
                    case EOGLL_ATTR_TEXTURE:
                        (*vertices)[vertexIndex++] = texCoord.u;
                        if (texCoord.hasV) {
                            (*vertices)[vertexIndex++] = texCoord.v;
                        }
                        if (texCoord.hasW) {
                            (*vertices)[vertexIndex++] = texCoord.w;
                        }
                        break;
                    default:
                        EOGLL_LOG_WARN(stderr, "Unknown attribute type %d\n", attrs.types[k]);
                        break;
                }
            }
        }
    }
    return EOGLL_SUCCESS;
}


void eogllPrintObjectFileData(EogllObjectFileData* data) {
    EOGLL_LOG_INFO(stdout, "Object file data:\n");
    EOGLL_LOG_INFO(stdout, "Positions:\n");
    for (int i = 0; i < data->numPositions; i++) {
        EOGLL_LOG_INFO(stdout, "%f %f %f %f\n", data->positions[i].x, data->positions[i].y, data->positions[i].z, data->positions[i].w);
    }
    EOGLL_LOG_INFO(stdout, "Normals:\n");
    for (int i = 0; i < data->numNormals; i++) {
        EOGLL_LOG_INFO(stdout, "%f %f %f\n", data->normals[i].x, data->normals[i].y, data->normals[i].z);
    }
    EOGLL_LOG_INFO(stdout, "Texture coordinates:\n");
    for (int i = 0; i < data->numTexCoords; i++) {
        EOGLL_LOG_INFO(stdout, "%f %f %f\n", data->texCoords[i].u, data->texCoords[i].v, data->texCoords[i].w);
    }
    EOGLL_LOG_INFO(stdout, "Faces:\n");
    for (int i = 0; i < data->numFaces; i++) {
        EOGLL_LOG_INFO(stdout, "Face %d:\n", i);
        for (int j = 0; j < data->faces[i].numIndices; j++) {
            EOGLL_LOG_INFO(stdout, "%d/%d/%d\n", data->faces[i].indices[j].geomIndex, data->faces[i].indices[j].texCoordIndex, data->faces[i].indices[j].normalIndex);
        }
        EOGLL_LOG_INFO(stdout, "\n");
    }
}


uint8_t eogllLoadObjectFile(const char* path, EogllObjectAttrs attrs, float** vertices, uint32_t* numVertices, unsigned int** indices, uint32_t* numIndices) {
    FILE* file = fopen(path, "r");
    if (!file) {
        EOGLL_LOG_ERROR(stderr, "Failed to open file %s\n", path);
        return EOGLL_FAILURE;
    }
    EogllObjectFileData data;
    if (eogllParseObjectFile(file, &data) != EOGLL_SUCCESS) {
        EOGLL_LOG_ERROR(stderr, "Failed to parse object file %s\n", path);
        return EOGLL_FAILURE;
    }

    eogllPrintObjectFileData(&data);

//    eogllTriangulateObjectFileData(&data); // TODO: implement this

    if (eogllObjectFileDataToVertices(&data, attrs, vertices, numVertices, indices, numIndices) != EOGLL_SUCCESS) {
        EOGLL_LOG_ERROR(stderr, "Failed to convert object file data to vertices\n");
        return EOGLL_FAILURE;
    }
//    eogllDeleteObjectFileData(&data);
    // TODO

    return EOGLL_SUCCESS;

}

EogllBufferObject eogllLoadBufferObject(const char* path, EogllObjectAttrs attrs, GLenum usage) {
    float* vertices;
    unsigned int* indices;
    uint32_t numVertices;
    uint32_t numIndices;
    if (eogllLoadObjectFile(path, attrs, &vertices, &numVertices, &indices, &numIndices) != EOGLL_SUCCESS) {
        EOGLL_LOG_ERROR(stderr, "Failed to load object %s\n", path);
        return (EogllBufferObject){0};
    }

    unsigned int numVerts = 0;
    for (int i = 0; i < attrs.numTypes; i++) {
        numVerts += attrs.builder.attribs[i].size / eogllSizeOf(attrs.builder.attribs[i].type);
    }
    // print out all vertices
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVerts; j++) {
            printf("%f ", vertices[i * numVerts + j]);
        }
        printf("\n");
    }
    unsigned int vao = eogllGenVertexArray();
    unsigned int vbo = eogllGenBuffer(vao, GL_ARRAY_BUFFER, (unsigned int)sizeof(float) * numVertices * numVerts, vertices, usage);
    unsigned int ebo = eogllGenBuffer(vao, GL_ELEMENT_ARRAY_BUFFER, (unsigned int)sizeof(unsigned int) * numIndices, indices, usage);
    eogllBuildAttributes(&attrs.builder, vao);
    free(vertices);
    free(indices);
    return eogllCreateBufferObject(vao, vbo, ebo, (unsigned int)sizeof(unsigned int) * numIndices, GL_UNSIGNED_INT);
}