#include "eogll/obj_loader.h"

#include "eogll/logging.h"
#include "eogll/util.h"
#include "eogll/gl.h"

EogllObjectAttrs eogllCreateObjectAttrs() {
    EogllObjectAttrs attrs = {{0}, 0, eogllCreateAttribBuilder()};
    return attrs;
}

void eogllAddObjectAttr(EogllObjectAttrs* attrs, GLenum type, GLint num, EogllObjectAttrType attrType) {
    attrs->types[attrs->numTypes++] = (EogllObjectAttr){attrType, num};
    eogllAddAttribute(&attrs->builder, type, num);
}


EogllResult eogllParseObjectFile(FILE* file, EogllObjectFileData *data) {
    char line[256];
    data->numFaces = 0;
    data->numPositions = 0;
    data->numNormals = 0;
    data->numTexCoords = 0;
    data->faces = NULL;
    data->positions = NULL;
    data->normals = NULL;
    data->texCoords = NULL;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            data->numPositions++;
        } else if (line[0] == 'v' && line[1] == 'n') {
            data->numNormals++;
        } else if (line[0] == 'v' && line[1] == 't') {
            data->numTexCoords++;
        } else if (line[0] == 'f' && line[1] == ' ') {
            data->numFaces++;
        }
    }
    data->faces = (EogllObjectFileFace*)malloc(sizeof(EogllObjectFileFace) * data->numFaces);
    data->positions = (EogllObjectPosition*)malloc(sizeof(EogllObjectPosition) * data->numPositions);
    data->normals = (EogllObjectNormal*)malloc(sizeof(EogllObjectNormal) * data->numNormals);
    data->texCoords = (EogllObjectTexCoord*)malloc(sizeof(EogllObjectTexCoord) * data->numTexCoords);
    if (!data->faces || !data->positions || !data->normals || !data->texCoords) {
        EOGLL_LOG_ERROR(stderr, "Failed to allocate memory for object file data\n");
        return EOGLL_FAILURE;
    }
    fseek(file, 0, SEEK_SET);
    unsigned int positionIndex = 0;
    unsigned int normalIndex = 0;
    unsigned int texCoordIndex = 0;
    unsigned int faceIndex = 0;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            EogllObjectPosition position;
            position.hasW = false;
            position.w = 1.0f;
            int numRead = sscanf(line, "v %f %f %f %f", &position.x, &position.y, &position.z, &position.w);
            if (numRead == 4) {
                position.hasW = true;
            }

            data->positions[positionIndex++] = position;
        } else if (line[0] == 'v' && line[1] == 'n') {
            EogllObjectNormal normal;
            sscanf(line, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
            data->normals[normalIndex++] = normal;
        } else if (line[0] == 'v' && line[1] == 't') {
            EogllObjectTexCoord texCoord;
            // if there is another texture coordinate, read one
            // after that, read another one if there is one
            texCoord.hasV = false;
            texCoord.hasW = false;
            int numRead = sscanf(line, "vt %f %f %f", &texCoord.u, &texCoord.v, &texCoord.w);
            if (numRead == 2) {
                texCoord.hasV = true;
            } else if (numRead == 3) {
                texCoord.hasV = true;
                texCoord.hasW = true;
            }

            data->texCoords[texCoordIndex++] = texCoord;
        } else if (line[0] == 'f' && line[1] == ' ') {
            EogllObjectFileFace face;
            face.numIndices = 0;
            // figure out how many indices there are
            for (int i = 0; i < strlen(line); i++) {
                if (line[i] == ' ') { // TODO: better way to do this?
                    face.numIndices++;
                }
            }
            face.indices = (EogllObjectIndex*)malloc(sizeof(EogllObjectIndex) * face.numIndices);
            if (!face.indices) {
                EOGLL_LOG_ERROR(stderr, "Failed to allocate memory for object file face indices\n");
                return EOGLL_FAILURE;
            }
            // parse the indices
            char *token = strtok(line, " ");
            int index = 0;
            while (token) {
                if (token[0] == 'f') {
                    token = strtok(NULL, " ");
                    continue;
                }
                EogllObjectIndex objectIndex;
                objectIndex.hasNormal = false;
                objectIndex.hasTexCoord = false;
                objectIndex.geomIndex = 0;
                objectIndex.normalIndex = 0;
                objectIndex.texCoordIndex = 0;
                if (strstr(token, "//")) {
                    sscanf(token, "%d//%d", &objectIndex.geomIndex, &objectIndex.normalIndex);
                    objectIndex.hasNormal = true;
                } else if (strstr(token, "/")) {
                    int numRead = sscanf(token, "%d/%d/%d", &objectIndex.geomIndex, &objectIndex.texCoordIndex, &objectIndex.normalIndex);
                    if (numRead == 2) {
                        objectIndex.hasTexCoord = true;
                    } else if (numRead == 3) {
                        objectIndex.hasTexCoord = true;
                        objectIndex.hasNormal = true;
                    }
                } else {
                    sscanf(token, "%d", &objectIndex.geomIndex);
                }

                face.indices[index++] = objectIndex;
                token = strtok(NULL, " ");
            }
            data->faces[faceIndex++] = face;
        }

    }
    return EOGLL_SUCCESS;
}

void eogllDeleteObjectFileData(EogllObjectFileData *data) {
    for (int i = 0; i < data->numFaces; i++) {
        free(data->faces[i].indices);
    }
    free(data->faces);
    free(data->positions);
    free(data->normals);
    free(data->texCoords);
}

EogllResult eogllObjectFileDataToVertices(EogllObjectFileData *data, EogllObjectAttrs attrs, float** vertices, uint32_t* numVertices, unsigned int** indices, uint32_t* numIndices) {
    // since at the moment, our indices have multiple attributes, we cannot index it easily.
    // The unoptimized easiest way to do this is to not use indices at all and just duplicate vertices
    // one thing we can do is to create a map of indices to vertices, and then use that to create the indices (maps are hard in C)
    // another is to do the first method, but then optimize it by removing duplicate vertices and using indices to reference them
    // TODO: optimize this
    // TODO: support rectangles and other polygons by triangulating them

    // first we need to calculate the number of vertices
    *numVertices = 0;
    for (int i = 0; i < data->numFaces; i++) {
        *numVertices += data->faces[i].numIndices;
    }
    *numIndices = *numVertices;

    unsigned int numVerts = 0;
    for (int i = 0; i < attrs.numTypes; i++) {
        numVerts += attrs.builder.attribs[i].size / eogllSizeOf(attrs.builder.attribs[i].type);
    }

    *vertices = (float*)malloc(sizeof(float) * *numVertices * numVerts);
    *indices = (unsigned int*)malloc(sizeof(unsigned int) * *numIndices);
    for (int i = 0; i < *numIndices; i++) {
        (*indices)[i] = i;
    }
    unsigned int vertexIndex = 0;
    unsigned int max = *numVertices * numVerts;

    for (int i = 0; i < data->numFaces; i++) {
        for (int j = 0; j < data->faces[i].numIndices; j++) {
            EogllObjectIndex index = data->faces[i].indices[j];
            EogllObjectPosition position;
            EogllObjectNormal normal;
            EogllObjectTexCoord texCoord;
            if (data->numPositions > 0) {
                position = data->positions[index.geomIndex - 1];
            }
            if (data->numNormals > 0) {
                normal = data->normals[index.normalIndex - 1];
            }
            if (data->numTexCoords > 0) {
                texCoord = data->texCoords[index.texCoordIndex - 1];
            }
            for (int k = 0; k < attrs.numTypes; k++) {
                if (vertexIndex >= max) {
                    EOGLL_LOG_ERROR(stderr, "Vertex index %d is out of bounds\n", vertexIndex);
                    return EOGLL_FAILURE;
                }
                GLint num = attrs.types[k].num;
                switch (attrs.types[k].type) {
                    case EOGLL_ATTR_POSITION: {
                        if (num == 4) {
                            (*vertices)[vertexIndex++] = position.x;
                            (*vertices)[vertexIndex++] = position.y;
                            (*vertices)[vertexIndex++] = position.z;
                            if (position.hasW) {
                                (*vertices)[vertexIndex++] = position.w;
                            } else {
                                (*vertices)[vertexIndex++] = 1.0f;
                            }
                        } else if (num == 3) {
                            (*vertices)[vertexIndex++] = position.x;
                            (*vertices)[vertexIndex++] = position.y;
                            (*vertices)[vertexIndex++] = position.z;
                        } else if (num == 2) {
                            (*vertices)[vertexIndex++] = position.x;
                            (*vertices)[vertexIndex++] = position.y;
                        } else {
                            EOGLL_LOG_WARN(stderr, "Unknown number of position components %d\n", num);
                        }

                    } break;
                    case EOGLL_ATTR_NORMAL: {
                        if (num != 3) {
                            EOGLL_LOG_WARN(stderr, "Unknown number of normal components %d (expected 3)\n", num);
                        }
                        (*vertices)[vertexIndex++] = normal.x;
                        (*vertices)[vertexIndex++] = normal.y;
                        (*vertices)[vertexIndex++] = normal.z;
                    } break;
                    case EOGLL_ATTR_TEXTURE: {
                        if (num == 3) {
                            (*vertices)[vertexIndex++] = texCoord.u;
                            if (texCoord.hasV) {
                                (*vertices)[vertexIndex++] = texCoord.v;
                            } else {
                                EOGLL_LOG_WARN(stderr, "Texture coordinate %d has no v component\n", index.texCoordIndex);
                                (*vertices)[vertexIndex++] = 0.0f;
                            }
                            if (texCoord.hasW) {
                                (*vertices)[vertexIndex++] = texCoord.w;
                            } else {
                                EOGLL_LOG_WARN(stderr, "Texture coordinate %d has no w component\n", index.texCoordIndex);
                                (*vertices)[vertexIndex++] = 0.0f;
                            }
                        } else if (num == 2) {
                            (*vertices)[vertexIndex++] = texCoord.u;
                            if (texCoord.hasV) {
                                (*vertices)[vertexIndex++] = texCoord.v;
                            } else {
                                EOGLL_LOG_WARN(stderr, "Texture coordinate %d has no v component\n", index.texCoordIndex);
                                (*vertices)[vertexIndex++] = 0.0f;
                            }
                        } else if (num == 1) {
                            (*vertices)[vertexIndex++] = texCoord.u;
                        } else {
                            EOGLL_LOG_WARN(stderr, "Unknown number of texture components %d\n", num);
                        }
                    } break;
                    default:
                        EOGLL_LOG_WARN(stderr, "Unknown attribute type %d\n", attrs.types[k]);
                        break;
                }
            }
        }
    }
    return EOGLL_SUCCESS;
}

//void eogllPrintObjectData(EogllObjectFileData* data) {
//    printf("Positions:\n");
//    for (int i = 0; i < data->numPositions; i++) {
//        printf("%f %f %f %f\n", data->positions[i].x, data->positions[i].y, data->positions[i].z, data->positions[i].w);
//    }
//    printf("Normals:\n");
//    for (int i = 0; i < data->numNormals; i++) {
//        printf("%f %f %f\n", data->normals[i].x, data->normals[i].y, data->normals[i].z);
//    }
//    printf("Texture Coordinates:\n");
//    for (int i = 0; i < data->numTexCoords; i++) {
//        printf("%f %f %f\n", data->texCoords[i].u, data->texCoords[i].v, data->texCoords[i].w);
//    }
//    printf("Faces:\n");
//    for (int i = 0; i < data->numFaces; i++) {
//        printf("Face %d:\n", i);
//        for (int j = 0; j < data->faces[i].numIndices; j++) {
//            printf("%d/%d/%d ", data->faces[i].indices[j].geomIndex, data->faces[i].indices[j].texCoordIndex,
//                   data->faces[i].indices[j].normalIndex);
//        }
//        printf("\n");
//    }
//}

EogllResult eogllLoadObjectFile(const char* path, EogllObjectAttrs attrs, float** vertices, uint32_t* numVertices, unsigned int** indices, uint32_t* numIndices) {
    FILE* file = fopen(path, "r");
    if (!file) {
        EOGLL_LOG_ERROR(stderr, "Failed to open file %s\n", path);
        return EOGLL_FAILURE;
    }
    EogllObjectFileData data;
    if (eogllParseObjectFile(file, &data) != EOGLL_SUCCESS) {
        EOGLL_LOG_ERROR(stderr, "Failed to parse object file %s\n", path);
        return EOGLL_FAILURE;
    }

    EOGLL_LOG_DEBUG(stdout, "Parsed object file %s\n", path);

    if (eogllObjectFileDataToVertices(&data, attrs, vertices, numVertices, indices, numIndices) != EOGLL_SUCCESS) {
        EOGLL_LOG_ERROR(stderr, "Failed to convert object file data to vertices\n");
        return EOGLL_FAILURE;
    }
    eogllDeleteObjectFileData(&data);

    EOGLL_LOG_DEBUG(stdout, "Converted object file data to vertices\n");
    EOGLL_LOG_DEBUG(stdout, "Num vertices: %d\n", *numVertices);

    return EOGLL_SUCCESS;

}

EogllBufferObject eogllLoadBufferObject(const char* path, EogllObjectAttrs attrs, GLenum usage) {
    float* vertices;
    unsigned int* indices;
    uint32_t numVertices;
    uint32_t numIndices;
    if (eogllLoadObjectFile(path, attrs, &vertices, &numVertices, &indices, &numIndices) != EOGLL_SUCCESS) {
        EOGLL_LOG_ERROR(stderr, "Failed to load object %s\n", path);
        return (EogllBufferObject){0};
    }

    unsigned int numVerts = 0;
    for (int i = 0; i < attrs.numTypes; i++) {
        numVerts += attrs.builder.attribs[i].size / eogllSizeOf(attrs.builder.attribs[i].type);
    }
    unsigned int vao = eogllGenVertexArray();
    unsigned int vbo = eogllGenBuffer(vao, GL_ARRAY_BUFFER, (unsigned int)sizeof(float) * numVertices * numVerts, vertices, usage);
    unsigned int ebo = eogllGenBuffer(vao, GL_ELEMENT_ARRAY_BUFFER, (unsigned int)sizeof(unsigned int) * numIndices, indices, usage);
    eogllBuildAttributes(&attrs.builder, vao);
    free(vertices);
    free(indices);
    return eogllCreateBufferObject(vao, vbo, ebo, (unsigned int)sizeof(unsigned int) * numIndices, GL_UNSIGNED_INT);
}