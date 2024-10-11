/**
 * @file transforms.hpp
 * @brief HOGLL transforms header file
 * @date 2024-10-9
 *
 * HOGLL transforms header file
 */

#pragma once
#ifndef _HOGLL_TRANSFORMS_HPP_
#define _HOGLL_TRANSFORMS_HPP_

#include "pch.hpp"

namespace ogl {
    struct Model {
    private:
        EogllModel model;
    public:
        inline Model() {
            model = eogllCreateModel();
        }

        inline glm::vec3* pos() {
            // make vec3 a pointer to the cglm vec3
            return (glm::vec3*)&model.pos;
        }

        inline glm::vec3* rot() {
            // make vec3 a pointer to the cglm vec3
            return (glm::vec3*)&model.rot;
        }

        inline glm::vec3* scale() {
            // make vec3 a pointer to the cglm vec3
            return (glm::vec3*)&model.scale;
        }

        inline void update(EogllShaderProgram* shader, const char* name) {
            eogllUpdateModelMatrix(&model, shader, name);
        }

        inline EogllModel* getModel() {
            return &model;
        }
    };
}

#endif