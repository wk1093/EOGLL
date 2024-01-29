#include "eogll/util.h"

#include "eogll/logging.h"

char* eogllReadFile(const char* path) {
    EOGLL_LOG_TRACE(stdout, "%s\n", path);
    FILE* file = fopen(path, "rb");
    if (!file) {
        EOGLL_LOG_ERROR(stderr, "Failed to open file %s\n", path);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        EOGLL_LOG_ERROR(stderr, "Failed to allocate memory for file %s\n", path);
        return NULL;
    }
    fread(buffer, 1, length, file);
    fclose(file);
    buffer[length] = '\0';
    return buffer;
}

double eogllGetTime() {
    return (double)glfwGetTime();
}


GLint eogllSizeOf(GLenum type) {
    // glVertexAttribPointer or glVertexAttribIPointer: GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, and GL_UNSIGNED_INT
    // glVertexAttribPointer: GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV and GL_UNSIGNED_INT_10F_11F_11F_REV
    // glVertexAttribLPointer: GL_DOUBLE
    switch (type) {
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
            return 1;
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
        case GL_HALF_FLOAT:
            return 2;
        case GL_INT:
        case GL_UNSIGNED_INT:
        case GL_FLOAT:
        case GL_INT_2_10_10_10_REV:
        case GL_UNSIGNED_INT_2_10_10_10_REV:
        case GL_UNSIGNED_INT_10F_11F_11F_REV:
            return 4;
        case GL_DOUBLE:
            return 8;
        default:
        EOGLL_LOG_WARN(stderr, "Unknown GL type %d\n", type);
            return 0;
    }
}