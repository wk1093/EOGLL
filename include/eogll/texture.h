/**
 * @file texture.h
 * @brief EOGLL texture header file
 * @date 2024-01-28
 *
 * EOGLL texture header file
 */

#pragma once
#ifndef _EOGLL_TEXTURE_H_
#define _EOGLL_TEXTURE_H_

#include "pch.h"
#include "shader.h"

#ifdef __cplusplus
extern "C" {
#endif

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
 * @endcode
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
 * @brief Creates a texture from a buffer
 * @param buffer The buffer to create the texture from
 * @param size The length of the buffer
 * @return The created texture
 * @see eogllBindTexture
 * @see eogllCreateTexture
 */
EOGLL_DECL_FUNC_ND EogllTexture* eogllCreateTextureFromBuffer(const uint8_t* buffer, size_t size);

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


#ifdef __cplusplus
}
#endif

#endif //_EOGLL_TEXTURE_H_
