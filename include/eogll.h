/**
 * @file eogll.h
 * @brief EOGLL header file
 * @date 2024-01-25
 *
 * EOGLL is a C library that wraps OpenGL, GLFW, GLAD, CGLM, and more to make it easier to use OpenGL.
 * EOGLL has many useful tools like object loading, camera, and more.
 *
 *
 */


/*
 * Naming convention:
 * DEFINES: CAPITAL_CASE: EOGLL_*
 * TYPES: PascalCase: Eogll*
 * Functions: camelCase: eogll*
 * Enums: CAPITAL_CASE: EOGLL_*
 */


#pragma once
#ifndef _EOGLL_H_
#define _EOGLL_H_

#include "eogll/pch.h"

#include "eogll/version.h"
#include "eogll/defines.h"
#include "eogll/input.h"
#include "eogll/logging.h"
#include "eogll/util.h"
#include "eogll/window.h"
#include "eogll/shader.h"
#include "eogll/attrib_builder.h"
#include "eogll/buffer_object.h"
#include "eogll/texture.h"
#include "eogll/transforms.h"
#include "eogll/camera.h"
#include "eogll/obj_loader.h"
#include "eogll/gl.h"
#include "eogll/framebuffer.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes EOGLL
 * @return EOGLL_SUCCESS if successful, EOGLL_FAILURE if not
 * @note This function must be called before any other EOGLL functions
 *
 * This function initializes GLFW and GLAD
 */
EOGLL_DECL_FUNC_ND EogllResult eogllInit();

/**
 * @brief Terminates EOGLL
 *
 * This function terminates GLFW
 */
EOGLL_DECL_FUNC void eogllTerminate();

#ifdef __cplusplus
}
#endif

#endif // _EOGLL_H_