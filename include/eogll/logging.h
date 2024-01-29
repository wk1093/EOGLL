/**
 * @file logging.h
 * @brief EOGLL logging header file
 * @date 2024-01-28
 *
 * EOGLL logging header file
 */

#pragma once
#ifndef _EOGLL_LOGGING_H_
#define _EOGLL_LOGGING_H_

#include "pch.h"

#ifdef __cplusplus
extern "C" {
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

#ifdef __cplusplus
}
#endif

#endif //_EOGLL_LOGGING_H_
