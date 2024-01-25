/*
 * EOGLL - Easy OpenGL Library
 * Naming convention:
 * DEFINES: CAPITAL_CASE: EOGLL_*
 * TYPES: PascalCase: Eogll*
 * Functions: camelCase: eogll*
 * Enums: CAPITAL_CASE: EOGLL_*
 */


#pragma once
#ifndef _EOGLL_H_
#define _EOGLL_H_

#define EOGLL_VERSION_MAJOR 0
#define EOGLL_VERSION_MINOR 2
#define EOGLL_VERSION_PATCH 5

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <hedley.h>

#include <stb.h>

#include <cglm/cglm.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

#define EOGLL_KEY_UNKNOWN            -1

/* Printable keys */
#define EOGLL_KEY_SPACE              32
#define EOGLL_KEY_APOSTROPHE         39  /* ' */
#define EOGLL_KEY_COMMA              44  /* , */
#define EOGLL_KEY_MINUS              45  /* - */
#define EOGLL_KEY_PERIOD             46  /* . */
#define EOGLL_KEY_SLASH              47  /* / */
#define EOGLL_KEY_0                  48
#define EOGLL_KEY_1                  49
#define EOGLL_KEY_2                  50
#define EOGLL_KEY_3                  51
#define EOGLL_KEY_4                  52
#define EOGLL_KEY_5                  53
#define EOGLL_KEY_6                  54
#define EOGLL_KEY_7                  55
#define EOGLL_KEY_8                  56
#define EOGLL_KEY_9                  57
#define EOGLL_KEY_SEMICOLON          59  /* ; */
#define EOGLL_KEY_EQUAL              61  /* = */
#define EOGLL_KEY_A                  65
#define EOGLL_KEY_B                  66
#define EOGLL_KEY_C                  67
#define EOGLL_KEY_D                  68
#define EOGLL_KEY_E                  69
#define EOGLL_KEY_F                  70
#define EOGLL_KEY_G                  71
#define EOGLL_KEY_H                  72
#define EOGLL_KEY_I                  73
#define EOGLL_KEY_J                  74
#define EOGLL_KEY_K                  75
#define EOGLL_KEY_L                  76
#define EOGLL_KEY_M                  77
#define EOGLL_KEY_N                  78
#define EOGLL_KEY_O                  79
#define EOGLL_KEY_P                  80
#define EOGLL_KEY_Q                  81
#define EOGLL_KEY_R                  82
#define EOGLL_KEY_S                  83
#define EOGLL_KEY_T                  84
#define EOGLL_KEY_U                  85
#define EOGLL_KEY_V                  86
#define EOGLL_KEY_W                  87
#define EOGLL_KEY_X                  88
#define EOGLL_KEY_Y                  89
#define EOGLL_KEY_Z                  90
#define EOGLL_KEY_LEFT_BRACKET       91  /* [ */
#define EOGLL_KEY_BACKSLASH          92  /* \ */
#define EOGLL_KEY_RIGHT_BRACKET      93  /* ] */
#define EOGLL_KEY_GRAVE_ACCENT       96  /* ` */
#define EOGLL_KEY_WORLD_1            161 /* non-US #1 */
#define EOGLL_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define EOGLL_KEY_ESCAPE             256
#define EOGLL_KEY_ENTER              257
#define EOGLL_KEY_TAB                258
#define EOGLL_KEY_BACKSPACE          259
#define EOGLL_KEY_INSERT             260
#define EOGLL_KEY_DELETE             261
#define EOGLL_KEY_RIGHT              262
#define EOGLL_KEY_LEFT               263
#define EOGLL_KEY_DOWN               264
#define EOGLL_KEY_UP                 265
#define EOGLL_KEY_PAGE_UP            266
#define EOGLL_KEY_PAGE_DOWN          267
#define EOGLL_KEY_HOME               268
#define EOGLL_KEY_END                269
#define EOGLL_KEY_CAPS_LOCK          280
#define EOGLL_KEY_SCROLL_LOCK        281
#define EOGLL_KEY_NUM_LOCK           282
#define EOGLL_KEY_PRINT_SCREEN       283
#define EOGLL_KEY_PAUSE              284
#define EOGLL_KEY_F1                 290
#define EOGLL_KEY_F2                 291
#define EOGLL_KEY_F3                 292
#define EOGLL_KEY_F4                 293
#define EOGLL_KEY_F5                 294
#define EOGLL_KEY_F6                 295
#define EOGLL_KEY_F7                 296
#define EOGLL_KEY_F8                 297
#define EOGLL_KEY_F9                 298
#define EOGLL_KEY_F10                299
#define EOGLL_KEY_F11                300
#define EOGLL_KEY_F12                301
#define EOGLL_KEY_F13                302
#define EOGLL_KEY_F14                303
#define EOGLL_KEY_F15                304
#define EOGLL_KEY_F16                305
#define EOGLL_KEY_F17                306
#define EOGLL_KEY_F18                307
#define EOGLL_KEY_F19                308
#define EOGLL_KEY_F20                309
#define EOGLL_KEY_F21                310
#define EOGLL_KEY_F22                311
#define EOGLL_KEY_F23                312
#define EOGLL_KEY_F24                313
#define EOGLL_KEY_F25                314
#define EOGLL_KEY_KP_0               320
#define EOGLL_KEY_KP_1               321
#define EOGLL_KEY_KP_2               322
#define EOGLL_KEY_KP_3               323
#define EOGLL_KEY_KP_4               324
#define EOGLL_KEY_KP_5               325
#define EOGLL_KEY_KP_6               326
#define EOGLL_KEY_KP_7               327
#define EOGLL_KEY_KP_8               328
#define EOGLL_KEY_KP_9               329
#define EOGLL_KEY_KP_DECIMAL         330
#define EOGLL_KEY_KP_DIVIDE          331
#define EOGLL_KEY_KP_MULTIPLY        332
#define EOGLL_KEY_KP_SUBTRACT        333
#define EOGLL_KEY_KP_ADD             334
#define EOGLL_KEY_KP_ENTER           335
#define EOGLL_KEY_KP_EQUAL           336
#define EOGLL_KEY_LEFT_SHIFT         340
#define EOGLL_KEY_LEFT_CONTROL       341
#define EOGLL_KEY_LEFT_ALT           342
#define EOGLL_KEY_LEFT_SUPER         343
#define EOGLL_KEY_RIGHT_SHIFT        344
#define EOGLL_KEY_RIGHT_CONTROL      345
#define EOGLL_KEY_RIGHT_ALT          346
#define EOGLL_KEY_RIGHT_SUPER        347
#define EOGLL_KEY_MENU               348

#define EOGLL_KEY_LAST               EOGLL_KEY_MENU


/* Mouse buttons */
#define EOGLL_MOUSE_BUTTON_1         0
#define EOGLL_MOUSE_BUTTON_2         1
#define EOGLL_MOUSE_BUTTON_3         2
#define EOGLL_MOUSE_BUTTON_4         3
#define EOGLL_MOUSE_BUTTON_5         4
#define EOGLL_MOUSE_BUTTON_6         5
#define EOGLL_MOUSE_BUTTON_7         6
#define EOGLL_MOUSE_BUTTON_8         7
#define EOGLL_MOUSE_BUTTON_LAST      EOGLL_MOUSE_BUTTON_8
#define EOGLL_MOUSE_BUTTON_LEFT      EOGLL_MOUSE_BUTTON_1
#define EOGLL_MOUSE_BUTTON_RIGHT     EOGLL_MOUSE_BUTTON_2
#define EOGLL_MOUSE_BUTTON_MIDDLE    EOGLL_MOUSE_BUTTON_3


#define EOGLL_RELEASE                0

#define EOGLL_PRESS                  1

#define EOGLL_CURSOR_NORMAL          0x00034001
#define EOGLL_CURSOR_HIDDEN          0x00034002
#define EOGLL_CURSOR_DISABLED        0x00034003

#define EOGLL_SUCCESS 0
#define EOGLL_FAILURE 1

#define EOGLL_NO_DISCARD HEDLEY_WARN_UNUSED_RESULT

#define EOGLL_VERSION (EOGLL_VERSION_MAJOR * 10000 + EOGLL_VERSION_MINOR * 100 + EOGLL_VERSION_PATCH)

#define EOGLL_DECL_FUNC
#define EOGLL_DECL_STRUCT
#define EOGLL_DECL_FUNC_ND EOGLL_DECL_FUNC EOGLL_NO_DISCARD
#define EOGLL_DECL_VAR
#define EOGLL_DECL_ENUM


typedef EOGLL_DECL_ENUM enum {
    EOGLL_LOG_LEVEL_TRACE,
    EOGLL_LOG_LEVEL_DEBUG,
    EOGLL_LOG_LEVEL_INFO,
    EOGLL_LOG_LEVEL_WARN,
    EOGLL_LOG_LEVEL_ERROR,
    EOGLL_LOG_LEVEL_FATAL
} EogllLogLevel;

#define EOGLL_LOG(stream, level, message, ...) \
    { \
        switch (level) { \
            case EOGLL_LOG_LEVEL_TRACE: \
                fprintf(stream, "[TRACE %s] ", __FUNCTION__); \
                break; \
            case EOGLL_LOG_LEVEL_DEBUG: \
                fprintf(stream, "[DEBUG %s] ", __FUNCTION__); \
                break; \
            case EOGLL_LOG_LEVEL_INFO: \
                fprintf(stream, "[INFO %s] ", __FUNCTION__); \
                break; \
            case EOGLL_LOG_LEVEL_WARN: \
                fprintf(stream, "[WARN %s] ", __FUNCTION__); \
                break; \
            case EOGLL_LOG_LEVEL_ERROR: \
                fprintf(stream, "[ERROR %s] ", __FUNCTION__); \
                break; \
            case EOGLL_LOG_LEVEL_FATAL: \
                fprintf(stream, "[FATAL %s] ", __FUNCTION__); \
                break;                         \
            default:                           \
                fprintf(stream, "[UNKNOWN %s:%d] ",  __FILE__, __LINE__); \
                break;\
        } \
        fprintf(stream, message, ##__VA_ARGS__); \
    }

#define EOGLL_LOG_POS(stream, level, message, ...) \
    { \
        switch (level) { \
            case EOGLL_LOG_LEVEL_TRACE: \
                fprintf(stream, "[TRACE %s:%d] ", __FILE__, __LINE__); \
                break; \
            case EOGLL_LOG_LEVEL_DEBUG: \
                fprintf(stream, "[DEBUG %s:%d] ", __FILE__, __LINE__); \
                break; \
            case EOGLL_LOG_LEVEL_INFO: \
                fprintf(stream, "[INFO %s:%d] ", __FILE__, __LINE__); \
                break; \
            case EOGLL_LOG_LEVEL_WARN: \
                fprintf(stream, "[WARN %s:%d] ", __FILE__, __LINE__); \
                break; \
            case EOGLL_LOG_LEVEL_ERROR: \
                fprintf(stream, "[ERROR %s:%d] ", __FILE__, __LINE__); \
                break; \
            case EOGLL_LOG_LEVEL_FATAL: \
                fprintf(stream, "[FATAL %s:%d] ", __FILE__, __LINE__); \
                break;                         \
            default:                           \
                fprintf(stream, "[UNKNOWN %s:%d] ",  __FILE__, __LINE__); \
                break;\
        } \
        fprintf(stream, message, ##__VA_ARGS__); \
    }

#ifdef EOGLL_DEBUG
#define EOGLL_LOG_DEBUG(stream, message, ...) EOGLL_LOG(stream, EOGLL_LOG_LEVEL_DEBUG, message, ##__VA_ARGS__)
#define EOGLL_LOG_DEBUG_POS(stream, message, ...) EOGLL_LOG_POS(stream, EOGLL_LOG_LEVEL_DEBUG, message, ##__VA_ARGS__)
#else
#define EOGLL_LOG_DEBUG(stream, message, ...)
#define EOGLL_LOG_DEBUG_POS(stream, message, ...)
#endif

#ifdef EOGLL_TRACE
#define EOGLL_LOG_TRACE(stream, message, ...) EOGLL_LOG(stream, EOGLL_LOG_LEVEL_TRACE, message, ##__VA_ARGS__)
#define EOGLL_LOG_TRACE_POS(stream, message, ...) EOGLL_LOG_POS(stream, EOGLL_LOG_LEVEL_TRACE, message, ##__VA_ARGS__)
#else
#define EOGLL_LOG_TRACE(stream, message, ...)
#define EOGLL_LOG_TRACE_POS(stream, message, ...)
#endif

#define EOGLL_LOG_INFO(stream, message, ...) EOGLL_LOG(stream, EOGLL_LOG_LEVEL_INFO, message, ##__VA_ARGS__)
#define EOGLL_LOG_INFO_POS(stream, message, ...) EOGLL_LOG_POS(stream, EOGLL_LOG_LEVEL_INFO, message, ##__VA_ARGS__)
#define EOGLL_LOG_WARN(stream, message, ...) EOGLL_LOG(stream, EOGLL_LOG_LEVEL_WARN, message, ##__VA_ARGS__)
#define EOGLL_LOG_WARN_POS(stream, message, ...) EOGLL_LOG_POS(stream, EOGLL_LOG_LEVEL_WARN, message, ##__VA_ARGS__)
#define EOGLL_LOG_ERROR(stream, message, ...) EOGLL_LOG(stream, EOGLL_LOG_LEVEL_ERROR, message, ##__VA_ARGS__)
#define EOGLL_LOG_ERROR_POS(stream, message, ...) EOGLL_LOG_POS(stream, EOGLL_LOG_LEVEL_ERROR, message, ##__VA_ARGS__)
#define EOGLL_LOG_FATAL(stream, message, ...) EOGLL_LOG(stream, EOGLL_LOG_LEVEL_FATAL, message, ##__VA_ARGS__)
#define EOGLL_LOG_FATAL_POS(stream, message, ...) EOGLL_LOG_POS(stream, EOGLL_LOG_LEVEL_FATAL, message, ##__VA_ARGS__)



EOGLL_DECL_FUNC_ND const char* eogllGetVersionString();


EOGLL_DECL_FUNC_ND uint8_t eogllInit();
EOGLL_DECL_FUNC void eogllTerminate();

EOGLL_DECL_FUNC_ND char* eogllReadFile(const char* path);

typedef EOGLL_DECL_STRUCT struct EogllWindow {
    GLFWwindow* window;
    uint32_t width;
    uint32_t height;

    bool press[EOGLL_KEY_LAST + 1];
    bool release[EOGLL_KEY_LAST + 1];
    bool isDown[EOGLL_KEY_LAST + 1];

    bool mousePress[EOGLL_MOUSE_BUTTON_LAST + 1];
    bool mouseRelease[EOGLL_MOUSE_BUTTON_LAST + 1];
    bool mouseIsDown[EOGLL_MOUSE_BUTTON_LAST + 1];

    double mousex;
    double mousedx;
    double mousey;
    double mousedy;
    double mouseScrollx;
    double mouseScrolly;

    bool focused;
} EogllWindow;

typedef EOGLL_DECL_STRUCT struct {
    bool resizable;
    bool decorated;
    bool floating;
    bool maximized;
    bool visible;
    bool focused;
} EogllWindowHints;

EOGLL_DECL_FUNC_ND EogllWindowHints eogllCreateWindowHints(bool resizable, bool decorated, bool floating, bool maximized, bool visible, bool focused);
EOGLL_DECL_FUNC_ND EogllWindowHints eogllDefaultWindowHints();

EOGLL_DECL_FUNC_ND EogllWindow* eogllCreateWindow(uint32_t width, uint32_t height, const char* title, EogllWindowHints hints);
EOGLL_DECL_FUNC_ND bool eogllWindowShouldClose(EogllWindow* window);
EOGLL_DECL_FUNC void eogllSetWindowShouldClose(EogllWindow* window, bool shouldClose);
EOGLL_DECL_FUNC void eogllPollEvents(EogllWindow* window);
EOGLL_DECL_FUNC void eogllSwapBuffers(EogllWindow* window);
EOGLL_DECL_FUNC void eogllDestroyWindow(EogllWindow* window);
EOGLL_DECL_FUNC_ND bool eogllGetKeyPress(EogllWindow* window, int key);
EOGLL_DECL_FUNC_ND bool eogllGetKeyRelease(EogllWindow* window, int key);
EOGLL_DECL_FUNC_ND bool eogllGetKeyIsDown(EogllWindow* window, int key);
EOGLL_DECL_FUNC_ND bool eogllGetMousePress(EogllWindow* window, int button);
EOGLL_DECL_FUNC_ND bool eogllGetMouseRelease(EogllWindow* window, int button);
EOGLL_DECL_FUNC_ND bool eogllGetMouseIsDown(EogllWindow* window, int button);
EOGLL_DECL_FUNC void eogllGetMousePos(EogllWindow* window, double* xpos, double* ypos);
EOGLL_DECL_FUNC void eogllSetMousePos(EogllWindow* window, double xpos, double ypos);
EOGLL_DECL_FUNC void eogllGetMouseScroll(EogllWindow* window, double* xscroll, double* yscroll);
EOGLL_DECL_FUNC void eogllGetWindowSize(EogllWindow* window, uint32_t* width, uint32_t* height);
EOGLL_DECL_FUNC void eogllSetWindowSize(EogllWindow* window, uint32_t width, uint32_t height);
EOGLL_DECL_FUNC void eogllGetWindowPos(EogllWindow* window, int* x, int* y);
EOGLL_DECL_FUNC void eogllSetWindowPos(EogllWindow* window, int x, int y);
EOGLL_DECL_FUNC void eogllGetCursorPos(EogllWindow* window, double* xpos, double* ypos);
EOGLL_DECL_FUNC void eogllSetCursorPos(EogllWindow* window, double xpos, double ypos);
EOGLL_DECL_FUNC void eogllCenterWindow(EogllWindow* window);
EOGLL_DECL_FUNC_ND double eogllGetTime();
EOGLL_DECL_FUNC void eogllSetCursorMode(EogllWindow* window, int mode);

typedef EOGLL_DECL_STRUCT struct {
    float r;
    float g;
    float b;
    float a;
} EogllColor;

EOGLL_DECL_FUNC void eogllClearColor(EogllColor color);
EOGLL_DECL_FUNC_ND EogllColor eogllCreateColor(float r, float g, float b, float a);
EOGLL_DECL_FUNC_ND bool eogllColorEqual(EogllColor a, EogllColor b);

EOGLL_DECL_VAR extern EogllColor EOGLL_COLOR_BLACK;
EOGLL_DECL_VAR extern EogllColor EOGLL_COLOR_WHITE;
EOGLL_DECL_VAR extern EogllColor EOGLL_COLOR_RED;
EOGLL_DECL_VAR extern EogllColor EOGLL_COLOR_GREEN;
EOGLL_DECL_VAR extern EogllColor EOGLL_COLOR_BLUE;
EOGLL_DECL_VAR extern EogllColor EOGLL_COLOR_YELLOW;
EOGLL_DECL_VAR extern EogllColor EOGLL_COLOR_MAGENTA;
EOGLL_DECL_VAR extern EogllColor EOGLL_COLOR_CYAN;
EOGLL_DECL_VAR extern EogllColor EOGLL_COLOR_TRANSPARENT;


typedef EOGLL_DECL_STRUCT struct {
    unsigned int id;
} EogllShaderProgram;

EOGLL_DECL_FUNC_ND EogllShaderProgram* eogllLinkProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
EOGLL_DECL_FUNC_ND EogllShaderProgram* eogllLinkProgramFromFile(const char* vertexShaderPath, const char* fragmentShaderPath);
EOGLL_DECL_FUNC void eogllDeleteProgram(EogllShaderProgram* shader);
EOGLL_DECL_FUNC void eogllUseProgram(EogllShaderProgram* shader);
EOGLL_DECL_FUNC void eogllSetUniformMatrix4fv(EogllShaderProgram* shader, const char* name, mat4 matrix);
EOGLL_DECL_FUNC void eogllSetUniform4f(EogllShaderProgram* shader, const char* name, float x, float y, float z, float w);
EOGLL_DECL_FUNC void eogllSetUniform4fv(EogllShaderProgram* shader, const char* name, vec4 vector);
EOGLL_DECL_FUNC void eogllSetUniform3f(EogllShaderProgram* shader, const char* name, float x, float y, float z);
EOGLL_DECL_FUNC void eogllSetUniform3fv(EogllShaderProgram* shader, const char* name, vec3 vector);
EOGLL_DECL_FUNC void eogllSetUniform2f(EogllShaderProgram* shader, const char* name, float x, float y);
EOGLL_DECL_FUNC void eogllSetUniform2fv(EogllShaderProgram* shader, const char* name, vec2 vector);
EOGLL_DECL_FUNC void eogllSetUniform1f(EogllShaderProgram* shader, const char* name, float x);
EOGLL_DECL_FUNC void eogllSetUniform1fv(EogllShaderProgram* shader, const char* name, float* vector, GLsizei count);
EOGLL_DECL_FUNC void eogllSetUniform1i(EogllShaderProgram* shader, const char* name, int x);
EOGLL_DECL_FUNC void eogllSetUniform1iv(EogllShaderProgram* shader, const char* name, int* vector, GLsizei count);
EOGLL_DECL_FUNC void eogllSetUniform1ui(EogllShaderProgram* shader, const char* name, unsigned int x);
EOGLL_DECL_FUNC void eogllSetUniform1uiv(EogllShaderProgram* shader, const char* name, unsigned int* vector, GLsizei count);
EOGLL_DECL_FUNC void eogllSetUniformMatrix3fv(EogllShaderProgram* shader, const char* name, mat3 matrix);
EOGLL_DECL_FUNC void eogllSetUniformMatrix2fv(EogllShaderProgram* shader, const char* name, mat2 matrix);



EOGLL_DECL_FUNC_ND unsigned int eogllGenVertexArray();
// passing vao to eogllGenBuffer will ensure that the correct vao is bound, and it will unbind it when it's done, this help track down bugs later on
// if we do a function that requires a vao to be bound, but it's not bound right before, there might be an unnoticed bug later,
// but if we always unbind it when we're done, we can be sure that that bug will appear right away instead of later on in a distant universe
EOGLL_DECL_FUNC_ND unsigned int eogllGenBuffer(unsigned int vao, GLenum mode, GLsizeiptr count, const void* indices, GLenum usage);


typedef EOGLL_DECL_STRUCT struct {
    GLenum type;
    GLint size;
    GLboolean normalized;
} EogllVertAttribData;

typedef EOGLL_DECL_STRUCT struct {
    EogllVertAttribData attribs[16]; // almost certainly not going to use more than 16. most high end GPUs only support 16 anyway
    GLuint numAttribs;
} EogllAttribBuilder;

EOGLL_DECL_FUNC_ND EogllAttribBuilder eogllCreateAttribBuilder();
EOGLL_DECL_FUNC_ND GLint eogllSizeOf(GLenum type);
EOGLL_DECL_FUNC void eogllAddAttribute(EogllAttribBuilder *builder, GLenum type, GLint num);
EOGLL_DECL_FUNC void eogllBuildAttributes(EogllAttribBuilder *builder, GLuint vao);

typedef EOGLL_DECL_STRUCT struct {
    unsigned int vao, vbo, ebo;
    uint32_t numIndices;
    GLenum indicesType;
    bool hasIndices;
} EogllBufferObject;


EOGLL_DECL_FUNC_ND HEDLEY_DEPRECATED_FOR(2.5, eogllCreateBufferObject) EogllBufferObject eogllConstructBufferObject(void* vertices, GLsizeiptr verticesSize, void* indices, GLsizeiptr indicesSize, EogllAttribBuilder *builder, GLenum usage, GLenum indicesType);
EOGLL_DECL_FUNC_ND EogllBufferObject eogllCreateBufferObject(unsigned int vao, unsigned int vbo, unsigned int ebo, GLsizeiptr indicesSize, GLenum indicesType);
EOGLL_DECL_FUNC_ND EogllBufferObject eogllCreateBasicBufferObject(unsigned int vao, unsigned int vbo, GLsizeiptr numVertices);
EOGLL_DECL_FUNC void eogllDrawBufferObject(EogllBufferObject* bufferObject, GLenum mode);
EOGLL_DECL_FUNC void eogllDrawBasicBufferObject(EogllBufferObject* bufferObject, GLenum mode);
EOGLL_DECL_FUNC void eogllBindBufferObject(EogllBufferObject* bufferObject);
EOGLL_DECL_FUNC void eogllDeleteBufferObject(EogllBufferObject* bufferObject);

EOGLL_DECL_FUNC void eogllSetWireframeMode(bool enable);

typedef EOGLL_DECL_STRUCT struct {
    unsigned int id;
    int width;
    int height;
    int channels;
    GLint format;
    int maxTextureUnits;
} EogllTexture;


EOGLL_DECL_FUNC_ND EogllTexture* eogllCreateTexture(const char* path);
EOGLL_DECL_FUNC void eogllBindTexture(EogllTexture* texture);
EOGLL_DECL_FUNC void eogllDeleteTexture(EogllTexture* texture);

EOGLL_DECL_FUNC void eogllBindTextureUniform(EogllTexture* texture, EogllShaderProgram* shader, const char* name, unsigned int index);

// EogllView, EogllProjection, EogllModel
typedef EOGLL_DECL_STRUCT struct { // basically a camera
    mat4 view;
} EogllView;

EOGLL_DECL_FUNC_ND EogllView eogllCreateView();
EOGLL_DECL_FUNC void eogllTranslateView3f(EogllView* view, float x, float y, float z);
EOGLL_DECL_FUNC void eogllTranslateView(EogllView* view, vec3 translation);
EOGLL_DECL_FUNC void eogllRotateView3f(EogllView* view, float angle, float x, float y, float z);
EOGLL_DECL_FUNC void eogllRotateView(EogllView* view, float angle, vec3 axis);
EOGLL_DECL_FUNC void eogllScaleView3f(EogllView* view, float x, float y, float z);
EOGLL_DECL_FUNC void eogllScaleView(EogllView* view, vec3 scale);
EOGLL_DECL_FUNC void eogllUpdateViewMatrix(EogllView* view, EogllShaderProgram* shader, const char* name);

typedef EOGLL_DECL_STRUCT struct {
    float fov;
    float near;
    float far;
} EogllProjection;

EOGLL_DECL_FUNC_ND EogllProjection eogllPerspectiveProjection(float fov, float near, float far);
EOGLL_DECL_FUNC void eogllUpdateProjectionMatrix(EogllProjection* projection, EogllShaderProgram* shader, const char* name, uint32_t width, uint32_t height);

typedef EOGLL_DECL_STRUCT struct {
    vec3 pos;
    vec3 rot;
    vec3 scale;
} EogllModel;

EOGLL_DECL_FUNC_ND EogllModel eogllCreateModel();
EOGLL_DECL_FUNC void eogllRotateModel(EogllModel* model, vec3 axis);
EOGLL_DECL_FUNC void eogllUpdateModelMatrix(EogllModel* model, EogllShaderProgram* shader, const char* name);

EOGLL_DECL_FUNC void eogllEnableDepth();
EOGLL_DECL_FUNC void eogllEnableTransparency();

typedef EOGLL_DECL_STRUCT struct {
    vec3 pos;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 worldUp;

    float yaw;
    float pitch;
} EogllCamera;

EOGLL_DECL_FUNC_ND EogllCamera eogllCreateCamera();

EOGLL_DECL_FUNC_ND EogllView eogllCameraMatrix(EogllCamera* camera);

EOGLL_DECL_FUNC void eogllTranslateCamera3f(EogllCamera* camera, float x, float y, float z);

EOGLL_DECL_FUNC void eogllUpdateCameraVectors(EogllCamera* camera);

EOGLL_DECL_FUNC void eogllYawCamera(EogllCamera* camera, float amount);

EOGLL_DECL_FUNC void eogllPitchCamera(EogllCamera* camera, float amount);

typedef EOGLL_DECL_ENUM enum {
    EOGLL_FORWARD,
    EOGLL_BACKWARD,
    EOGLL_LEFT,
    EOGLL_RIGHT,
    EOGLL_UP,
    EOGLL_DOWN
} EogllCameraDirection;

EOGLL_DECL_FUNC void eogllMoveCamera(EogllCamera* cam, EogllCameraDirection dir, float amount);

EOGLL_DECL_FUNC void eogllUpdateCameraMatrix(EogllCamera* camera, EogllShaderProgram* program, const char* name);

// Object loading stuff

// EogllObjectAttrs is very similar to EogllAttribBuilder, but it also stores the type of the attributes (where it comes from in the obj file)

//EogllObjectAttrs objMode = eogllCreateObjectAttrs();
//eogllAddObjectAttr(&objMode, GL_FLOAT, 3, EOGLL_ATTR_POSITION);
//eogllAddObjectAttr(&objMode, GL_FLOAT, 2, EOGLL_ATTR_TEXTURE);
//EogllBufferObject bufferObject = eogllBufferObjectLoad("resources/models/cube.obj", objMode);

typedef EOGLL_DECL_ENUM enum {
    EOGLL_ATTR_NONE,
    EOGLL_ATTR_POSITION,
    EOGLL_ATTR_TEXTURE,
    EOGLL_ATTR_NORMAL
} EogllObjectAttrType;

typedef EOGLL_DECL_STRUCT struct {
    EogllObjectAttrType types[8]; // probably will only use 3, but maybe there is more to the obj format that I don't know about
    uint32_t numTypes;
    EogllAttribBuilder builder;
} EogllObjectAttrs;

EOGLL_DECL_FUNC_ND EogllObjectAttrs eogllCreateObjectAttrs();
EOGLL_DECL_FUNC void eogllAddObjectAttr(EogllObjectAttrs* attrs, GLenum type, GLint num, EogllObjectAttrType attrType);
EOGLL_DECL_FUNC_ND EogllBufferObject eogllLoadBufferObject(const char* path, EogllObjectAttrs attrs, GLenum usage);



#ifdef __cplusplus
}
#endif

#endif // _EOGLL_H_