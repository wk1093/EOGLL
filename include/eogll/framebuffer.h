/**
 * @file framebuffer.h
 * @brief EOGLL framebuffer header file
 * @date 2024-03-22
 *
 * EOGLL framebuffer header file
 */

#pragma once
#ifndef _EOGLL_FRAMEBUFFER_H_
#define _EOGLL_FRAMEBUFFER_H_

#include "pch.h"
#include "window.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A struct that represents a framebuffer
 * @see eogllCreateFramebuffer
 * @see eogllDestroyFramebuffer
 * 
 * Can be used to create and handle framebuffers.
 */
typedef EOGLL_DECL_STRUCT struct EogllFramebuffer {
    /// @brief The framebuffer object
    GLuint fbo;
    /// @brief The texture object
    GLuint texture;
    /// @brief The renderbuffer object
    GLuint rbo;
    /// @brief The width of the framebuffer
    uint32_t width;
    /// @brief The height of the framebuffer
    uint32_t height;
} EogllFramebuffer;

/**
 * @brief Creates a framebuffer
 * @param width The width of the framebuffer
 * @param height The height of the framebuffer
 * @return A pointer to the created framebuffer
 * @see EogllFramebuffer
 * 
 * Creates a framebuffer with the specified width and height.
 */
EOGLL_DECL_FUNC_ND EogllFramebuffer* eogllCreateFramebuffer(uint32_t width, uint32_t height);

/**
 * @brief Destroys a framebuffer
 * @param framebuffer The framebuffer to destroy
 * @see EogllFramebuffer
 * 
 * Destroys the specified framebuffer.
 */
EOGLL_DECL_FUNC void eogllDestroyFramebuffer(EogllFramebuffer* framebuffer);

/**
 * @brief Binds a framebuffer
 * @param framebuffer The framebuffer to bind
 * @see EogllFramebuffer
 * 
 * Binds the specified framebuffer.
 */
EOGLL_DECL_FUNC void eogllBindFramebuffer(EogllFramebuffer* framebuffer);

/**
 * @brief Sets the current framebuffer to NULL/default
 * @see EogllFramebuffer
 * 
 * Sets the current framebuffer to NULL/default.
 */
EOGLL_DECL_FUNC void eogllUnbindFramebuffer();

/**
 * @brief Resizes a framebuffer
 * @param framebuffer The framebuffer to resize
 * @param width The new width of the framebuffer
 * @param height The new height of the framebuffer
 * @see EogllFramebuffer
 * 
 * Resizes the specified framebuffer to the specified width and height.
 */
EOGLL_DECL_FUNC void eogllFramebufferResize(EogllFramebuffer* framebuffer, uint32_t width, uint32_t height);

#ifdef __cplusplus
}
#endif

#endif //_EOGLL_FRAMEBUFFER_H_