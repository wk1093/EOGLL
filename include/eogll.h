/**
 * @file eogll.h
 * @brief EOGLL header file
 * @date 2024-01-25
 *
 * EOGLL is a C library that wraps OpenGL, GLFW, GLAD, CGLM, and more to make it easier to use OpenGL.
 * EOGLL has many useful tools like object loading, camera, and more.
 *
 *
 */




/*
 * Naming convention:
 * DEFINES: CAPITAL_CASE: EOGLL_*
 * TYPES: PascalCase: Eogll*
 * Functions: camelCase: eogll*
 * Enums: CAPITAL_CASE: EOGLL_*
 */


#pragma once
#ifndef _EOGLL_H_
#define _EOGLL_H_

#include "eogll_version.h"

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

/// Normal cursor mode
#define EOGLL_CURSOR_NORMAL          0x00034001

/// Hidden cursor mode
#define EOGLL_CURSOR_HIDDEN          0x00034002

/// Disabled cursor mode
#define EOGLL_CURSOR_DISABLED        0x00034003

/**
 * @brief Result type for EOGLL functions
 */
typedef uint8_t EogllResult;
#define EOGLL_SUCCESS 0
#define EOGLL_FAILURE 1

#define EOGLL_NO_DISCARD HEDLEY_WARN_UNUSED_RESULT

#define EOGLL_VERSION_NUMBER (EOGLL_VERSION_MAJOR * 10000 + EOGLL_VERSION_MINOR * 100 + EOGLL_VERSION_PATCH)


//#define EOGLL_DECL_FUNC
//#define EOGLL_DECL_STRUCT
//#define EOGLL_DECL_FUNC_ND EOGLL_DECL_FUNC EOGLL_NO_DISCARD
//#define EOGLL_DECL_VAR
//#define EOGLL_DECL_ENUM
#ifndef EOGLL_DECL_FUNC
/**
 * @brief Declares a function
 *
 * Allows the user to add attributes to the function declarations of EOGLL
 */
#define EOGLL_DECL_FUNC HEDLEY_PUBLIC
#endif
#ifndef EOGLL_DECL_STRUCT
/**
 * @brief Declares a struct
 *
 * Allows the user to add attributes to the struct declarations of EOGLL
 */
#define EOGLL_DECL_STRUCT
#endif
#ifndef EOGLL_DECL_FUNC_ND
/**
 * @brief Declares a function where the return value is not meant to be discarded
 */
#define EOGLL_DECL_FUNC_ND EOGLL_DECL_FUNC EOGLL_NO_DISCARD
#endif
#ifndef EOGLL_DECL_VAR
/**
 * @brief Declares a variable
 *
 * Allows the user to add attributes to the variable declarations of EOGLL
 */
#define EOGLL_DECL_VAR HEDLEY_PUBLIC
#endif
#ifndef EOGLL_DECL_ENUM
/**
 * @brief Declares an enum
 *
 * Allows the user to add attributes to the enum declarations of EOGLL
 */
#define EOGLL_DECL_ENUM
#endif

/**
 * @brief Logging levels
 *
 * EOGLL_LOG_LEVEL_TRACE: Trace level, many of the EOGLL functions will output a message at this level
 * EOGLL_LOG_LEVEL_DEBUG: Debug level, some of the EOGLL functions will output a message at this level (none of the "loop" functions will output a message at this level)
 * EOGLL_LOG_LEVEL_INFO: Info level, some startup messages will be output at this level
 * EOGLL_LOG_LEVEL_WARN: Warn level, some warnings will output at this level if something is wrong
 * EOGLL_LOG_LEVEL_ERROR: Error level, most errors will output at this level
 * EOGLL_LOG_LEVEL_FATAL: Fatal level, fatal errors will output at this level
 *
 * EOGLL_LOG_LEVEL_TRACE is only enabled if EOGLL_TRACE is defined
 * EOGLL_LOG_LEVEL_DEBUG is only enabled if EOGLL_DEBUG is defined
 *
 * EOGLL_LOG_LEVEL_INFO, EOGLL_LOG_LEVEL_WARN, EOGLL_LOG_LEVEL_ERROR, and EOGLL_LOG_LEVEL_FATAL are always enabled
 */
typedef EOGLL_DECL_ENUM enum EogllLogLevel {
    EOGLL_LOG_LEVEL_TRACE,
    EOGLL_LOG_LEVEL_DEBUG,
    EOGLL_LOG_LEVEL_INFO,
    EOGLL_LOG_LEVEL_WARN,
    EOGLL_LOG_LEVEL_ERROR,
    EOGLL_LOG_LEVEL_FATAL
} EogllLogLevel;

/**
 * @brief Core logging function
 *
 * @param stream The stream to log to
 * @param level The level of the message
 * @param message The message to log
 * @param ... The arguments to the message
 * @note This function is not meant to be called directly, use the macros instead
 *
 * @see EOGLL_LOG_DEBUG
 * @see EOGLL_LOG_TRACE
 * @see EOGLL_LOG_INFO
 * @see EOGLL_LOG_WARN
 * @see EOGLL_LOG_ERROR
 * @see EOGLL_LOG_FATAL
 *
 * @see EogllLogLevel
 */
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

/**
 * @brief Core logging function with file and line
 * @param stream The stream to log to
 * @param level The level of the message
 * @param message The message to log
 * @param ... The arguments to the message
 * @note This function is not meant to be called directly, use the macros instead
 * @see EOGLL_LOG_DEBUG_POS
 * @see EOGLL_LOG_TRACE_POS
 * @see EOGLL_LOG_INFO_POS
 * @see EOGLL_LOG_WARN_POS
 * @see EOGLL_LOG_ERROR_POS
 * @see EOGLL_LOG_FATAL_POS
 * @see EogllLogLevel
 */
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
/**
 * @brief Logs a message at the debug level
 * @param stream The stream to log to
 * @param message The message to log
 * @param ... The arguments to the message
 * @see EOGLL_LOG_DEBUG_POS
 *
 * Sample:
 * @code{.c}
 * EOGLL_LOG_DEBUG(stdout, "Hello, %s!", "world");
 * @endcode
 *
 * Output:
 * @code{.txt}
 * [DEBUG main] Hello, world!
 * @endcode
 */
#define EOGLL_LOG_DEBUG(stream, message, ...)
/**
 * @brief Logs a message at the debug level with file and line
 * @param stream The stream to log to
 * @param message The message to log
 * @param ... The arguments to the message
 * @see EOGLL_LOG_DEBUG
 *
 * Sample:
 * @code{.c}
 * EOGLL_LOG_DEBUG_POS(stdout, "Hello, %s!", "world");
 * @endcode
 *
 * Output:
 * @code{.txt}
 * [DEBUG main.c:42] Hello, world!
 * @endcode
 */
#define EOGLL_LOG_DEBUG_POS(stream, message, ...)
#endif

#ifdef EOGLL_TRACE
#define EOGLL_LOG_TRACE(stream, message, ...) EOGLL_LOG(stream, EOGLL_LOG_LEVEL_TRACE, message, ##__VA_ARGS__)
#define EOGLL_LOG_TRACE_POS(stream, message, ...) EOGLL_LOG_POS(stream, EOGLL_LOG_LEVEL_TRACE, message, ##__VA_ARGS__)
#else
/**
 * @brief Logs a message at the trace level
 * @param stream The stream to log to
 * @param message The message to log
 * @param ... The arguments to the message
 * @see EOGLL_LOG_TRACE_POS
 *
 * Sample:
 * @code{.c}
 * EOGLL_LOG_TRACE(stdout, "Hello, %s!", "world");
 * @endcode
 *
 * Output:
 * @code{.txt}
 * [TRACE main] Hello, world!
 * @endcode
 */
#define EOGLL_LOG_TRACE(stream, message, ...)

/**
 * @brief Logs a message at the trace level with file and line
 * @param stream The stream to log to
 * @param message The message to log
 * @param ... The arguments to the message
 * @see EOGLL_LOG_TRACE
 *
 * Sample:
 * @code{.c}
 * EOGLL_LOG_TRACE_POS(stdout, "Hello, %s!", "world");
 * @endcode
 *
 * Output:
 * @code{.txt}
 * [TRACE main.c:42] Hello, world!
 * @endcode
 */
#define EOGLL_LOG_TRACE_POS(stream, message, ...)
#endif

/**
 * @brief Logs a message at the info level
 * @param stream The stream to log to
 * @param message The message to log
 * @param ... The arguments to the message
 * @see EOGLL_LOG_INFO_POS
 *
 * Sample:
 * @code{.c}
 * EOGLL_LOG_INFO(stdout, "Hello, %s!", "world");
 * @endcode
 *
 * Output:
 * @code{.txt}
 * [INFO main] Hello, world!
 * @endcode
 */
#define EOGLL_LOG_INFO(stream, message, ...) EOGLL_LOG(stream, EOGLL_LOG_LEVEL_INFO, message, ##__VA_ARGS__)

/**
 * @brief Logs a message at the info level with file and line
 * @param stream The stream to log to
 * @param message The message to log
 * @param ... The arguments to the message
 * @see EOGLL_LOG_INFO
 *
 * Sample:
 * @code{.c}
 * EOGLL_LOG_INFO_POS(stdout, "Hello, %s!", "world");
 * @endcode
 *
 * Output:
 * @code{.txt}
 * [INFO main.c:42] Hello, world!
 * @endcode
 */
#define EOGLL_LOG_INFO_POS(stream, message, ...) EOGLL_LOG_POS(stream, EOGLL_LOG_LEVEL_INFO, message, ##__VA_ARGS__)

/**
 * @brief Logs a message at the warn level
 * @param stream The stream to log to
 * @param message The message to log
 * @param ... The arguments to the message
 * @see EOGLL_LOG_WARN_POS
 *
 * Sample:
 * @code{.c}
 * EOGLL_LOG_WARN(stdout, "Hello, %s!", "world");
 * @endcode
 *
 * Output:
 * @code{.txt}
 * [WARN main] Hello, world!
 * @endcode
 */
#define EOGLL_LOG_WARN(stream, message, ...) EOGLL_LOG(stream, EOGLL_LOG_LEVEL_WARN, message, ##__VA_ARGS__)

/**
 * @brief Logs a message at the warn level with file and line
 * @param stream The stream to log to
 * @param message The message to log
 * @param ... The arguments to the message
 * @see EOGLL_LOG_WARN
 *
 * Sample:
 * @code{.c}
 * EOGLL_LOG_WARN_POS(stdout, "Hello, %s!", "world");
 * @endcode
 *
 * Output:
 * @code{.txt}
 * [WARN main.c:42] Hello, world!
 * @endcode
 */
#define EOGLL_LOG_WARN_POS(stream, message, ...) EOGLL_LOG_POS(stream, EOGLL_LOG_LEVEL_WARN, message, ##__VA_ARGS__)

/**
 * @brief Logs a message at the error level
 * @param stream The stream to log to
 * @param message The message to log
 * @param ... The arguments to the message
 * @see EOGLL_LOG_ERROR_POS
 *
 * Sample:
 * @code{.c}
 * EOGLL_LOG_ERROR(stdout, "Hello, %s!", "world");
 * @endcode
 *
 * Output:
 * @code{.txt}
 * [ERROR main] Hello, world!
 * @endcode
 */
#define EOGLL_LOG_ERROR(stream, message, ...) EOGLL_LOG(stream, EOGLL_LOG_LEVEL_ERROR, message, ##__VA_ARGS__)

/**
 * @brief Logs a message at the error level with file and line
 * @param stream The stream to log to
 * @param message The message to log
 * @param ... The arguments to the message
 * @see EOGLL_LOG_ERROR
 *
 * Sample:
 * @code{.c}
 * EOGLL_LOG_ERROR_POS(stdout, "Hello, %s!", "world");
 * @endcode
 *
 * Output:
 * @code{.txt}
 * [ERROR main.c:42] Hello, world!
 * @endcode
 */
#define EOGLL_LOG_ERROR_POS(stream, message, ...) EOGLL_LOG_POS(stream, EOGLL_LOG_LEVEL_ERROR, message, ##__VA_ARGS__)

/**
 * @brief Logs a message at the fatal level
 * @param stream The stream to log to
 * @param message The message to log
 * @param ... The arguments to the message
 * @see EOGLL_LOG_FATAL_POS
 *
 * Sample:
 * @code{.c}
 * EOGLL_LOG_FATAL(stdout, "Hello, %s!", "world");
 * @endcode
 *
 * Output:
 * @code{.txt}
 * [FATAL main] Hello, world!
 * @endcode
 */
#define EOGLL_LOG_FATAL(stream, message, ...) EOGLL_LOG(stream, EOGLL_LOG_LEVEL_FATAL, message, ##__VA_ARGS__)

/**
 * @brief Logs a message at the fatal level with file and line
 * @param stream The stream to log to
 * @param message The message to log
 * @param ... The arguments to the message
 * @see EOGLL_LOG_FATAL
 *
 * Sample:
 * @code{.c}
 * EOGLL_LOG_FATAL_POS(stdout, "Hello, %s!", "world");
 * @endcode
 *
 * Output:
 * @code{.txt}
 * [FATAL main.c:42] Hello, world!
 * @endcode
 */
#define EOGLL_LOG_FATAL_POS(stream, message, ...) EOGLL_LOG_POS(stream, EOGLL_LOG_LEVEL_FATAL, message, ##__VA_ARGS__)

/**
 * @brief Gets the version of EOGLL
 * @return The version of EOGLL
 *
 * Should output something like "EOGLL 0.1.0"
 */
EOGLL_DECL_FUNC_ND const char* eogllGetVersionString();

// TODO: implement check init
///**
// * @brief Used internally to check if EOGLL has been initialized
// * @note This should not be used or changed by the user
// *
// * @see eogllCheckInit
// */
//EOGLL_DECL_VAR extern bool eogllInitialized;
//
///**
// * @brief Checks if EOGLL has been initialized
// * @note This should not be used or changed by the user
// *
// * @see eogllInitialized
// */
//static inline void eogllCheckInit() {
//    if (!eogllInitialized) {
//        EOGLL_LOG_FATAL(stderr, "EOGLL has not been initialized!\n");
//        exit(1);
//    }
//}

/**
 * @brief Initializes EOGLL
 * @return EOGLL_SUCCESS if successful, EOGLL_FAILURE if not
 * @note This function must be called before any other EOGLL functions
 *
 * This function initializes GLFW and GLAD
 */
EOGLL_DECL_FUNC_ND EogllResult eogllInit();

/**
 * @brief Terminates EOGLL
 *
 * This function terminates GLFW
 */
EOGLL_DECL_FUNC void eogllTerminate();

/**
 * @brief Reads a file into a char array
 * @param path The path to the file
 * @return The contents of the file as a char array (must be freed)
 * @note This function is used internally, but isn't meant to be used by the user
 */
EOGLL_DECL_FUNC_ND char* eogllReadFile(const char* path);

/**
 * @brief A struct that represents a window
 * @see eogllCreateWindow
 * @see eogllDestroyWindow
 *
 * This struct is used to handle all window related things
 */
typedef EOGLL_DECL_STRUCT struct EogllWindow {
    /// The GLFW window
    GLFWwindow* window;
    /// The width of the window, this is updated whenever the window is resized
    uint32_t width;
    /// The height of the window, this is updated whenever the window is resized
    uint32_t height;

    /// An array of booleans that represents if a key was pressed
    bool press[EOGLL_KEY_LAST + 1];

    /// An array of booleans that represents if a key was released
    bool release[EOGLL_KEY_LAST + 1];

    /// An array of booleans that represents if a key is down
    bool isDown[EOGLL_KEY_LAST + 1];

    /// An array of booleans that represents if a mouse button was pressed
    bool mousePress[EOGLL_MOUSE_BUTTON_LAST + 1];

    /// An array of booleans that represents if a mouse button was released
    bool mouseRelease[EOGLL_MOUSE_BUTTON_LAST + 1];

    /// An array of booleans that represents if a mouse button is down
    bool mouseIsDown[EOGLL_MOUSE_BUTTON_LAST + 1];

    /// The x position of the mouse
    double mousex;

    /// The x delta of the mouse
    double mousedx;

    /// The y position of the mouse
    double mousey;

    /// The y delta of the mouse
    double mousedy;

    /// The x scroll of the mouse
    double mouseScrollx;

    /// The y scroll of the mouse
    double mouseScrolly;

    /// whether or not the window is focused
    bool focused;

    // TODO: add more window properties
} EogllWindow;

/**
 * @brief A struct that holds all the extra data to create a window
 * @see eogllCreateWindow
 * @see eogllDefaultWindowHints
 * @see eogllCreateWindowHints
 *
 * This struct is used to create a window with window "hints"
 */
typedef EOGLL_DECL_STRUCT struct EogllWindowHints {
    /// Whether or not the window can be resized
    bool resizable;

    /// Whether or not the window has a border and title bar
    bool decorated;

    /// Whether or not the window is floating (always on top)
    bool floating;

    /// Whether or not the window is maximized
    bool maximized;

    /// Whether or not the window is visible
    bool visible;

    /// Whether or not the window is focused (this is only the starting state, the window can go in and out of focus later)
    bool focused;
} EogllWindowHints;

/**
 * @brief Creates a window hints struct
 * @param resizable Whether or not the window can be resized
 * @param decorated Whether or not the window has a border and title bar
 * @param floating Whether or not the window is floating (always on top)
 * @param maximized Whether or not the window is maximized
 * @param visible Whether or not the window is visible
 * @param focused Whether or not the window is focused (this is only the starting state, the window can go in and out of focus later)
 * @return The created window hints struct
 * @see eogllDefaultWindowHints
 * @see EogllWindowHints
 *
 * This function creates a window hints struct with the given values
 */
EOGLL_DECL_FUNC_ND EogllWindowHints eogllCreateWindowHints(bool resizable, bool decorated, bool floating, bool maximized, bool visible, bool focused);

/**
 * @brief Creates a window hints struct with default values
 * @return The created window hints struct
 * @see eogllCreateWindowHints
 * @see EogllWindowHints
 *
 * This function creates a window hints struct with the following values:
 * resizable: true
 * decorated: true
 * floating: false
 * maximized: false
 * visible: true
 * focused: true
 */
EOGLL_DECL_FUNC_ND EogllWindowHints eogllDefaultWindowHints();

/**
 * @brief Creates a window
 * @param width The width of the window
 * @param height The height of the window
 * @param title The title of the window
 * @param hints The window hints to use
 * @return The created window
 * @see eogllDestroyWindow
 * @see EogllWindow
 * @see EogllWindowHints
 *
 * This function creates a window with the given width, height, title, and window hints
 */
EOGLL_DECL_FUNC_ND EogllWindow* eogllCreateWindow(uint32_t width, uint32_t height, const char* title, EogllWindowHints hints);

/**
 * @brief Checks if the window should close
 * @param window The window to check
 * @return Whether or not the window should close
 * @see eogllSetWindowShouldClose
 *
 * This function checks if the window should close (normally this is when the user clicks the close button).
 * Most programs will have a loop that looks something like this:
 * @code{.c}
 * while (!eogllWindowShouldClose(window)) {
 *    // do stuff
 *    eogllPollEvents(window);
 *    eogllSwapBuffers(window);
 * }
 * @endcode
 */
EOGLL_DECL_FUNC_ND bool eogllWindowShouldClose(EogllWindow* window);

/**
 * @brief Sets whether or not the window should close
 * @param window The window to set
 * @param shouldClose Whether or not the window should close
 * @see eogllWindowShouldClose
 *
 * This function is mostly used when you want to exit the program, but you don't want to have to repeat all of the cleanup code:
 * @code{.c}
 * while (!eogllWindowShouldClose(window)) {
 *     // do stuff
 *     if (shouldExit) {
 *         eogllSetWindowShouldClose(window, true);
 *     }
 *     // rest of loop
 * }
 * // cleanup code HERE in one place
 * // delete stuff (buffers, shaders, window, etc.)
 *
 * @endcode
 *
 * Instead of doing this:
 * @code{.c}
 * while (!eogllWindowShouldClose(window)) {
 *     // do stuff
 *     if (shouldExit) {
 *         // cleanup code HERE
 *         // delete stuff (buffers, shaders, window, etc.)
 *         return 0;
 *     }
 *     // rest of loop
 * }
 * // repeated cleanup code
 * // delete stuff (buffers, shaders, window, etc.)
 * @endcode
 */
EOGLL_DECL_FUNC void eogllSetWindowShouldClose(EogllWindow* window, bool shouldClose);

/**
 * @brief Polls events
 * @param window The window to poll events for
 * @see eogllWindowShouldClose
 * @see eogllSwapBuffers
 *
 * This function polls events for the given window.
 * This function should be called every frame.
 *
 * This function is used to update the window's properties (such as the width and height) and to update the input.
 */
EOGLL_DECL_FUNC void eogllPollEvents(EogllWindow* window);

/**
 * @brief Swaps the buffers
 * @param window The window to swap the buffers for
 * @see eogllWindowShouldClose
 * @see eogllPollEvents
 *
 * This function swaps the buffers for the given window.
 * This function should be called every frame.
 *
 * This function is used to update the window's display.
 */
EOGLL_DECL_FUNC void eogllSwapBuffers(EogllWindow* window);

/**
 * @brief Destroys a window
 * @param window The window to destroy
 * @see eogllCreateWindow
 *
 * This function destroys the given window.
 * This function should be called when you are done with the window.
 */
EOGLL_DECL_FUNC void eogllDestroyWindow(EogllWindow* window);

#define DEPRECATED HEDLEY_DEPRECATED_FOR(0.2.6, window->press[key])
/**
 * @brief Gets if a key is pressed
 * @param window The window to check
 * @param key The key to check
 * @return Whether or not the key is pressed
 * @see eogllGetKeyRelease
 * @see eogllGetKeyIsDown
 *
 * @deprecated This function is deprecated (since 0.2.6), use window->press[key] instead
 *
 * This function checks if the given key is pressed.
 */
EOGLL_DECL_FUNC_ND DEPRECATED bool eogllGetKeyPress(EogllWindow* window, int key);
#undef DEPRECATED

#define DEPRECATED HEDLEY_DEPRECATED_FOR(0.2.6, window->release[key])
/**
 * @brief Gets if a key is released
 * @param window The window to check
 * @param key The key to check
 * @return Whether or not the key is released
 * @see eogllGetKeyPress
 * @see eogllGetKeyIsDown
 *
 * @deprecated This function is deprecated (since 0.2.6), use window->release[key] instead
 *
 * This function checks if the given key is released.
 */
EOGLL_DECL_FUNC_ND DEPRECATED bool eogllGetKeyRelease(EogllWindow* window, int key);
#undef DEPRECATED

#define DEPRECATED HEDLEY_DEPRECATED_FOR(0.2.6, window->isDown[key])
/**
 * @brief Gets if a key is down
 * @param window The window to check
 * @param key The key to check
 * @return Whether or not the key is down
 * @see eogllGetKeyPress
 * @see eogllGetKeyRelease
 *
 * @deprecated This function is deprecated (since 0.2.6), use window->isDown[key] instead
 *
 * This function checks if the given key is down.
 */
EOGLL_DECL_FUNC_ND DEPRECATED bool eogllGetKeyIsDown(EogllWindow* window, int key);
#undef DEPRECATED

#define DEPRECATED HEDLEY_DEPRECATED_FOR(0.2.6, window->mousePress[key])
/**
 * @brief Gets if a mouse button is pressed
 * @param window The window to check
 * @param button The mouse button to check
 * @return Whether or not the mouse button is pressed
 * @see eogllGetMouseRelease
 * @see eogllGetMouseIsDown
 *
 * @deprecated This function is deprecated (since 0.2.6), use window->mousePress[button] instead
 *
 * This function checks if the given mouse button is pressed.
 */
EOGLL_DECL_FUNC_ND DEPRECATED bool eogllGetMousePress(EogllWindow* window, int button);
#undef DEPRECATED

#define DEPRECATED HEDLEY_DEPRECATED_FOR(0.2.6, window->mouseRelease[key])
/**
 * @brief Gets if a mouse button is released
 * @param window The window to check
 * @param button The mouse button to check
 * @return Whether or not the mouse button is released
 * @see eogllGetMousePress
 * @see eogllGetMouseIsDown
 *
 * @deprecated This function is deprecated (since 0.2.6), use window->mouseRelease[button] instead
 *
 * This function checks if the given mouse button is released.
 */
EOGLL_DECL_FUNC_ND DEPRECATED bool eogllGetMouseRelease(EogllWindow* window, int button);
#undef DEPRECATED

#define DEPRECATED HEDLEY_DEPRECATED_FOR(0.2.6, window->mouseIsDown[key])
/**
 * @brief Gets if a mouse button is down
 * @param window The window to check
 * @param button The mouse button to check
 * @return Whether or not the mouse button is down
 * @see eogllGetMousePress
 * @see eogllGetMouseRelease
 *
 * @deprecated This function is deprecated (since 0.2.6), use window->mouseIsDown[button] instead
 *
 * This function checks if the given mouse button is down.
 */
EOGLL_DECL_FUNC_ND DEPRECATED bool eogllGetMouseIsDown(EogllWindow* window, int button);
#undef DEPRECATED

/**
 * @brief Gets the position of the mouse
 * @param window The window to get the mouse position for
 * @param xpos A pointer to the destination of the x position
 * @param ypos A pointer to the destination of the y position
 * @see eogllSetMousePos
 * @see EogllWindow
 *
 * This function gets the position of the mouse.
 * This function is effectively the same as using window->mousex and window->mousey.
 */
EOGLL_DECL_FUNC void eogllGetMousePos(EogllWindow* window, double* xpos, double* ypos);

/**
 * @brief Sets the position of the mouse
 * @param window The window to set the mouse position for
 * @param xpos The x position to set
 * @param ypos The y position to set
 * @see eogllGetMousePos
 * @see EogllWindow
 *
 * This function sets the position of the mouse.
 */
EOGLL_DECL_FUNC void eogllSetMousePos(EogllWindow* window, double xpos, double ypos);

/**
 * @brief Gets the delta of the mouse
 * @param window The window to get the mouse delta for
 * @param dxpos A pointer to the destination of the x delta
 * @param dypos A pointer to the destination of the y delta
 * @see EogllWindow
 *
 * This function gets the delta of the mouse.
 * This function is effectively the same as using window->mousedx and window->mousedy.
 */
EOGLL_DECL_FUNC void eogllGetMouseDelta(EogllWindow* window, double* dxpos, double* dypos);

/**
 * @brief Gets the scroll of the mouse
 * @param window The window to get the mouse scroll for
 * @param xscroll A pointer to the destination of the x scroll
 * @param yscroll A pointer to the destination of the y scroll
 * @see EogllWindow
 *
 * This function gets the scroll of the mouse.
 * This function is effectively the same as using window->mouseScrollx and window->mouseScrolly.
 */
EOGLL_DECL_FUNC void eogllGetMouseScroll(EogllWindow* window, double* xscroll, double* yscroll);

/**
 * @brief Gets the size of the window
 * @param window The window to get the size for
 * @param width A pointer to the destination of the width
 * @param height A pointer to the destination of the height
 * @see eogllSetWindowSize
 * @see EogllWindow
 *
 * This function gets the size of the window.
 * This function is effectively the same as using window->width and window->height.
 */
EOGLL_DECL_FUNC void eogllGetWindowSize(EogllWindow* window, uint32_t* width, uint32_t* height);

/**
 * @brief Sets the size of the window
 * @param window The window to set the size for
 * @param width The width to set
 * @param height The height to set
 * @see eogllGetWindowSize
 * @see EogllWindow
 *
 * This function sets the size of the window.
 */
EOGLL_DECL_FUNC void eogllSetWindowSize(EogllWindow* window, uint32_t width, uint32_t height);

/**
 * @brief Gets the position of the window
 * @param window The window to get the position for
 * @param x A pointer to the destination of the x position
 * @param y A pointer to the destination of the y position
 * @see eogllSetWindowPos
 * @see EogllWindow
 *
 * This function gets the position of the window.
 */
EOGLL_DECL_FUNC void eogllGetWindowPos(EogllWindow* window, int* x, int* y);

/**
 * @brief Sets the position of the window
 * @param window The window to set the position for
 * @param x The x position to set
 * @param y The y position to set
 * @see eogllGetWindowPos
 * @see EogllWindow
 *
 * This function sets the position of the window.
 */
EOGLL_DECL_FUNC void eogllSetWindowPos(EogllWindow* window, int x, int y);

/**
 * @brief Gets the current cursor pos
 * @param window The window to get the cursor pos for
 * @param xpos A pointer to the destination of the x position
 * @param ypos A pointer to the destination of the y position
 * @see eogllSetCursorPos
 * @see EogllWindow
 *
 * This function gets the current cursor pos.
 * This function is different from eogllGetMousePos:
 * eogllGetMousePos is updated by a callback function, so it's updated whenever the mouse moves, but eogllGetCursorPos gets the current cursor pos, so it's only updated when you call this function.
 * eogllGetCursorPos is more CPU intensive than eogllGetMousePos, so you should only use it when you need to.
 */
EOGLL_DECL_FUNC void eogllGetCursorPos(EogllWindow* window, double* xpos, double* ypos);

/**
 * @brief Sets the cursor pos
 * @param window The window to set the cursor pos for
 * @param xpos The x position to set
 * @param ypos The y position to set
 * @see eogllGetCursorPos
 * @see EogllWindow
 *
 * This function sets the cursor pos.
 * This function is identical to eogllSetMousePos.
 */
EOGLL_DECL_FUNC void eogllSetCursorPos(EogllWindow* window, double xpos, double ypos);

/**
 * @brief Centers the window on the current monitor
 * @param window The window to center
 * @see EogllWindow
 *
 * This function centers the window on the current monitor.
 * Very useful when creating a splash screen (undecorated) window.
 */
EOGLL_DECL_FUNC void eogllCenterWindow(EogllWindow* window);

/**
 * @brief Gets the current time
 * @return The current time
 * @see eogllSetTime
 *
 * This function gets the current time.
 * This function is effectively the same as using glfwGetTime.
 */
EOGLL_DECL_FUNC_ND double eogllGetTime();

/**
 * @brief Sets the cursor mode
 * @param window The window to set the cursor mode for
 * @param mode The cursor mode to set
 * @see EogllWindow
 * @see EOGLL_CURSOR_NORMAL
 * @see EOGLL_CURSOR_HIDDEN
 * @see EOGLL_CURSOR_DISABLED
 *
 * This function sets the cursor mode.
 * This function is effectively the same as using glfwSetInputMode(window->window, GLFW_CURSOR, mode).
 */
EOGLL_DECL_FUNC void eogllSetCursorMode(EogllWindow* window, int mode);

/**
 * @brief A representation of a color
 * @see eogllClearColor
 * @see eogllCreateColor
 * @see eogllColorEqual
 *
 * @deprecated This struct is deprecated (since 0.2.6), use the default glClearColor function instead
 *
 * This struct is used to represent a color.
 *
 */
typedef EOGLL_DECL_STRUCT struct EogllColor {
    /// The red component of the color
    float r;

    /// The green component of the color
    float g;

    /// The blue component of the color
    float b;

    /// The alpha component of the color
    float a;
} EogllColor;

#define DEPRECATED HEDLEY_DEPRECATED_FOR(0.2.6, glClearColor(color.r, color.g, color.b, color.a))
/**
 * @brief Clears the color buffer
 * @param color The color to clear the buffer to
 * @see eogllCreateColor
 * @see eogllColorEqual
 * @see EogllColor
 *
 * @deprecated This function is deprecated (since 0.2.6), use glClearColor(color.r, color.g, color.b, color.a) instead
 *
 * This function clears the color buffer to the given color.
 */
EOGLL_DECL_FUNC DEPRECATED void eogllClearColor(EogllColor color);
#undef DEPRECATED

#define DEPRECATED HEDLEY_DEPRECATED(0.2.6)
/**
 * @brief Creates a color
 * @param r The red component of the color
 * @param g The green component of the color
 * @param b The blue component of the color
 * @param a The alpha component of the color
 * @return The created color
 * @see eogllClearColor
 * @see eogllColorEqual
 * @see EogllColor
 *
 * @deprecated This function is deprecated (since 0.2.6)
 *
 * This function creates a color with the given components.
 */
EOGLL_DECL_FUNC_ND DEPRECATED EogllColor eogllCreateColor(float r, float g, float b, float a);

/**
 * @brief Checks if two colors are equal
 * @param a The first color
 * @param b The second color
 * @return Whether or not the two colors are equal
 * @see eogllClearColor
 * @see eogllCreateColor
 * @see EogllColor
 *
 * @deprecated This function is deprecated (since 0.2.6)
 *
 * This function checks if the two colors are equal.
 */
EOGLL_DECL_FUNC_ND DEPRECATED bool eogllColorEqual(EogllColor a, EogllColor b);
/**
 * @brief The color black
 * @see EogllColor
 *
 * @deprecated This variable is deprecated (since 0.2.6)
 */
EOGLL_DECL_VAR DEPRECATED extern EogllColor EOGLL_COLOR_BLACK;

/**
 * @brief The color white
 * @see EogllColor
 *
 * @deprecated This variable is deprecated (since 0.2.6)
 */
EOGLL_DECL_VAR DEPRECATED extern EogllColor EOGLL_COLOR_WHITE;

/**
 * @brief The color red
 * @see EogllColor
 *
 * @deprecated This variable is deprecated (since 0.2.6)
 */
EOGLL_DECL_VAR DEPRECATED extern EogllColor EOGLL_COLOR_RED;

/**
 * @brief The color green
 * @see EogllColor
 *
 * @deprecated This variable is deprecated (since 0.2.6)
 */
EOGLL_DECL_VAR DEPRECATED extern EogllColor EOGLL_COLOR_GREEN;

/**
 * @brief The color blue
 * @see EogllColor
 *
 * @deprecated This variable is deprecated (since 0.2.6)
 */
EOGLL_DECL_VAR DEPRECATED extern EogllColor EOGLL_COLOR_BLUE;

/**
 * @brief The color yellow
 * @see EogllColor
 *
 * @deprecated This variable is deprecated (since 0.2.6)
 */
EOGLL_DECL_VAR DEPRECATED extern EogllColor EOGLL_COLOR_YELLOW;

/**
 * @brief The color magenta
 * @see EogllColor
 *
 * @deprecated This variable is deprecated (since 0.2.6)
 */
EOGLL_DECL_VAR DEPRECATED extern EogllColor EOGLL_COLOR_MAGENTA;

/**
 * @brief The color cyan
 * @see EogllColor
 *
 * @deprecated This variable is deprecated (since 0.2.6)
 */
EOGLL_DECL_VAR DEPRECATED extern EogllColor EOGLL_COLOR_CYAN;

/**
 * @brief The color transparent
 * @see EogllColor
 *
 * @deprecated This variable is deprecated (since 0.2.6)
 */
EOGLL_DECL_VAR DEPRECATED extern EogllColor EOGLL_COLOR_TRANSPARENT;
#undef DEPRECATED

/**
 * @brief A struct that represents a shader program
 * @see eogllLinkProgram
 * @see eogllLinkProgramFromFile
 * @see eogllDeleteProgram
 * @see eogllUseProgram
 *
 * This struct is used to handle all shader related things
 */
typedef EOGLL_DECL_STRUCT struct EogllShaderProgram {
    /// The id of the shader program
    unsigned int id;
} EogllShaderProgram;

/**
 * @brief Links a shader program
 * @param vertexShaderSource The source of the vertex shader
 * @param fragmentShaderSource The source of the fragment shader
 * @return The linked shader program
 * @see eogllLinkProgramFromFile
 * @see eogllDeleteProgram
 * @see eogllUseProgram
 * @see EogllShaderProgram
 *
 * This function links a shader program with the given vertex and fragment shader sources.
 */
EOGLL_DECL_FUNC_ND EogllShaderProgram* eogllLinkProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

/**
 * @brief Links a shader program from files
 * @param vertexShaderPath The path to the vertex shader
 * @param fragmentShaderPath The path to the fragment shader
 * @return The linked shader program
 * @see eogllLinkProgram
 * @see eogllDeleteProgram
 * @see eogllUseProgram
 * @see EogllShaderProgram
 * @see eogllReadFile
 *
 * This function links a shader program with the given vertex and fragment shader paths.
 */
EOGLL_DECL_FUNC_ND EogllShaderProgram* eogllLinkProgramFromFile(const char* vertexShaderPath, const char* fragmentShaderPath);

/**
 * @brief Deletes a shader program
 * @param shader The shader program to delete
 * @see eogllLinkProgram
 * @see eogllLinkProgramFromFile
 * @see eogllUseProgram
 * @see EogllShaderProgram
 *
 * This function deletes the given shader program.
 * This function should be called when you are done with the shader program.
 */
EOGLL_DECL_FUNC void eogllDeleteProgram(EogllShaderProgram* shader);

/**
 * @brief Uses a shader program
 * @param shader The shader program to use
 * @see eogllLinkProgram
 * @see eogllLinkProgramFromFile
 * @see eogllDeleteProgram
 * @see EogllShaderProgram
 *
 * This function uses the given shader program.
 * This function should be called before you draw anything using the shader program.
 */
EOGLL_DECL_FUNC void eogllUseProgram(EogllShaderProgram* shader);

/**
 * @brief Sets a uniform matrix 4x4
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param matrix The matrix to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniformMatrix4fv(EogllShaderProgram* shader, const char* name, mat4 matrix);

/**
 * @brief Sets a uniform matrix 3x3
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param matrix The matrix to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniformMatrix3fv(EogllShaderProgram* shader, const char* name, mat3 matrix);

/**
 * @brief Sets a uniform matrix 2x2
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param matrix The matrix to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniformMatrix2fv(EogllShaderProgram* shader, const char* name, mat2 matrix);

/**
 * @brief Sets a uniform vec4 (given 4 floats)
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param x The x component of the vector
 * @param y The y component of the vector
 * @param z The z component of the vector
 * @param w The w component of the vector
 */
EOGLL_DECL_FUNC void eogllSetUniform4f(EogllShaderProgram* shader, const char* name, float x, float y, float z, float w);

/**
 * @brief Sets a uniform vec4 (given a vec4)
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param vector The vector to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniform4fv(EogllShaderProgram* shader, const char* name, vec4 vector);

/**
 * @brief Sets a uniform vec3 (given 3 floats)
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param x The x component of the vector
 * @param y The y component of the vector
 * @param z The z component of the vector
 */
EOGLL_DECL_FUNC void eogllSetUniform3f(EogllShaderProgram* shader, const char* name, float x, float y, float z);

/**
 * @brief Sets a uniform vec3 (given a vec3)
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param vector The vector to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniform3fv(EogllShaderProgram* shader, const char* name, vec3 vector);

/**
 * @brief Sets a uniform vec2 (given 2 floats)
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param x The x component of the vector
 * @param y The y component of the vector
 */
EOGLL_DECL_FUNC void eogllSetUniform2f(EogllShaderProgram* shader, const char* name, float x, float y);

/**
 * @brief Sets a uniform vec2 (given a vec2)
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param vector The vector to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniform2fv(EogllShaderProgram* shader, const char* name, vec2 vector);

/**
 * @brief Sets a uniform float
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param x The float to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniform1f(EogllShaderProgram* shader, const char* name, float x);

/**
 * @brief Sets a uniform float array
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param vector The array to set the uniform to
 * @param count The number of elements in the array
 */
EOGLL_DECL_FUNC void eogllSetUniform1fv(EogllShaderProgram* shader, const char* name, float* vector, GLsizei count);

/**
 * @brief Sets a uniform int
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param x The int to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniform1i(EogllShaderProgram* shader, const char* name, int x);

/**
 * @brief Sets a uniform int array
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param vector The array to set the uniform to
 * @param count The number of elements in the array
 */
EOGLL_DECL_FUNC void eogllSetUniform1iv(EogllShaderProgram* shader, const char* name, int* vector, GLsizei count);

/**
 * @brief Sets a uniform unsigned int
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param x The unsigned int to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniform1ui(EogllShaderProgram* shader, const char* name, unsigned int x);

/**
 * @brief Sets a uniform unsigned int array
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param vector The array to set the uniform to
 * @param count The number of elements in the array
 */
EOGLL_DECL_FUNC void eogllSetUniform1uiv(EogllShaderProgram* shader, const char* name, unsigned int* vector, GLsizei count);

// TODO: list of vectors and matrices


/**
 * @brief Creates a vertex array object
 * @return The created vertex array object
 * @see eogllGenBuffer
 *
 * This function creates a vertex array object.
 */
EOGLL_DECL_FUNC_ND unsigned int eogllGenVertexArray();

/**
 * @brief Creates a buffer object
 * @param vao The vertex array object to use
 * @param mode The mode to use
 * @param count The number of indices
 * @param indices The indices
 * @param usage The usage
 * @return The created buffer object
 * @see eogllGenVertexArray
 *
 * This function creates a buffer object.
 *
 * passing vao to eogllGenBuffer will ensure that the correct vao is bound, and it will unbind it when it's done, this help track down bugs later on
 * if we do a function that requires a vao to be bound, but it's not bound right before, there might be an unnoticed bug later,
 * but if we always unbind it when we're done, we can be sure that that bug will appear right away instead of later on in a distant universe.
 */
EOGLL_DECL_FUNC_ND unsigned int eogllGenBuffer(unsigned int vao, GLenum mode, GLsizeiptr count, const void* indices, GLenum usage);

/**
 * @brief This struct represents a vertex attribute
 * @see eogllCreateAttribBuilder
 * @see eogllAddAttribute
 * @see EogllAttribBuilder
 *
 * This struct represents a vertex attribute.
 * This struct is used internally by EogllAttribBuilder.
 * This struct is not meant to be used by the user.
 */
typedef EOGLL_DECL_STRUCT struct EogllVertAttribData {
    /// The type of the attribute
    GLenum type;

    /// The number of elements in the attribute
    GLint size;

    /// The offset of the attribute
    GLboolean normalized;
} EogllVertAttribData;

/**
 * @brief This struct represents an attribute builder
 * @see eogllCreateAttribBuilder
 * @see eogllAddAttribute
 * @see eogllBuildAttributes
 *
 * This struct represents an attribute builder.
 * This struct is used to build attributes for a vertex array object.
 *
 * This struct replaces the complicated OpenGL functions that are used to build attributes.
 * This struct is much easier to use than the OpenGL functions.
 *
 * @code{.c}
 * EogllAttribBuilder builder = eogllCreateAttribBuilder();
 * eogllAddAttribute(&builder, GL_FLOAT, 3); // vec3 pos
 * eogllAddAttribute(&builder, GL_FLOAT, 2); // vec2 texCoord
 * eogllAddAttribute(&builder, GL_FLOAT, 3); // vec3 normal
 * eogllBuildAttributes(&builder, vao); // vao is the vertex array object
 * @endcode
 */
typedef EOGLL_DECL_STRUCT struct EogllAttribBuilder {
    /**
     * @brief The attributes
     *
     * This array contains all of the attributes.
     * There is a limit of 16 attributes because most GPUs only support 16 attributes.
     */
    EogllVertAttribData attribs[16];

    /// The number of attributes
    GLuint numAttribs;
} EogllAttribBuilder;

/**
 * @brief Creates an attribute builder
 * @return The created attribute builder
 * @see eogllAddAttribute
 * @see eogllBuildAttributes
 * @see EogllAttribBuilder
 */
EOGLL_DECL_FUNC_ND EogllAttribBuilder eogllCreateAttribBuilder();

/**
 * @brief Gets the size of a GL type
 * @param type The type to get the size of
 * @return The size of the type
 * @see eogllAddAttribute
 * @see EogllAttribBuilder
 *
 * This function gets the size of the given GL type (like GL_FLOAT, or GL_UNSIGNED_INT).
 * This function is used internally by EogllAttribBuilder.
 * This function is not meant to be used by the user.
 * This function is used to calculate the offset of the attribute.
 */
EOGLL_DECL_FUNC_ND GLint eogllSizeOf(GLenum type);

/**
 * @brief Adds an attribute to the attribute builder
 * @param builder The attribute builder to add the attribute to
 * @param type The type of the attribute
 * @param num The number of elements in the attribute
 * @see eogllCreateAttribBuilder
 * @see eogllBuildAttributes
 * @see EogllAttribBuilder
 *
 * This function adds an attribute to the given attribute builder.
 * This function is used to build attributes for a vertex array object.
 */
EOGLL_DECL_FUNC void eogllAddAttribute(EogllAttribBuilder *builder, GLenum type, GLint num);

/**
 * @brief Builds the attributes for a vertex array object
 * @param builder The attribute builder to use
 * @param vao The vertex array object to build the attributes for
 * @see eogllCreateAttribBuilder
 * @see eogllAddAttribute
 * @see EogllAttribBuilder
 *
 * This function builds the attributes for the given vertex array object.
 * This function is used to build attributes for a vertex array object.
 */
EOGLL_DECL_FUNC void eogllBuildAttributes(EogllAttribBuilder *builder, GLuint vao);

/**
 * @brief This struct represents a buffer object
 * @see eogllCreateBufferObject
 * @see eogllCreateBasicBufferObject
 *
 * This struct represents what I call a buffer object.
 * This encapsulates the vertex array object, the vertex buffer object, and the element buffer object (optional).
 * This struct allows for easy drawing of objects.
 *
 * Sample NORMAL (with indices) usage:
 * @code{.c}
 * unsigned int vao = eogllGenVertexArray();
 * unsigned int vbo = eogllGenBuffer(vao, GL_STATIC_DRAW, sizeof(vertices), vertices); // vertices is an array of floats
 * unsigned int ebo = eogllGenBuffer(vao, GL_STATIC_DRAW, sizeof(indices), indices); // indices is an array of unsigned ints
 * eogllBuildAttributes(&builder, vao); // builder is an EogllAttribBuilder
 * EogllBufferObject bufferObject = eogllCreateBufferObject(vao, vbo, ebo, sizeof(indices), GL_UNSIGNED_INT);
 * @endcode
 *
 * Sample BASIC (without indices) usage:
 * @code{.c}
 * unsigned int vao = eogllGenVertexArray();
 * unsigned int vbo = eogllGenBuffer(vao, GL_STATIC_DRAW, sizeof(vertices), vertices); // vertices is an array of floats
 * eogllBuildAttributes(&builder, vao); // builder is an EogllAttribBuilder
 * EogllBufferObject bufferObject = eogllCreateBasicBufferObject(vao, vbo, sizeof(vertices)/sizeof(float));
 * @endcode
 */
typedef EOGLL_DECL_STRUCT struct EogllBufferObject {
    /// The vertex array object
    unsigned int vao;
    /// The vertex buffer object
    unsigned int vbo;
    /// The element buffer object
    unsigned int ebo;
    /// The number of indices
    uint32_t numIndices;
    /// The type of the indices
    GLenum indicesType;
    /// Whether or not the buffer object has indices
    bool hasIndices;
} EogllBufferObject;

#define DEPRECATED HEDLEY_DEPRECATED_FOR(0.2.5, eogllCreateBufferObject)
/**
 * @brief Creates a buffer object with the given data
 * @param vertices The vertices
 * @param verticesSize The size of the vertices
 * @param indices The indices
 * @param indicesSize The size of the indices
 * @param builder The attribute builder to use
 * @param usage The usage
 * @param indicesType The type of the indices
 * @return The created buffer object
 * @see eogllCreateBasicBufferObject
 * @see eogllDrawBufferObject
 * @see eogllBindBufferObject
 * @see eogllDeleteBufferObject
 * @see EogllBufferObject
 * @see EogllAttribBuilder
 *
 * @deprecated This function is deprecated (since 0.2.5), use eogllCreateBufferObject instead
 *
 * This function creates a buffer object.
 * This function has been deprecated in favor of eogllCreateBufferObject or eogllCreateBasicBufferObject.
 */
EOGLL_DECL_FUNC_ND DEPRECATED EogllBufferObject eogllConstructBufferObject(void* vertices, GLsizeiptr verticesSize, void* indices, GLsizeiptr indicesSize, EogllAttribBuilder *builder, GLenum usage, GLenum indicesType);
#undef DEPRECATED

/**
 * @brief Creates a buffer object with the given data
 * @param vao The vertex array object to use
 * @param vbo The vertex buffer object to use
 * @param ebo The element buffer object to use
 * @param indicesSize The size of the indices
 * @param indicesType The type of the indices
 * @return The created buffer object
 * @see eogllCreateBasicBufferObject
 * @see eogllDrawBufferObject
 * @see eogllBindBufferObject
 * @see eogllDeleteBufferObject
 * @see EogllBufferObject
 *
 * This function creates a buffer object.
 */
EOGLL_DECL_FUNC_ND EogllBufferObject eogllCreateBufferObject(unsigned int vao, unsigned int vbo, unsigned int ebo, GLsizeiptr indicesSize, GLenum indicesType);

/**
 * @brief Creates a basic buffer object with the given data
 * @param vao The vertex array object to use
 * @param vbo The vertex buffer object to use
 * @param numVertices The number of vertices
 * @return The created buffer object
 * @see eogllCreateBufferObject
 * @see eogllDrawBasicBufferObject
 * @see eogllBindBufferObject
 * @see eogllDeleteBufferObject
 * @see EogllBufferObject
 *
 * This function creates a basic buffer object.
 */
EOGLL_DECL_FUNC_ND EogllBufferObject eogllCreateBasicBufferObject(unsigned int vao, unsigned int vbo, GLsizeiptr numVertices);

/**
 * @brief Draws a buffer object
 * @param bufferObject The buffer object to draw
 * @param mode The mode to use
 * @see eogllCreateBufferObject
 * @see eogllCreateBasicBufferObject
 * @see eogllBindBufferObject
 * @see eogllDeleteBufferObject
 * @see EogllBufferObject
 *
 * This function draws a buffer object.
 */
EOGLL_DECL_FUNC void eogllDrawBufferObject(EogllBufferObject* bufferObject, GLenum mode);

/**
 * @brief Draws a basic buffer object
 * @param bufferObject The buffer object to draw
 * @param mode The mode to use
 * @see eogllCreateBufferObject
 * @see eogllCreateBasicBufferObject
 * @see eogllBindBufferObject
 * @see eogllDeleteBufferObject
 * @see EogllBufferObject
 *
 * This function draws a basic buffer object.
 */
EOGLL_DECL_FUNC void eogllDrawBasicBufferObject(EogllBufferObject* bufferObject, GLenum mode);

/**
 * @brief Binds a buffer object
 * @param bufferObject The buffer object to bind
 * @see eogllCreateBufferObject
 * @see eogllCreateBasicBufferObject
 * @see eogllDrawBufferObject
 * @see eogllDrawBasicBufferObject
 * @see eogllDeleteBufferObject
 * @see EogllBufferObject
 *
 * This function binds a buffer object.
 * This isn't used in normal drawing with EOGLL, but can be used for custom drawing.
 */
EOGLL_DECL_FUNC void eogllBindBufferObject(EogllBufferObject* bufferObject);

/**
 * @brief Deletes a buffer object
 * @param bufferObject The buffer object to delete
 * @see eogllCreateBufferObject
 * @see eogllCreateBasicBufferObject
 * @see eogllDrawBufferObject
 * @see eogllDrawBasicBufferObject
 * @see eogllBindBufferObject
 * @see EogllBufferObject
 *
 * This function deletes a buffer object.
 * This function should be called when you are done with the buffer object.
 */
EOGLL_DECL_FUNC void eogllDeleteBufferObject(EogllBufferObject* bufferObject);

/**
 * @brief This will enable or disable wireframe mode
 * @param enable Whether or not to enable wireframe mode
 *
 * This function will enable or disable wireframe mode.
 * This function is useful for debugging.
 */
EOGLL_DECL_FUNC void eogllSetWireframeMode(bool enable);

/**
 * @brief This struct represents a texture
 * @see eogllCreateTexture
 * @see eogllBindTexture
 * @see eogllDeleteTexture
 *
 * This struct represents a texture.
 * This struct is used to handle all texture related things.
 * Sample usage:
 * @code{.c}
 * // init code
 * EogllTexture* texture = eogllCreateTexture("resources/textures/texture.png");
 *
 * // before drawing
 * eogllBindTexture(texture);
 *
 * // or if you want to use a specific texture unit and uniform
 * eogllBindTextureUniform(texture, shader, "texture", 0);
 *
 */
typedef EOGLL_DECL_STRUCT struct EogllTexture {
    /// The id of the texture
    unsigned int id;

    /// The width of the texture
    int width;

    /// The height of the texture
    int height;

    /// The number of channels in the texture (3 for RGB, 4 for RGBA)
    int channels;

    /// The format of the texture (GL_RGB, GL_RGBA)
    GLint format;

    /// GL_MAX_TEXTURE_IMAGE_UNITS value, used to check if the texture unit is valid
    int maxTextureUnits;
} EogllTexture;

/**
 * @brief Creates a texture
 * @param path The path to the texture
 * @return The created texture
 * @see eogllBindTexture
 * @see eogllDeleteTexture
 * @see EogllTexture
 *
 * This function creates a texture.
 */
EOGLL_DECL_FUNC_ND EogllTexture* eogllCreateTexture(const char* path);

/**
 * @brief Binds a texture
 * @param texture The texture to bind
 * @see eogllCreateTexture
 * @see eogllDeleteTexture
 * @see EogllTexture
 *
 * This function binds a texture.
 */
EOGLL_DECL_FUNC void eogllBindTexture(EogllTexture* texture);

/**
 * @brief Deletes a texture
 * @param texture The texture to delete
 * @see eogllCreateTexture
 * @see eogllBindTexture
 * @see EogllTexture
 *
 * This function deletes a texture.
 * This function should be called when you are done with the texture.
 */
EOGLL_DECL_FUNC void eogllDeleteTexture(EogllTexture* texture);

/**
 * @brief Binds a texture to a specific texture unit and uniform
 * @param texture The texture to bind
 * @param shader The shader program to use
 * @param name The name of the uniform
 * @param index The index of the texture unit
 * @see eogllCreateTexture
 * @see eogllBindTexture
 * @see eogllDeleteTexture
 * @see EogllTexture
 *
 * This function binds a texture to a specific texture unit and uniform.
 * This function does check if the texture unit is valid (below GL_MAX_TEXTURE_IMAGE_UNITS value).
 */
EOGLL_DECL_FUNC void eogllBindTextureUniform(EogllTexture* texture, EogllShaderProgram* shader, const char* name, unsigned int index);

#define DEPRECATED HEDLEY_DEPRECATED_FOR(0.2.8, mat4)
/**
 * @brief A struct that represents a view matrix
 * @see eogllCreateView
 *
 * @deprecated This struct is deprecated (since 0.2.8), use mat4 instead
 *
 * This struct is used to handle all view matrix related things.
 */
typedef EOGLL_DECL_STRUCT struct EogllView { // basically a camera
    /// The view matrix
    mat4 view;
} EogllView;

/**
 * @brief Creates a view matrix
 * @return The created view matrix
 * @see EogllView
 *
 * @deprecated This function is deprecated (since 0.2.8), use mat4 instead
 *
 * This function creates a view matrix.
 */
EOGLL_DECL_FUNC_ND DEPRECATED EogllView eogllCreateView();

/**
 * @brief Translates a view matrix
 * @param view The view matrix to translate
 * @param x The x component of the translation
 * @param y The y component of the translation
 * @param z The z component of the translation
 * @see eogllCreateView
 * @see EogllView
 *
 * @deprecated This function is deprecated (since 0.2.8), use mat4 instead
 *
 * This function translates the given view matrix.
 */
EOGLL_DECL_FUNC DEPRECATED void eogllTranslateView3f(EogllView* view, float x, float y, float z);

/**
 * @brief Translates a view matrix
 * @param view The view matrix to translate
 * @param translation The translation
 * @see eogllCreateView
 * @see EogllView
 *
 * @deprecated This function is deprecated (since 0.2.8), use mat4 instead
 *
 * This function translates the given view matrix.
 */
EOGLL_DECL_FUNC DEPRECATED void eogllTranslateView(EogllView* view, vec3 translation);

/**
 * @brief Rotates a view matrix
 * @param view The view matrix to rotate
 * @param angle The angle to rotate by
 * @param x The x component of the axis to rotate around
 * @param y The y component of the axis to rotate around
 * @param z The z component of the axis to rotate around
 * @see eogllCreateView
 * @see EogllView
 *
 * @deprecated This function is deprecated (since 0.2.8), use mat4 instead
 *
 * This function rotates the given view matrix.
 */
EOGLL_DECL_FUNC DEPRECATED void eogllRotateView3f(EogllView* view, float angle, float x, float y, float z);

/**
 * @brief Rotates a view matrix
 * @param view The view matrix to rotate
 * @param angle The angle to rotate by
 * @param axis The axis to rotate around
 * @see eogllCreateView
 * @see EogllView
 *
 * @deprecated This function is deprecated (since 0.2.8), use mat4 instead
 *
 * This function rotates the given view matrix.
 */
EOGLL_DECL_FUNC DEPRECATED void eogllRotateView(EogllView* view, float angle, vec3 axis);

/**
 * @brief Scales a view matrix
 * @param view The view matrix to scale
 * @param x The x component of the scale
 * @param y The y component of the scale
 * @param z The z component of the scale
 * @see eogllCreateView
 * @see EogllView
 *
 * @deprecated This function is deprecated (since 0.2.8), use mat4 instead
 *
 * This function scales the given view matrix.
 */
EOGLL_DECL_FUNC DEPRECATED void eogllScaleView3f(EogllView* view, float x, float y, float z);

/**
 * @brief Scales a view matrix
 * @param view The view matrix to scale
 * @param scale The scale
 * @see eogllCreateView
 * @see EogllView
 *
 * @deprecated This function is deprecated (since 0.2.8), use mat4 instead
 *
 * This function scales the given view matrix.
 */
EOGLL_DECL_FUNC DEPRECATED void eogllScaleView(EogllView* view, vec3 scale);

/**
 * @brief Updates a view matrix
 * @param view The view matrix to update
 * @param shader The shader program to use
 * @param name The name of the uniform
 * @see eogllCreateView
 * @see EogllView
 *
 * @deprecated This function is deprecated (since 0.2.8), use mat4 instead
 *
 * This function updates the given view matrix.
 */
EOGLL_DECL_FUNC DEPRECATED void eogllUpdateViewMatrix(EogllView* view, EogllShaderProgram* shader, const char* name);
#undef DEPRECATED

/**
 * @brief A struct that represents a projection matrix
 * @see eogllCreateProjection
 *
 * This struct is used to handle all projection matrix related things.
 *
 * Sample usage:
 * @code{.c}
 * // init code
 * EogllProjection* projection = eogllCreateProjection(45.0f, 0.1f, 100.0f);
 *
 * // before drawing
 * eogllUpdateProjectionMatrix(projection, shader, "projection", width, height); // mat4 projection in the shader
 * @endcode
 */
typedef EOGLL_DECL_STRUCT struct EogllProjection {
    /// The fov of the projection matrix
    float fov;
    /// The near of the projection matrix
    float near;
    /// The far of the projection matrix
    float far;

    /// The projection matrix
    mat4 projection;

    /// The last width used to update the projection matrix
    uint32_t lastWidth;
    /// The last height used to update the projection matrix
    uint32_t lastHeight;
} EogllProjection;

/**
 * @brief Creates a projection matrix
 * @param fov The fov of the projection matrix
 * @param near The near of the projection matrix
 * @param far The far of the projection matrix
 * @return The created projection matrix
 * @see EogllProjection
 *
 * This function creates a projection matrix.
 */
EOGLL_DECL_FUNC_ND EogllProjection eogllPerspectiveProjection(float fov, float near, float far);

/**
 * @brief Updates a projection matrix
 * @param projection The projection matrix to update
 * @param shader The shader program to use
 * @param name The name of the uniform
 * @param width The width of the window
 * @param height The height of the window
 *
 * This function updates the given projection matrix.
 * This function should be called before drawing.
 */
EOGLL_DECL_FUNC void eogllUpdateProjectionMatrix(EogllProjection* projection, EogllShaderProgram* shader, const char* name, uint32_t width, uint32_t height);

/**
 * @brief A struct that represents a model matrix
 * @see eogllCreateModel
 *
 * This struct is used to handle all model matrix related things.
 *
 * Sample usage:
 * @code{.c}
 * // init code
 * EogllModel* model = eogllCreateModel();
 *
 * // before drawing
 * eogllRotateModel(model, (vec3){0.0f, 0.2f, 0.0f}); // rotates a bit
 * eogllUpdateModelMatrix(model, shader, "model"); // mat4 model in the shader
 * @endcode
 */
typedef EOGLL_DECL_STRUCT struct EogllModel {
    /// The position
    vec3 pos;
    /// The rotation
    vec3 rot;
    /// The scale
    vec3 scale;
} EogllModel;

/**
 * @brief Creates a model matrix
 * @return The created model matrix
 * @see EogllModel
 *
 * This function creates a model matrix.
 */
EOGLL_DECL_FUNC_ND EogllModel eogllCreateModel();

/**
 * @brief Rotates a model matrix
 * @param model The model matrix to rotate
 * @param angle The angle to rotate by
 * @param x The x component of the axis to rotate around
 * @param y The y component of the axis to rotate around
 * @param z The z component of the axis to rotate around
 *
 * This function rotates the given model matrix.
 */
EOGLL_DECL_FUNC void eogllRotateModel3f(EogllModel* model, float angle, float x, float y, float z);

/**
 * @brief Rotates a model matrix
 * @param model The model matrix to rotate
 * @param angle The angle to rotate by
 * @param axis The axis to rotate around
 *
 * This function rotates the given model matrix.
 */
EOGLL_DECL_FUNC void eogllRotateModel(EogllModel* model, float angle, vec3 axis);

/**
 * @brief Translates a model matrix
 * @param model The model matrix to translate
 * @param x The x component of the translation
 * @param y The y component of the translation
 * @param z The z component of the translation
 *
 * This function translates the given model matrix.
 */
EOGLL_DECL_FUNC void eogllTranslateModel3f(EogllModel* model, float x, float y, float z);

/**
 * @brief Translates a model matrix
 * @param model The model matrix to translate
 * @param translation The translation
 *
 * This function translates the given model matrix.
 */
EOGLL_DECL_FUNC void eogllTranslateModel(EogllModel* model, vec3 translation);

/**
 * @brief Scales a model matrix
 * @param model The model matrix to scale
 * @param x The x component of the scale
 * @param y The y component of the scale
 * @param z The z component of the scale
 *
 * This function scales the given model matrix.
 */
EOGLL_DECL_FUNC void eogllScaleModel3f(EogllModel* model, float x, float y, float z);

/**
 * @brief Scales a model matrix
 * @param model The model matrix to scale
 * @param scale The scale
 *
 * This function scales the given model matrix.
 */
EOGLL_DECL_FUNC void eogllScaleModel(EogllModel* model, vec3 scale);

/**
 * @brief Updates a model matrix
 * @param model The model matrix to update
 * @param shader The shader program to use
 * @param name The name of the uniform
 *
 * This function updates the given model matrix.
 * This function should be called before drawing.
 */
EOGLL_DECL_FUNC void eogllUpdateModelMatrix(EogllModel* model, EogllShaderProgram* shader, const char* name);

/**
 * @brief Enables depth testing
 *
 * This function enables depth testing.
 */
EOGLL_DECL_FUNC void eogllEnableDepth();

/**
 * @brief Enables transparency
 *
 * This function enables transparency.
 */
EOGLL_DECL_FUNC void eogllEnableTransparency();

/**
 * @brief Enables face culling
 *
 * This function enables face culling.
 */
EOGLL_DECL_FUNC void eogllEnableFaceCulling();

/**
 * @brief A struct that represents a camera
 * @see eogllCreateCamera
 *
 * This struct is used to handle all camera related things.
 */
typedef EOGLL_DECL_STRUCT struct EogllCamera {
    /// The position of the camera
    vec3 pos;
    /// The front vector of the camera
    vec3 front;
    /// The up vector of the camera
    vec3 up;
    /// The right vector of the camera
    vec3 right;
    /// The world up vector of the camera
    vec3 worldUp;
    /// The yaw of the camera
    float yaw;
    /// The pitch of the camera
    float pitch;
} EogllCamera;

/**
 * @brief A struct that represents a camera matrix
 * @see eogllCameraMatrix
 *
 * This struct is used to return a matrix from eogllCameraMatrix.
 * Since the mat4 is an array type, it can't be returned from a function.
 */
typedef EOGLL_DECL_STRUCT struct EogllCameraMatrix {
    /// The view matrix
    mat4 view;
} EogllCameraMatrix;

/**
 * @brief Creates a camera
 * @return The created camera
 * @see EogllCamera
 *
 * This function creates a camera.
 */
EOGLL_DECL_FUNC_ND EogllCamera eogllCreateCamera();

/**
 * @brief Gets the camera matrix
 * @param camera The camera to get the matrix from
 * @return The camera matrix
 * @see EogllCamera
 *
 * This function gets the camera matrix.
 */
EOGLL_DECL_FUNC_ND EogllCameraMatrix eogllCameraMatrix(EogllCamera* camera);

/**
 * @brief Translates a camera
 * @param camera The camera to translate
 * @param x The x component of the translation
 * @param y The y component of the translation
 * @param z The z component of the translation
 *
 * This function translates the given camera.
 */
EOGLL_DECL_FUNC void eogllTranslateCamera3f(EogllCamera* camera, float x, float y, float z);

/**
 * @brief Translates a camera
 * @param camera The camera to translate
 * @param translation The translation
 *
 * This function translates the given camera.
 */
EOGLL_DECL_FUNC void eogllTranslateCamera(EogllCamera* camera, vec3 translation);

/**
 * @brief Upadtes the camera vectors
 * @param camera The camera to update the vectors for
 *
 * This function is used internally to update the camera vectors after using yaw or pitch.
 * This function is not meant to be used by the user.
 */
EOGLL_DECL_FUNC void eogllUpdateCameraVectors(EogllCamera* camera);

/**
 * @brief Yaws a camera
 * @param camera The camera to yaw
 * @param amount The amount to yaw by
 *
 * This function yaws the given camera.
 */
EOGLL_DECL_FUNC void eogllYawCamera(EogllCamera* camera, float amount);

/**
 * @brief Pitches a camera
 * @param camera The camera to pitch
 * @param amount The amount to pitch by
 *
 * This function pitches the given camera.
 */
EOGLL_DECL_FUNC void eogllPitchCamera(EogllCamera* camera, float amount);

/**
 * @brief An enum that represents a camera direction
 *
 * This enum is used to specify a camera direction.
 * This enum is used by eogllMoveCamera.
 */
typedef EOGLL_DECL_ENUM enum EogllCameraDirection {
    /// The camera direction forward
    EOGLL_FORWARD,
    /// The camera direction backward
    EOGLL_BACKWARD,
    /// The camera direction left
    EOGLL_LEFT,
    /// The camera direction right
    EOGLL_RIGHT,
    /// The camera direction up
    EOGLL_UP,
    /// The camera direction down
    EOGLL_DOWN
} EogllCameraDirection;

/**
 * @brief Moves a camera
 * @param cam The camera to move
 * @param dir The direction to move in
 * @param amount The amount to move by
 *
 * This function moves the given camera.
 */
EOGLL_DECL_FUNC void eogllMoveCamera(EogllCamera* cam, EogllCameraDirection dir, float amount);

/**
 * @brief Updates a camera matrix
 * @param camera The camera to update
 * @param program The shader program to use
 * @param name The name of the uniform
 *
 * This function updates the given camera matrix.
 * This function should be called before drawing.
 */
EOGLL_DECL_FUNC void eogllUpdateCameraMatrix(EogllCamera* camera, EogllShaderProgram* program, const char* name);

// Object loading stuff

// EogllObjectAttrs is very similar to EogllAttribBuilder, but it also stores the type of the attributes (where it comes from in the obj file)

//EogllObjectAttrs objMode = eogllCreateObjectAttrs();
//eogllAddObjectAttr(&objMode, GL_FLOAT, 3, EOGLL_ATTR_POSITION);
//eogllAddObjectAttr(&objMode, GL_FLOAT, 2, EOGLL_ATTR_TEXTURE);
//EogllBufferObject bufferObject = eogllBufferObjectLoad("resources/models/cube.obj", objMode);

/**
 * @brief An enum that represents an object attribute type
 *
 * This enum is used to specify an object attribute type.
 * This enum is used by EogllObjectAttrs.
 */
typedef EOGLL_DECL_ENUM enum EogllObjectAttrType {
    /// The default object attribute type
    EOGLL_ATTR_NONE,
    /// The position object attribute type
    EOGLL_ATTR_POSITION,
    /// The texture object attribute type
    EOGLL_ATTR_TEXTURE,
    /// The normal object attribute type
    EOGLL_ATTR_NORMAL
} EogllObjectAttrType;

/**
 * @brief Internal object loading struct for indexing
 * @see EogllObjectAttrs
 * @see eogllLoadBufferObject
 *
 * This struct is used internally by eogllLoadBufferObject.
 */
typedef struct EogllObjectIndex {
    /// The geometry index (position)
    unsigned int geomIndex;
    /// The normal index
    unsigned int normalIndex;
    /// The texture coordinate index
    unsigned int texCoordIndex;
    /// Whether or not the object has normals
    bool hasNormal;
    /// Whether or not the object has texture coordinates
    bool hasTexCoord;
} EogllObjectIndex;

/**
 * @brief Internal object loading struct for faces
 * @see EogllObjectAttrs
 * @see eogllLoadBufferObject
 *
 * This struct is used internally by eogllLoadBufferObject.
 */
typedef struct EogllObjectFileFace {
    /// The number of indices
    unsigned int numIndices;
    /// The indices
    EogllObjectIndex *indices;
} EogllObjectFileFace;

/**
 * @brief Internal object loading struct for storing position data
 * @see EogllObjectAttrs
 * @see eogllLoadBufferObject
 *
 * This struct is used internally by eogllLoadBufferObject.
 */
typedef struct EogllObjectPosition {
    /// The x component of the position
    float x;
    /// The y component of the position
    float y;
    /// The z component of the position
    float z;
    /// The w component of the position
    float w;
    /// Whether or not the object has a w component
    bool hasW;
} EogllObjectPosition;

/**
 * @brief Internal object loading struct for storing normal data
 * @see EogllObjectAttrs
 * @see eogllLoadBufferObject
 *
 * This struct is used internally by eogllLoadBufferObject.
 */
typedef struct EogllObjectNormal {
    /// The x component of the normal
    float x;
    /// The y component of the normal
    float y;
    /// The z component of the normal
    float z;
} EogllObjectNormal;

/**
 * @brief Internal object loading struct for storing texture coordinate data
 * @see EogllObjectAttrs
 * @see eogllLoadBufferObject
 *
 * This struct is used internally by eogllLoadBufferObject.
 */
typedef struct EogllObjectTexCoord {
    /// The u component of the texture coordinate
    float u;
    /// The v component of the texture coordinate
    float v;
    /// The w component of the texture coordinate
    float w;
    /// Whether or not the object has a v component
    bool hasV;
    /// Whether or not the object has a w component
    bool hasW;
} EogllObjectTexCoord;

/**
 * @brief Internal object loading struct for storing all of the object data
 * @see EogllObjectAttrs
 * @see eogllLoadBufferObject
 *
 * This struct is used internally by eogllLoadBufferObject.
 */
typedef struct EogllObjectFileData {
    /// The number of faces
    unsigned int numFaces;
    /// The faces
    EogllObjectFileFace *faces;
    /// The number of positions
    unsigned int numPositions;
    /// The positions
    EogllObjectPosition *positions;
    /// The number of normals
    unsigned int numNormals;
    /// The normals
    EogllObjectNormal *normals;
    /// The number of texture coordinates
    unsigned int numTexCoords;
    /// The texture coordinates
    EogllObjectTexCoord *texCoords;
} EogllObjectFileData;

/**
 * @brief Parses an object file
 * @param file The file to parse
 * @param data The data to store the parsed data in
 * @return EOGLL_SUCCESS if successful, EOGLL_FAILURE if not
 * @see EogllObjectFileData
 * @see eogllLoadBufferObject
 *
 * This function parses an object file.
 * This function is used internally by eogllLoadBufferObject.
 */
EOGLL_DECL_FUNC_ND EogllResult eogllParseObjectFile(FILE* file, EogllObjectFileData *data);

/**
 * @brief Deletes an object file data struct
 * @param data The object file data struct to delete
 * @see EogllObjectFileData
 * @see eogllLoadBufferObject
 *
 * This function deletes an object file data struct.
 * This function is used internally by eogllLoadBufferObject.
 */
EOGLL_DECL_FUNC void eogllDeleteObjectFileData(EogllObjectFileData *data);

/**
 * @brief A struct that represents object attributes
 * @see eogllCreateObjectAttrs
 * @see eogllAddObjectAttr
 *
 * This struct is used to handle object attributes.
 * Object attributes are similar to vertex attributes, but they also store the type of the attribute (where it comes from in the obj file).
 * This allows us to load object files with customizable attributes (like position, texture, and normal).
 *
 * TODO: specify the number of positions (normally 3 or 4) to use for the position attribute + same for texture and normal
 */
typedef EOGLL_DECL_STRUCT struct EogllObjectAttrs {
    /// The types of the attributes
    EogllObjectAttrType types[8];
    /// The number of attributes
    uint32_t numTypes;
    /// The attribute builder
    EogllAttribBuilder builder;
} EogllObjectAttrs;

/**
 * @brief Converts an object file data struct to vertices and indices
 * @param data The object file data struct to convert
 * @param attrs The object attributes to use
 * @param vertices Resulting vertices
 * @param numVertices Resulting number of vertices
 * @param indices Resulting indices
 * @param numIndices Resulting number of indices
 * @return EOGLL_SUCCESS if successful, EOGLL_FAILURE if not
 *
 * This function converts an object file data struct to vertices and indices.
 * If something goes wrong with object loading (SEGFAULT or alike), this function is probably the culprit.
 * This function is still a work in progress, and is not optimized or hardly tested.
 * Bad input will easily cause a SEGFAULT.
 * This function is used internally by eogllLoadObjectFile.
 */
EOGLL_DECL_FUNC_ND EogllResult eogllObjectFileDataToVertices(EogllObjectFileData *data, EogllObjectAttrs attrs, float** vertices, uint32_t* numVertices, unsigned int** indices, uint32_t* numIndices);

/**
 * @brief Loads an object file
 * @param path The path to the object file
 * @param attrs The object attributes to use
 * @param vertices Resulting vertices
 * @param numVertices Resulting number of vertices
 * @param indices Resulting indices
 * @param numIndices Resulting number of indices
 * @return EOGLL_SUCCESS if successful, EOGLL_FAILURE if not
 * @see EogllObjectAttrs
 * @see eogllObjectFileDataToVertices
 * @see eogllParseObjectFile
 *
 * Uses eogllParseObjectFile and eogllObjectFileDataToVertices to load an object file.
 * This function is used internally by eogllLoadBufferObject.
 */
EOGLL_DECL_FUNC_ND EogllResult eogllLoadObjectFile(const char* path, EogllObjectAttrs attrs, float** vertices, uint32_t* numVertices, unsigned int** indices, uint32_t* numIndices);

/**
 * @brief Creates an object attributes struct
 * @return The created object attributes struct
 * @see EogllObjectAttrs
 * @see eogllAddObjectAttr
 *
 * This function creates an object attributes struct.
 */
EOGLL_DECL_FUNC_ND EogllObjectAttrs eogllCreateObjectAttrs();

/**
 * @brief Adds an object attribute to an object attributes struct
 * @param attrs The object attributes struct to add the attribute to
 * @param type The type of the attribute
 * @param num The number of components in the attribute
 * @param attrType The type of the attribute (where it comes from in the obj file)
 * @see EogllObjectAttrs
 * @see eogllCreateObjectAttrs
 *
 * This function adds an object attribute to an object attributes struct.
 */
EOGLL_DECL_FUNC void eogllAddObjectAttr(EogllObjectAttrs* attrs, GLenum type, GLint num, EogllObjectAttrType attrType);

/**
 * @brief Loads a buffer object from an object file
 * @param path The path to the object file
 * @param attrs The object attributes to use
 * @param usage The usage
 * @return The created buffer object
 * @see EogllObjectAttrs
 * @see eogllLoadObjectFile
 * @see eogllCreateBufferObject
 *
 * This function loads a buffer object from an object file.
 */
EOGLL_DECL_FUNC_ND EogllBufferObject eogllLoadBufferObject(const char* path, EogllObjectAttrs attrs, GLenum usage);

#ifdef __cplusplus
}
#endif

#endif // _EOGLL_H_