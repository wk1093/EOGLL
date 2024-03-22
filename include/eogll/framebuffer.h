/**
 * @file framebuffer.h
 * @brief EOGLL framebuffer header file
 * @date 2024-03-22
 *
 * EOGLL framebuffer header file
 */

#pragma once
#ifndef _EOGLL_FRAMEBUFFER_H_
#define _EOGLL_FRAMEBUFFER_H_

#include "pch.h"
#include "window.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef EOGLL_DECL_STRUCT struct EogllFramebuffer {
    uint32_t fbo;
    uint32_t texture;
    uint32_t rbo;
    uint32_t width;
    uint32_t height;
} EogllFramebuffer;

EOGLL_DECL_FUNC_ND EogllFramebuffer* eogllCreateFramebuffer(uint32_t width, uint32_t height);
EOGLL_DECL_FUNC void eogllDestroyFramebuffer(EogllFramebuffer* framebuffer);
EOGLL_DECL_FUNC void eogllBindFramebuffer(EogllFramebuffer* framebuffer);
EOGLL_DECL_FUNC void eogllUnbindFramebuffer();
EOGLL_DECL_FUNC void eogllFramebufferResize(EogllFramebuffer* framebuffer, uint32_t width, uint32_t height);

#ifdef __cplusplus
}
#endif

#endif //_EOGLL_FRAMEBUFFER_H_