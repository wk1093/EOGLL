/**
 * @file util.h
 * @brief EOGLL utilities header file
 * @date 2024-01-28
 *
 * EOGLL utilities header file
 */

#pragma once
#ifndef _EOGLL_UTIL_H_
#define _EOGLL_UTIL_H_

#include "pch.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reads a file into a char array
 * @param path The path to the file
 * @return The contents of the file as a char array (must be freed)
 * @note This function is used internally, but isn't meant to be used by the user
 */
EOGLL_DECL_FUNC_ND char* eogllReadFile(const char* path);

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

#ifdef __cplusplus
}
#endif

#endif //_EOGLL_UTIL_H_
