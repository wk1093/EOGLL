#include "eogll/shader.h"

#include "eogll/logging.h"
#include "eogll/util.h"

EogllShaderProgram* eogllLinkProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
    EogllShaderProgram *shader = (EogllShaderProgram *) malloc(sizeof(EogllShaderProgram));

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLenum er = glGetError();
    if (er != GL_NO_ERROR) {
        EOGLL_LOG_ERROR(stderr, "OpenGL error: %d\n", er);
    }

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    shader->vertexStatus = success;
    if (!success) {
        glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
        EOGLL_LOG_ERROR(stderr, "Vertex shader compilation failed (%d): %s\n", success, infoLog);
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    er = glGetError();
    if (er != GL_NO_ERROR) {
        EOGLL_LOG_ERROR(stderr, "OpenGL error: %d\n", er);
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    shader->fragmentStatus = success;
    if (!success) {
        glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
        EOGLL_LOG_ERROR(stderr, "Fragment shader compilation failed: %s\n", infoLog);
    }


    shader->id = glCreateProgram();

    glAttachShader(shader->id, vertexShader);
    glAttachShader(shader->id, fragmentShader);
    glLinkProgram(shader->id);

    glGetProgramiv(shader->id, GL_LINK_STATUS, &success);
    shader->programStatus = success;
    if (!success) {
        glGetProgramInfoLog(shader->id, sizeof(infoLog), NULL, infoLog);
        EOGLL_LOG_ERROR(stderr, "Shader program linking failed: %s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader;
}

EogllShaderProgram* eogllLinkProgramFromFile(const char* vertexShaderPath, const char* fragmentShaderPath) {
    char* vertexShaderSource = eogllReadFile(vertexShaderPath);
    if (!vertexShaderSource) {
        EOGLL_LOG_ERROR(stderr, "Failed to read vertex shader source from %s\n", vertexShaderPath);
        return NULL;
    }
    char* fragmentShaderSource = eogllReadFile(fragmentShaderPath);
    if (!fragmentShaderSource) {
        EOGLL_LOG_ERROR(stderr, "Failed to read fragment shader source from %s\n", fragmentShaderPath);
        return NULL;
    }
    EogllShaderProgram* shader = eogllLinkProgram(vertexShaderSource, fragmentShaderSource);
    free(vertexShaderSource);
    free(fragmentShaderSource);
    return shader;
}

void eogllDeleteProgram(EogllShaderProgram* shader) {
    glDeleteProgram(shader->id);
    free(shader);
}

void eogllUseProgram(EogllShaderProgram* shader) {
    glUseProgram(shader->id);
}

void eogllSetUniformMatrix4fv(EogllShaderProgram* shader, const char* name, mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(shader->id, name), 1, GL_FALSE, (float*)value);
}

void eogllSetUniform4f(EogllShaderProgram* shader, const char* name, float v0, float v1, float v2, float v3) {
    glUniform4f(glGetUniformLocation(shader->id, name), v0, v1, v2, v3);
}

void eogllSetUniform4fv(EogllShaderProgram* shader, const char* name, vec4 value) {
    glUniform4fv(glGetUniformLocation(shader->id, name), 1, value);
}

void eogllSetUniform3f(EogllShaderProgram* shader, const char* name, float v0, float v1, float v2) {
    glUniform3f(glGetUniformLocation(shader->id, name), v0, v1, v2);
}

void eogllSetUniform3fv(EogllShaderProgram* shader, const char* name, vec3 value) {
    glUniform3fv(glGetUniformLocation(shader->id, name), 1, value);
}

void eogllSetUniform2f(EogllShaderProgram* shader, const char* name, float v0, float v1) {
    glUniform2f(glGetUniformLocation(shader->id, name), v0, v1);
}

void eogllSetUniform2fv(EogllShaderProgram* shader, const char* name, vec2 value) {
    glUniform2fv(glGetUniformLocation(shader->id, name), 1, value);
}

void eogllSetUniform1f(EogllShaderProgram* shader, const char* name, float v0) {
    glUniform1f(glGetUniformLocation(shader->id, name), v0);
}

void eogllSetUniform1fv(EogllShaderProgram* shader, const char* name, float* vector, GLsizei count) {
    glUniform1fv(glGetUniformLocation(shader->id, name), count, vector);
}

void eogllSetUniform1i(EogllShaderProgram* shader, const char* name, int v0) {
    glUniform1i(glGetUniformLocation(shader->id, name), v0);
}

void eogllSetUniform1iv(EogllShaderProgram* shader, const char* name, int* vector, GLsizei count) {
    glUniform1iv(glGetUniformLocation(shader->id, name), count, vector);
}

void eogllSetUniform1ui(EogllShaderProgram* shader, const char* name, unsigned int v0) {
    glUniform1ui(glGetUniformLocation(shader->id, name), v0);
}

void eogllSetUniform1uiv(EogllShaderProgram* shader, const char* name, unsigned int* vector, GLsizei count) {
    glUniform1uiv(glGetUniformLocation(shader->id, name), count, vector);
}

void eogllSetUniformMatrix2fv(EogllShaderProgram* shader, const char* name, mat2 value) {
    glUniformMatrix2fv(glGetUniformLocation(shader->id, name), 1, GL_FALSE, (float*)value);
}

void eogllSetUniformMatrix3fv(EogllShaderProgram* shader, const char* name, mat3 value) {
    glUniformMatrix3fv(glGetUniformLocation(shader->id, name), 1, GL_FALSE, (float*)value);
}

void eogllSetUniform2fl(EogllShaderProgram* shader, const char* name, vec2* vectors, GLsizei count) {
    glUniform2fv(glGetUniformLocation(shader->id, name), count, (float*)vectors);
}

void eogllSetUniform3fl(EogllShaderProgram* shader, const char* name, vec3* vectors, GLsizei count) {
    glUniform3fv(glGetUniformLocation(shader->id, name), count, (float*)vectors);
}

void eogllSetUniform4fl(EogllShaderProgram* shader, const char* name, vec4* vectors, GLsizei count) {
    glUniform4fv(glGetUniformLocation(shader->id, name), count, (float*)vectors);
}