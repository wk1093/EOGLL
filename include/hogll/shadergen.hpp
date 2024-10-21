/**
 * @file shadergen.hpp
 * @brief HOGLL shader generation header file
 * @date 2024-10-9
 *
 * HOGLL shader generation header file
 */

#pragma once
#ifndef _HOGLL_SHADER_GEN_HPP_
#define _HOGLL_SHADER_GEN_HPP_

#include "pch.hpp"

#include "objectattrs.hpp"
#include "model.hpp"

namespace ogl {
    EOGLL_NO_DISCARD EogllShaderProgram* basicShaderGenerator(ModelAttrs attrs, bool defaultUniforms);
}

#endif