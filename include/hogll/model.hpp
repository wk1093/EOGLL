/**
 * @file model.hpp
 * @brief HOGLL model header file
 * @date 2024-10-17
 *
 * HOGLL model
 */

#pragma once
#ifndef _HOGLL_MODEL_HPP_
#define _HOGLL_MODEL_HPP_

#include "pch.hpp"
#include "objectattrs.hpp"
#include "bufferobj.hpp"

namespace ogl {
    namespace internal {
        struct Vertex {
            glm::vec3 pos;
            glm::vec3 norm;
            glm::vec2 tex;
        };

        struct Mesh {
            std::vector<Vertex> vert;
            std::vector<unsigned int> indices;
        };

        struct GlMesh {
            std::vector<float> vert;
            std::vector<unsigned int> indices;
        };

        GlMesh packMesh(Mesh mesh, ObjectAttrs attrs);
    }

    class Model {
    public:
        Model(std::string path, ObjectAttrs attrs);
        ~Model();

        void draw();

    private:

        std::string path;
        ObjectAttrs attrs;
        BufferObject render;
        std::vector<internal::Mesh> meshes;
    };
}

#endif