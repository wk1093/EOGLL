/**
 * @file defines.h
 * @brief EOGLL definitions header file
 * @date 2024-01-28
 *
 * EOGLL definitions header file
 */

#pragma once
#ifndef _EOGLL_DEFINES_H_
#define _EOGLL_DEFINES_H_

#include <hedley.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Result type for EOGLL functions
 */
typedef uint8_t EogllResult;
/**
 * @brief Success constant for EOGLL functions
 */
#define EOGLL_SUCCESS 0
/**
 * @brief Failure constant for EOGLL functions
 */
#define EOGLL_FAILURE 1

/**
 * @brief No discard attribute for EOGLL functions
 */
#define EOGLL_NO_DISCARD HEDLEY_WARN_UNUSED_RESULT

/**
 * @brief Version number for comparing and testing EOGLL versions
 * This version number is not in a format meant for displaying/reading
 * This number is used for comparing or testing if a version is correct, newer, or older
 */
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

#ifdef __cplusplus
}
#endif

#endif //_EOGLL_DEFINES_H_
