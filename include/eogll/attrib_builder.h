/**
 * @file attrib_builder.h
 * @brief EOGLL attribute builder header file
 * @date 2024-01-28
 *
 * EOGLL attribute builder header file
 */

#pragma once
#ifndef _EOGLL_ATTRIB_BUILDER_H_
#define _EOGLL_ATTRIB_BUILDER_H_

#include "pch.h"

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif //_EOGLL_ATTRIB_BUILDER_H_
