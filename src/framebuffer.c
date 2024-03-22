#include "eogll/framebuffer.h"

EogllFramebuffer* eogllCreateFramebuffer(uint32_t width, uint32_t height) {
    EogllFramebuffer* framebuffer = (EogllFramebuffer*)malloc(sizeof(EogllFramebuffer));
    framebuffer->width = width;
    framebuffer->height = height;
    glGenFramebuffers(1, &framebuffer->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);
    glGenTextures(1, &framebuffer->texture);
    glBindTexture(GL_TEXTURE_2D, framebuffer->texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, framebuffer->width, framebuffer->height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebuffer->texture, 0);

    glGenRenderbuffers(1, &framebuffer->rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, framebuffer->rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, framebuffer->width, framebuffer->height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, framebuffer->rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("Framebuffer is not complete!\n");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    return framebuffer;
}

void eogllDestroyFramebuffer(EogllFramebuffer* framebuffer) {
    glDeleteFramebuffers(1, &framebuffer->fbo);
    glDeleteTextures(1, &framebuffer->texture);
    glDeleteRenderbuffers(1, &framebuffer->rbo);
    free(framebuffer);
}

void eogllBindFramebuffer(EogllFramebuffer* framebuffer) {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);
    glViewport(0, 0, (int)framebuffer->width, (int)framebuffer->height);
}

void eogllUnbindFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void eogllFramebufferResize(EogllFramebuffer* framebuffer, uint32_t width, uint32_t height) {
    framebuffer->width = width;
    framebuffer->height = height;
    glBindTexture(GL_TEXTURE_2D, framebuffer->texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, framebuffer->width, framebuffer->height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebuffer->texture, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, framebuffer->rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, framebuffer->width, framebuffer->height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, framebuffer->rbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("Framebuffer is not complete!\n");
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glViewport(0, 0, (int)framebuffer->width, (int)framebuffer->height); // todo: check this
}



