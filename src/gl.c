#include "eogll/gl.h"

unsigned int eogllGenVertexArray() {
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    return vao;
}

unsigned int eogllGenBuffer(unsigned int vao, GLenum mode, GLsizeiptr count, const void* indices, GLenum usage) {
    glBindVertexArray(vao);
    unsigned int vo;
    glGenBuffers(1, &vo);
    glBindBuffer(mode, vo);
    glBufferData(mode, count, indices, usage);
    glBindVertexArray(0);
    return vo;
}

void eogllSetWireframeMode(bool enable) {
    if (enable) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void eogllEnableDepth() {
    glEnable(GL_DEPTH_TEST);
}

void eogllEnableTransparency() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void eogllEnableFaceCulling() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}