/**
 * @file pch.h
 * @brief EOGLL precompiled header file
 * @date 2024-01-28
 *
 * EOGLL precompiled header file
 *
 * This file isn't always precompiled, it's mostly to organize the includes and to make sure that the same includes are used everywhere.
 */

#pragma once
#ifndef INCLUDE_EOGLL_PCH_H
#define INCLUDE_EOGLL_PCH_H

#include "defines.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <hedley.h>

#include <cglm/cglm.h>

#include <stb.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int __eogll_texture_max_texture_units;

#endif //INCLUDE_EOGLL_PCH_H
