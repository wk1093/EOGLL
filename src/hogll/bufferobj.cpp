#include "hogll/bufferobj.hpp"

namespace ogl {
    BufferObject::BufferObject(const char* name, EogllObjectAttrs attrs) {
        buffer = eogllLoadBufferObject(name, attrs, GL_STATIC_DRAW);
    }
    BufferObject::BufferObject(unsigned int vao, unsigned int vbo, unsigned int ebo, GLsizeiptr indicesSize, GLenum indicesType) {
        buffer = eogllCreateBufferObject(vao, vbo, ebo, indicesSize, indicesType);
    }
    BufferObject::BufferObject(unsigned int vao, unsigned int vbo, GLsizeiptr numVertices) {
        buffer = eogllCreateBasicBufferObject(vao, vbo, numVertices);
    }
    BufferObject::~BufferObject() {
        eogllDeleteBufferObject(&buffer);
    }
    void BufferObject::draw(GLenum mode) {
        if (buffer.hasIndices) {
            eogllDrawBufferObject(&buffer, mode);
        } else {
            eogllDrawBasicBufferObject(&buffer, mode);
        }
    }
    void BufferObject::bind() {
        eogllBindBufferObject(&buffer);
    }
    
    EogllBufferObject* BufferObject::getBuffer() {
        return &buffer;
    }

}