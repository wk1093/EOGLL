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

#include "window.hpp"

namespace ogl {
    struct Model {
    private:
        EogllModel model;
    public:
        inline Model(EogllModel ebo) : model(ebo) {}
        Model();
        Model(glm::vec3 pos);

        glm::vec3* posptr();
        glm::vec3& pos();

        glm::vec3* rotptr();
        glm::vec3& rot();

        glm::vec3* scaleptr();
        glm::vec3& scale();

        void update(EogllShaderProgram* shader, const char* name="model");

        EogllModel* getModel();

        void rotate(float amount, glm::vec3 axis);
    };

    struct Camera {
    private:
        EogllCamera camera;
    public:
        inline Camera(EogllCamera ebo) : camera(ebo) {}
        Camera();
        Camera(glm::vec3 pos);

        glm::vec3* posptr();
        glm::vec3& pos();

        void yaw(float amount);
        void pitch(float amount);

        void move(EogllCameraDirection dir, float amount);

        void update(EogllShaderProgram* shader, const char* name="view");
    };

    struct Projection {
    private:
        EogllProjection proj;
    public:
        inline Projection(EogllProjection ebo) : proj(ebo) {}
        Projection(float fov, float near, float far);
        Projection(float near, float far);

        void update(EogllShaderProgram* shader, const char* name, const ogl::Window& window);
        void update(EogllShaderProgram* shader, const char* name, uint32_t width, uint32_t height);
        void update(EogllShaderProgram* shader, const char* name, float top, float bottom, float left, float right);
    };
}

#endif