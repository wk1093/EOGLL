#include "eogll/attrib_builder.h"

#include "eogll/util.h"

EogllAttribBuilder eogllCreateAttribBuilder() {
    EogllAttribBuilder builder = {{0}, 0};
    return builder;
}

void eogllAddAttribute(EogllAttribBuilder *builder, GLenum type, GLint num) {
    builder->attribs[builder->numAttribs].type = type;
    builder->attribs[builder->numAttribs].size = eogllSizeOf(type) * num;
    builder->attribs[builder->numAttribs].normalized = GL_FALSE;
    builder->numAttribs++;
}

void eogllBuildAttributes(EogllAttribBuilder *builder, GLuint vao) {
    // first we need to calculate the stride
    GLsizei stride = 0;
    for (int i = 0; i < builder->numAttribs; i++) {
        stride += builder->attribs[i].size;
    }
    // now we can build the vertex array
    glBindVertexArray(vao);
    uint64_t offset = 0;
    for (int i = 0; i < builder->numAttribs; i++) {

        glVertexAttribPointer(i, builder->attribs[i].size / eogllSizeOf(builder->attribs[i].type), builder->attribs[i].type, builder->attribs[i].normalized, stride, (void*)offset);
        glEnableVertexAttribArray(i);
        offset += builder->attribs[i].size;
    }
}