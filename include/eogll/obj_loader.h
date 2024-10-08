/**
 * @file obj_loader.h
 * @brief EOGLL object loading header file
 * @date 2024-01-28
 *
 * EOGLL object loading header file
 */

#pragma once
#ifndef _EOGLL_OBJ_LOADER_H_
#define _EOGLL_OBJ_LOADER_H_

#include "pch.h"
#include "attrib_builder.h"
#include "buffer_object.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief An enum that represents an object attribute type
 *
 * This enum is used to specify an object attribute type.
 * This enum is used by EogllObjectAttrs.
 *
 */
typedef EOGLL_DECL_ENUM enum EogllObjectAttrType {
    /// The default object attribute type
    EOGLL_ATTR_NONE,
    /// The position object attribute type
    EOGLL_ATTR_POSITION,
    /// The texture object attribute type
    EOGLL_ATTR_TEXTURE,
    /// The normal object attribute type
    EOGLL_ATTR_NORMAL
} EogllObjectAttrType;


// we want this to display as if it is in a namespace Internal
/**
 * @brief *Internal*
 * @see eogllCreateObjectAttrs
 * @see eogllAddObjectAttr
 *
 * This struct is used to handle object attributes.
 * Object attributes are similar to vertex attributes, but they also store the type of the attribute (where it comes from in the obj file).
 * This allows us to load object files with customizable attributes.
 *
 * Sample usage:
 * @code{.c}
 * EogllObjectAttrs objMode = eogllCreateObjectAttrs();
 * eogllAddObjectAttr(&objMode, GL_FLOAT, 3, EOGLL_ATTR_POSITION);
 * eogllAddObjectAttr(&objMode, GL_FLOAT, 2, EOGLL_ATTR_TEXTURE);
 * EogllBufferObject bufferObject = eogllBufferObjectLoad("resources/models/cube.obj", objMode);
 * @endcode
 */
typedef EOGLL_DECL_STRUCT struct EogllObjectAttr {
    /// The type of the attribute
    EogllObjectAttrType type;
    /// The amount of components in the attribute
    GLint num;
} EogllObjectAttr;

/**
 * @brief *Internal*
 * @see EogllObjectAttrs
 * @see eogllLoadBufferObject
 *
 * A way to store indices for an object.
 */
typedef EOGLL_DECL_STRUCT struct EogllObjectIndex {
    /// The geometry index (position)
    unsigned int geomIndex;
    /// The normal index
    unsigned int normalIndex;
    /// The texture coordinate index
    unsigned int texCoordIndex;
    /// Whether or not the object has normals
    bool hasNormal;
    /// Whether or not the object has texture coordinates
    bool hasTexCoord;
} EogllObjectIndex;

/**
 * @brief *Internal*
 * @see EogllObjectAttrs
 * @see eogllLoadBufferObject
 *
 * A way to store faces for an object.
 */
typedef EOGLL_DECL_STRUCT struct EogllObjectFileFace {
    /// The number of indices
    unsigned int numIndices;
    /// The indices
    EogllObjectIndex *indices;
} EogllObjectFileFace;

/**
 * @brief *Internal*
 * @see EogllObjectAttrs
 * @see eogllLoadBufferObject
 *
 * A way to store positions for an object.
 */
typedef EOGLL_DECL_STRUCT struct EogllObjectPosition {
    /// The x component of the position
    float x;
    /// The y component of the position
    float y;
    /// The z component of the position
    float z;
    /// The w component of the position
    float w;
    /// Whether or not the object has a w component
    bool hasW;
} EogllObjectPosition;

/**
 * @brief *Internal*
 * @see EogllObjectAttrs
 * @see eogllLoadBufferObject
 *
 * A way to store normals for an object.
 */
typedef EOGLL_DECL_STRUCT struct EogllObjectNormal {
    /// The x component of the normal
    float x;
    /// The y component of the normal
    float y;
    /// The z component of the normal
    float z;
} EogllObjectNormal;

/**
 * @brief *Internal*
 * @see EogllObjectAttrs
 * @see eogllLoadBufferObject
 *
 * A way to store texture coordinates for an object.
 */
typedef EOGLL_DECL_STRUCT struct EogllObjectTexCoord {
    /// The u component of the texture coordinate
    float u;
    /// The v component of the texture coordinate
    float v;
    /// The w component of the texture coordinate
    float w;
    /// Whether or not the object has a v component
    bool hasV;
    /// Whether or not the object has a w component
    bool hasW;
} EogllObjectTexCoord;

/**
 * @brief *Internal*
 * @see EogllObjectAttrs
 * @see eogllLoadBufferObject
 *
 * A representation of an object file, that can be used to load an object file.
 */
typedef EOGLL_DECL_STRUCT struct EogllObjectFileData {
    /// The number of faces
    unsigned int numFaces;
    /// The faces
    EogllObjectFileFace *faces;
    /// The number of positions
    unsigned int numPositions;
    /// The positions
    EogllObjectPosition *positions;
    /// The number of normals
    unsigned int numNormals;
    /// The normals
    EogllObjectNormal *normals;
    /// The number of texture coordinates
    unsigned int numTexCoords;
    /// The texture coordinates
    EogllObjectTexCoord *texCoords;
} EogllObjectFileData;

/**
 * @brief *Internal*
 * @param file The file to parse
 * @param data The data to store the parsed data in
 * @return EOGLL_SUCCESS if successful, EOGLL_FAILURE if not
 * @see EogllObjectFileData
 * @see eogllLoadBufferObject
 *
 * This function parses an object file into an object file data struct.
 */
EOGLL_DECL_FUNC_ND EogllResult eogllParseObjectFile(FILE* file, EogllObjectFileData *data);

/**
 * @brief *Internal*
 * @param data The object file data struct to delete
 * @see EogllObjectFileData
 * @see eogllLoadBufferObject
 *
 * This function deletes an object file data struct.
 */
EOGLL_DECL_FUNC void eogllDeleteObjectFileData(EogllObjectFileData *data);

/**
 * @brief A struct that represents object attributes
 * @see eogllCreateObjectAttrs
 * @see eogllAddObjectAttr
 *
 * This struct is used to handle object attributes.
 * Object attributes are similar to vertex attributes, but they also store the type of the attribute (where it comes from in the obj file).
 * This allows us to load object files with customizable attributes (like position, texture, and normal).
 *
 */
typedef EOGLL_DECL_STRUCT struct EogllObjectAttrs {
    /// The types of the attributes
    EogllObjectAttr types[8];
    /// The number of attributes
    uint32_t numTypes;
    /// The attribute builder
    EogllAttribBuilder builder;
} EogllObjectAttrs;

/**
 * @brief *Internal*
 * @param data The object file data struct to convert
 * @param attrs The object attributes to use
 * @param vertices Resulting vertices
 * @param numVertices Resulting number of vertices
 * @param indices Resulting indices
 * @param numIndices Resulting number of indices
 * @return EOGLL_SUCCESS if successful, EOGLL_FAILURE if not
 *
 * This function converts an object file data struct to vertices and indices.
 * If something goes wrong with object loading (SEGFAULT or alike), this function is probably the culprit.
 * This function is still a work in progress, and is not optimized or hardly tested.
 * Bad input will easily cause a SEGFAULT.
 * This function is used internally by eogllLoadObjectFile.
 *
 * @warning This function is still a work in progress, and is not optimized or hardly tested.
 *
 * @todo Optimize this function and test it more
 */
EOGLL_DECL_FUNC_ND EogllResult eogllObjectFileDataToVertices(EogllObjectFileData *data, EogllObjectAttrs attrs, float** vertices, uint32_t* numVertices, unsigned int** indices, uint32_t* numIndices);

/**
 * @brief *Internal*
 * @param path The path to the object file
 * @param attrs The object attributes to use
 * @param vertices Resulting vertices
 * @param numVertices Resulting number of vertices
 * @param indices Resulting indices
 * @param numIndices Resulting number of indices
 * @return EOGLL_SUCCESS if successful, EOGLL_FAILURE if not
 * @see EogllObjectAttrs
 * @see eogllObjectFileDataToVertices
 * @see eogllParseObjectFile
 *
 * Uses eogllParseObjectFile and eogllObjectFileDataToVertices to load an object file.
 */
EOGLL_DECL_FUNC_ND EogllResult eogllLoadObjectFile(const char* path, EogllObjectAttrs attrs, float** vertices, uint32_t* numVertices, unsigned int** indices, uint32_t* numIndices);

/**
 * @brief Creates an object attributes struct
 * @return The created object attributes struct
 * @see EogllObjectAttrs
 * @see eogllAddObjectAttr
 *
 * This function creates an object attributes struct.
 */
EOGLL_DECL_FUNC_ND EogllObjectAttrs eogllCreateObjectAttrs();

/**
 * @brief Adds an object attribute to an object attributes struct
 * @param attrs The object attributes struct to add the attribute to
 * @param type The type of the attribute
 * @param num The number of components in the attribute
 * @param attrType The type of the attribute (where it comes from in the obj file)
 * @see EogllObjectAttrs
 * @see eogllCreateObjectAttrs
 *
 * This function adds an object attribute to an object attributes struct.
 */
EOGLL_DECL_FUNC void eogllAddObjectAttr(EogllObjectAttrs* attrs, GLenum type, GLint num, EogllObjectAttrType attrType);

/**
 * @brief Loads a buffer object from an object file
 * @param path The path to the object file
 * @param attrs The object attributes to use
 * @param usage The usage
 * @return The created buffer object
 * @see EogllObjectAttrs
 * @see eogllLoadObjectFile
 * @see eogllCreateBufferObject
 *
 * This function loads a buffer object from an object file.
 */
EOGLL_DECL_FUNC_ND EogllBufferObject eogllLoadBufferObject(const char* path, EogllObjectAttrs attrs, GLenum usage);

/**
 * @brief Generates normals for an object file
 * @param data The object file data struct to generate normals for
 * @see EogllObjectFileData
 * @see eogllObjectFileDataToVertices
 * @see eogllLoadObjectFile
 * 
 * This function generates normals for an object file.
 */
EOGLL_DECL_FUNC void eogllGenerateNormals(EogllObjectFileData *data);

#ifdef __cplusplus
}
#endif

#endif //_EOGLL_OBJ_LOADER_H_
