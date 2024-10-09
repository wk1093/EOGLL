#include "eogll/buffer_object.h"

#include "eogll/logging.h"
#include "eogll/util.h"


EogllBufferObject eogllCreateBufferObject(unsigned int vao, unsigned int vbo, unsigned int ebo, GLsizeiptr indicesSize, GLenum indicesType) {
    EogllBufferObject bufferObject;
    bufferObject.vao = vao;
    bufferObject.vbo = vbo;
    bufferObject.ebo = ebo;
    bufferObject.numIndices = indicesSize / eogllSizeOf(indicesType);
    bufferObject.indicesType = indicesType;
    bufferObject.hasIndices = true;
    return bufferObject;
}

EogllBufferObject eogllCreateBasicBufferObject(unsigned int vao, unsigned int vbo, GLsizeiptr numVertices) {
    EogllBufferObject bufferObject;
    bufferObject.vao = vao;
    bufferObject.vbo = vbo;
    bufferObject.ebo = 0;
    bufferObject.numIndices = numVertices;
    bufferObject.indicesType = 0;
    bufferObject.hasIndices = false;
    return bufferObject;
}

void eogllDrawBufferObject(EogllBufferObject* bufferObject, GLenum mode) {
    if (!bufferObject->hasIndices) {
        // Maybe we should just draw it as a basic buffer object?
        // TODO: figure out what to do here (for now we just log an error)
        EOGLL_LOG_ERROR(stderr, "Buffer object has no indices\n");
        return;
    }
    glBindVertexArray(bufferObject->vao);
    glDrawElements(mode, (GLint)bufferObject->numIndices, bufferObject->indicesType, 0);
    glBindVertexArray(0);
}

void eogllDrawBasicBufferObject(EogllBufferObject* bufferObject, GLenum mode) {
    glBindVertexArray(bufferObject->vao);
    glDrawArrays(mode, 0, (GLint)bufferObject->numIndices);
    glBindVertexArray(0);
}

void eogllBindBufferObject(EogllBufferObject* bufferObject) {
    glBindVertexArray(bufferObject->vao);
}

void eogllDeleteBufferObject(EogllBufferObject* bufferObject) {
    glDeleteVertexArrays(1, &bufferObject->vao);
    glDeleteBuffers(1, &bufferObject->vbo);
    if (bufferObject->hasIndices)
        glDeleteBuffers(1, &bufferObject->ebo);
}