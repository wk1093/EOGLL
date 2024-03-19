/**
 * @file transforms.h
 * @brief EOGLL shader header file
 * @date 2024-01-28
 *
 * EOGLL shader header file
 */

#pragma once
#ifndef _EOGLL_TRANSFORMS_H_
#define _EOGLL_TRANSFORMS_H_

#include "pch.h"
#include "shader.h"

#ifdef __cplusplus
extern "C" {
#endif

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
EOGLL_DECL_FUNC void eogllUpdateProjectionMatrix(const EogllProjection* projection, EogllShaderProgram* shader, const char* name, uint32_t width, uint32_t height);

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
EOGLL_DECL_FUNC void eogllUpdateModelMatrix(const EogllModel* model, EogllShaderProgram* shader, const char* name);

#ifdef __cplusplus
}
#endif

#endif //_EOGLL_TRANSFORMS_H_
