/**
 * @file buffer_object.h
 * @brief EOGLL buffer object header file
 * @date 2024-01-28
 *
 * EOGLL buffer object header file
 */

#pragma once
#ifndef _EOGLL_BUFFER_OBJECT_H_
#define _EOGLL_BUFFER_OBJECT_H_

#include "pch.h"

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif //_EOGLL_BUFFER_OBJECT_H_
