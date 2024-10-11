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
        Model();
        Model(glm::vec3 pos);

        glm::vec3* posptr();
        glm::vec3& pos();

        glm::vec3* rotptr();
        glm::vec3& rot();

        glm::vec3* scaleptr();
        glm::vec3& scale();

        void update(EogllShaderProgram* shader, const char* name);

        EogllModel* getModel();
    };

    struct Camera {
    private:
        EogllCamera camera;
    public:
        Camera();
        Camera(glm::vec3 pos);

        glm::vec3* posptr();
        glm::vec3& pos();

        void yaw(float amount);
        void pitch(float amount);

        void move(EogllCameraDirection dir, float amount);

        void update(EogllShaderProgram* shader, const char* name);
    };
}

#endif