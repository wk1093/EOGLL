#include "eogll.h"

#include <stdlib.h>

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
    window->mousex = 0;
    window->mousey = 0;
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
    EogllShaderProgram* shader = (EogllShaderProgram*)malloc(sizeof(EogllShaderProgram));

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
