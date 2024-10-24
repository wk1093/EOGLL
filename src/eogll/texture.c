#include "eogll/texture.h"

#include "eogll/logging.h"


// EogllTexture* t = eogllStartTexture();
// glTexParameteri(...);
// whatever else you need to do before using the texture
// eogllFinishTexture(t, "path/to/texture.png");

EogllTexture *eogllStartTexture() {
    EogllTexture *texture = (EogllTexture *) malloc(sizeof(EogllTexture));
    if (!texture) {
        EOGLL_LOG_ERROR(stderr, "Failed to allocate memory for texture\n");
        return NULL;
    }
    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    return texture;
}
void eogllFinishTexture(EogllTexture *texture, const char *path) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (!data) {
        EOGLL_LOG_ERROR(stderr, "Failed to load texture %s\n", path);
        return;
    }
    EOGLL_LOG_DEBUG(stdout, "Loaded texture %s\n", path);
    EOGLL_LOG_DEBUG(stdout, "%d %d %d\n", width, height, nrChannels);
    GLint format;
    switch (nrChannels) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            EOGLL_LOG_ERROR(stderr, "Unknown number of channels %d\n", nrChannels);
            return;
    }
    texture->width = width;
    texture->height = height;
    texture->channels = nrChannels;
    texture->format = format;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

EogllTexture *eogllCreateTexture(const char *path) {
    EogllTexture *texture = (EogllTexture *) malloc(sizeof(EogllTexture));
    if (!texture) {
        EOGLL_LOG_ERROR(stderr, "Failed to allocate memory for texture\n");
        return NULL;
    }
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (!data) {
        EOGLL_LOG_ERROR(stderr, "Failed to load texture %s\n", path);
        return NULL;
    }
    EOGLL_LOG_DEBUG(stdout, "Loaded texture %s\n", path);
    EOGLL_LOG_DEBUG(stdout, "%d %d %d\n", width, height, nrChannels);
    GLint format;
    switch (nrChannels) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            EOGLL_LOG_ERROR(stderr, "Unknown number of channels %d\n", nrChannels);
            return NULL;
    }
    texture->width = width;
    texture->height = height;
    texture->channels = nrChannels;
    texture->format = format;
    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    return texture;
}

EogllTexture* eogllCreateTextureFromBuffer(const uint8_t* buffer, size_t size) {
    EogllTexture *texture = (EogllTexture *) malloc(sizeof(EogllTexture));
    if (!texture) {
        EOGLL_LOG_ERROR(stderr, "Failed to allocate memory for texture\n");
        return NULL;
    }
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load_from_memory(buffer, size, &width, &height, &nrChannels, 0);
    if (!data) {
        EOGLL_LOG_ERROR(stderr, "Failed to load texture from buffer\n");
        return NULL;
    }
    EOGLL_LOG_DEBUG(stdout, "Loaded texture from buffer\n");
    EOGLL_LOG_DEBUG(stdout, "%d %d %d\n", width, height, nrChannels);
    GLint format;
    switch (nrChannels) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            EOGLL_LOG_ERROR(stderr, "Unknown number of channels %d\n", nrChannels);
            return NULL;
    }
    texture->width = width;
    texture->height = height;
    texture->channels = nrChannels;
    texture->format = format;
    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    return texture;
}

void eogllBindTexture(EogllTexture *texture) {
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

void eogllDeleteTexture(EogllTexture *texture) {
    glDeleteTextures(1, &texture->id);
    free(texture);
}

void eogllBindTextureUniform(EogllTexture* texture, EogllShaderProgram* shader, const char* name, unsigned int index) {
    if (index >= __eogll_texture_max_texture_units) {
        EOGLL_LOG_ERROR(stderr, "Texture unit %d is not supported\n", index);
        return;
    }
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    eogllSetUniform1i(shader, name, (int)index);
}

void eogllBindTextureUniformi(GLuint texture, EogllShaderProgram* shader, const char* name, unsigned int index) {
    if (index >= __eogll_texture_max_texture_units) {
        EOGLL_LOG_ERROR(stderr, "Texture unit %d is not supported\n", index);
        return;
    }
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, texture);
    eogllSetUniform1i(shader, name, (int)index);
}