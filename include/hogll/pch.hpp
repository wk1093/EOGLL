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
#ifndef INCLUDE_HOGLL_PCH_HPP
#define INCLUDE_HOGLL_PCH_HPP

#include <eogll.h>

#include <vector>
#include <initializer_list>
#include <string>
#include <unordered_map>
#include <iostream>
#include <map>
#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#endif
