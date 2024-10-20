/**
 * @file bufferobj.hpp
 * @brief HOGLL buffer object header file
 * @date 2024-10-9
 *
 * HOGLL buffer object header file
 */

#pragma once
#ifndef _HOGLL_BUFFER_OBJ_HPP_
#define _HOGLL_BUFFER_OBJ_HPP_

#include "pch.hpp"
#include "objectattrs.hpp"

namespace ogl {
    struct BufferObject {
    private:
        EogllBufferObject buffer;
    public:
        inline BufferObject(EogllBufferObject ebo) : buffer(ebo) {}
        HEDLEY_DEPRECATED_FOR(0.7.1, RenderModel) BufferObject(const char* name, EogllObjectAttrs attrs);
        HEDLEY_DEPRECATED_FOR(0.7.1, RenderModel) BufferObject(const char* name, ogl::ObjectAttrs attrs);
        BufferObject(unsigned int vao, unsigned int vbo, unsigned int ebo, GLsizeiptr indicesSize, GLenum indicesType);
        BufferObject(unsigned int vao, unsigned int vbo, GLsizeiptr numVertices);
        ~BufferObject();

        void draw(GLenum mode);
        void bind();

        EOGLL_NO_DISCARD EogllBufferObject* getBuffer();
    };
}

#endif