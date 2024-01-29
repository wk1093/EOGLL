/**
 * @file gl.h
 * @brief EOGLL gl header file
 * @date 2024-01-28
 *
 * EOGLL gl header file
 */

#pragma once
#ifndef _EOGLL_GL_H_
#define _EOGLL_GL_H_

#include "pch.h"

#ifdef __cplusplus
extern "C" {
#endif


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
 * @brief This will enable or disable wireframe mode
 * @param enable Whether or not to enable wireframe mode
 *
 * This function will enable or disable wireframe mode.
 * This function is useful for debugging.
 */
EOGLL_DECL_FUNC void eogllSetWireframeMode(bool enable);

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

#ifdef __cplusplus
}
#endif

#endif //_EOGLL_GL_H_
