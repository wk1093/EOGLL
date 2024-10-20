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
    struct BoneInfo {
        int id;
        glm::mat4 offset;
    };

    enum ModelAttrType {
        POSITION,
        NORMAL,
        TEXTURE,
        BONE_IDS,
        BONE_WEIGHTS
    };

    struct ModelAttr {
        GLenum type;
        GLint size; // size of the attribute (for example, a vec3 has size 3 * eogllSizeOf(GL_FLOAT))
        ModelAttrType attr;

        ModelAttr();
        ModelAttr(GLenum type, GLint size, ModelAttrType attr);

        int num();
    };

    class ModelAttrs {
    public:
        ModelAttrs();
        ModelAttrs(std::initializer_list<ModelAttr> args);
        ModelAttrs(ObjectAttrs obj_attrs);

        void add(GLenum type, GLint size, ModelAttrType attr);

        EOGLL_NO_DISCARD std::vector<ModelAttr> getAttrs();

        EOGLL_NO_DISCARD int num();

        EOGLL_NO_DISCARD int size();

        void build(int vao);

        ModelAttr& operator[](int i);

    private:
        ModelAttrType getAttrType(EogllObjectAttrType type);

        std::vector<ModelAttr> attrs;
    };


    namespace internal {
        struct Vertex {
            glm::vec3 pos;
            glm::vec3 norm;
            glm::vec2 tex;
            glm::ivec4 bone_ids;
            glm::vec4 bone_weights;
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
            std::vector<float> vert; // when we pass an int we will just reinterpret_cast it to float (it is the same size)
            std::vector<unsigned int> indices;
        };

        EOGLL_NO_DISCARD GlMesh packMesh(Mesh mesh, ModelAttrs attrs);
    }

    class RenderModel {
    public:
        // we will look for texture in same directory as the model by default
        // but if we change relpath to tex, it will look for textures in the folder tex, relative to the model
        // but if we disabled relative to obj, it will not be relative to the object, but to our working directory
        RenderModel(std::string path, ModelAttrs attrs, std::string relpath = ".", bool relative_to_obj=true);
        ~RenderModel();

        // instead of taking in the window and shader, this one passes a lambda that is called right before drawing the models, this allows the user to specify custom uniforms and/or other preparations
        void draw(EogllShaderProgram* shader, std::function<void(EogllShaderProgram*)> preDraw);

    private:

        void loadModel(const std::string& p);

        void processNode(aiNode* node, const aiScene* scene);

        EOGLL_NO_DISCARD internal::Mesh processMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4 transform);

        EOGLL_NO_DISCARD std::vector<internal::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    
        void extractBones(std::vector<internal::Vertex>& vertices, aiMesh* mesh, const aiScene* scene);
    public:
        std::string path;
        ModelAttrs attrs;
        std::vector<internal::Mesh> meshes;
        std::vector<internal::Texture> textures_loaded;
        std::map<std::string, BoneInfo> boneInfoMap;
        int boneCounter = 0;

    };
}

#endif