/**
 * @file shader.h
 * @brief EOGLL shader header file
 * @date 2024-01-28
 *
 * EOGLL shader header file
 */

#pragma once
#ifndef _EOGLL_SHADER_H_
#define _EOGLL_SHADER_H_

#include "pch.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief A struct that represents a shader program
 * @see eogllLinkProgram
 * @see eogllLinkProgramFromFile
 * @see eogllDeleteProgram
 * @see eogllUseProgram
 *
 * This struct is used to handle all shader related things
 */
typedef EOGLL_DECL_STRUCT struct EogllShaderProgram {
    /// The id of the shader program
    unsigned int id;
    int vertexStatus;
    int fragmentStatus;
    int programStatus;
} EogllShaderProgram;

/**
 * @brief Links a shader program
 * @param vertexShaderSource The source of the vertex shader
 * @param fragmentShaderSource The source of the fragment shader
 * @return The linked shader program
 * @see eogllLinkProgramFromFile
 * @see eogllDeleteProgram
 * @see eogllUseProgram
 * @see EogllShaderProgram
 *
 * This function links a shader program with the given vertex and fragment shader sources.
 */
EOGLL_DECL_FUNC_ND EogllShaderProgram* eogllLinkProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

/**
 * @brief Links a shader program from files
 * @param vertexShaderPath The path to the vertex shader
 * @param fragmentShaderPath The path to the fragment shader
 * @return The linked shader program
 * @see eogllLinkProgram
 * @see eogllDeleteProgram
 * @see eogllUseProgram
 * @see EogllShaderProgram
 * @see eogllReadFile
 *
 * This function links a shader program with the given vertex and fragment shader paths.
 */
EOGLL_DECL_FUNC_ND EogllShaderProgram* eogllLinkProgramFromFile(const char* vertexShaderPath, const char* fragmentShaderPath);

/**
 * @brief Deletes a shader program
 * @param shader The shader program to delete
 * @see eogllLinkProgram
 * @see eogllLinkProgramFromFile
 * @see eogllUseProgram
 * @see EogllShaderProgram
 *
 * This function deletes the given shader program.
 * This function should be called when you are done with the shader program.
 */
EOGLL_DECL_FUNC void eogllDeleteProgram(EogllShaderProgram* shader);

/**
 * @brief Uses a shader program
 * @param shader The shader program to use
 * @see eogllLinkProgram
 * @see eogllLinkProgramFromFile
 * @see eogllDeleteProgram
 * @see EogllShaderProgram
 *
 * This function uses the given shader program.
 * This function should be called before you draw anything using the shader program.
 */
EOGLL_DECL_FUNC void eogllUseProgram(EogllShaderProgram* shader);

/**
 * @brief Sets a uniform matrix 4x4
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param matrix The matrix to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniformMatrix4fv(EogllShaderProgram* shader, const char* name, mat4 matrix);

/**
 * @brief Sets a uniform matrix 3x3
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param matrix The matrix to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniformMatrix3fv(EogllShaderProgram* shader, const char* name, mat3 matrix);

/**
 * @brief Sets a uniform matrix 2x2
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param matrix The matrix to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniformMatrix2fv(EogllShaderProgram* shader, const char* name, mat2 matrix);

/**
 * @brief Sets a uniform vec4 (given 4 floats)
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param x The x component of the vector
 * @param y The y component of the vector
 * @param z The z component of the vector
 * @param w The w component of the vector
 */
EOGLL_DECL_FUNC void eogllSetUniform4f(EogllShaderProgram* shader, const char* name, float x, float y, float z, float w);

/**
 * @brief Sets a uniform vec4 (given a vec4)
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param vector The vector to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniform4fv(EogllShaderProgram* shader, const char* name, vec4 vector);

/**
 * @brief Sets a uniform vec3 (given 3 floats)
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param x The x component of the vector
 * @param y The y component of the vector
 * @param z The z component of the vector
 */
EOGLL_DECL_FUNC void eogllSetUniform3f(EogllShaderProgram* shader, const char* name, float x, float y, float z);

/**
 * @brief Sets a uniform vec3 (given a vec3)
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param vector The vector to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniform3fv(EogllShaderProgram* shader, const char* name, vec3 vector);

/**
 * @brief Sets a uniform vec2 (given 2 floats)
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param x The x component of the vector
 * @param y The y component of the vector
 */
EOGLL_DECL_FUNC void eogllSetUniform2f(EogllShaderProgram* shader, const char* name, float x, float y);

/**
 * @brief Sets a uniform vec2 (given a vec2)
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param vector The vector to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniform2fv(EogllShaderProgram* shader, const char* name, vec2 vector);

/**
 * @brief Sets a uniform float
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param x The float to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniform1f(EogllShaderProgram* shader, const char* name, float x);

/**
 * @brief Sets a uniform float array
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param vector The array to set the uniform to
 * @param count The number of elements in the array
 */
EOGLL_DECL_FUNC void eogllSetUniform1fv(EogllShaderProgram* shader, const char* name, float* vector, GLsizei count);

/**
 * @brief Sets a uniform int
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param x The int to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniform1i(EogllShaderProgram* shader, const char* name, int x);

/**
 * @brief Sets a uniform int array
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param vector The array to set the uniform to
 * @param count The number of elements in the array
 */
EOGLL_DECL_FUNC void eogllSetUniform1iv(EogllShaderProgram* shader, const char* name, int* vector, GLsizei count);

/**
 * @brief Sets a uniform unsigned int
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param x The unsigned int to set the uniform to
 */
EOGLL_DECL_FUNC void eogllSetUniform1ui(EogllShaderProgram* shader, const char* name, unsigned int x);

/**
 * @brief Sets a uniform unsigned int array
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param vector The array to set the uniform to
 * @param count The number of elements in the array
 */
EOGLL_DECL_FUNC void eogllSetUniform1uiv(EogllShaderProgram* shader, const char* name, unsigned int* vector, GLsizei count);

/**
 * @brief Sets a uniform list of vec2
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param vectors The list of vectors to set the uniform to
 * @param count The number of elements in the list
 */
EOGLL_DECL_FUNC void eogllSetUniform2fl(EogllShaderProgram* shader, const char* name, vec2* vectors, GLsizei count);

/**
 * @brief Sets a uniform list of vec3
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param vectors The list of vectors to set the uniform to
 * @param count The number of elements in the list
 */
EOGLL_DECL_FUNC void eogllSetUniform3fl(EogllShaderProgram* shader, const char* name, vec3* vectors, GLsizei count);

/**
 * @brief Sets a uniform list of vec4
 * @param shader The shader program to set the uniform for
 * @param name The name of the uniform
 * @param vectors The list of vectors to set the uniform to
 * @param count The number of elements in the list
 */
EOGLL_DECL_FUNC void eogllSetUniform4fl(EogllShaderProgram* shader, const char* name, vec4* vectors, GLsizei count);

#ifdef __cplusplus
}
#endif

#endif //_EOGLL_SHADER_H_
