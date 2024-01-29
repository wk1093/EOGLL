/**
 * @file camera.h
 * @brief EOGLL camera header file
 * @date 2024-01-28
 *
 * EOGLL camera header file
 */

#pragma once
#ifndef _EOGLL_CAMERA_H_
#define _EOGLL_CAMERA_H_

#include "pch.h"
#include "shader.h"

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif


#endif //_EOGLL_CAMERA_H_
