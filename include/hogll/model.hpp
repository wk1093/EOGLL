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
#include "transforms.hpp"

namespace ogl {
    namespace internal {
        struct Vertex {
            glm::vec3 pos;
            glm::vec3 norm;
            glm::vec2 tex;
        };

        struct Texture {
            EogllTexture* texture;
            std::string type; // diffuse, specular (this can be whatever you want, it will be in the shader)
            // for example, if you have 2 textures with the type "abc" and 1 texture with the type "def" (in that order)
            // the uniform names will be "sampler_abc1", "sampler_abc2", "sampler_def1"
            std::string path;
        };

        struct Mesh {
            std::vector<Vertex> vert;
            std::vector<unsigned int> indices;
            std::vector<Texture> textures;
            BufferObject* render;

            Mesh() {}
        };

        struct GlMesh {
            std::vector<float> vert;
            std::vector<unsigned int> indices;
        };

        GlMesh packMesh(Mesh mesh, ObjectAttrs attrs);
    }

    class RenderModel {
    public:
        RenderModel(std::string path, ObjectAttrs attrs);
        ~RenderModel();

        void draw(Window* window, EogllShaderProgram* shader);
        void draw(Window* window, EogllShaderProgram* shader, Camera camera, Projection projection, Model model);

    private:

        void loadModel();

        void processNode(aiNode* node, const aiScene* scene);

        internal::Mesh processMesh(aiMesh* mesh, const aiScene* scene);

        std::vector<internal::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    public:
        std::string path;
        ObjectAttrs attrs;
        std::vector<internal::Mesh> meshes;
        std::vector<internal::Texture> textures_loaded;

    };
}

#endif