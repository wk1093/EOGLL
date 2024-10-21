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
    /**
     * @brief A struct that represents a bone's info
     * 
     * This struct is used to store data on bones. This will eventually be used for skeletal animation.
     */
    struct BoneInfo {
        /// @brief The id of the bone
        int id;

        /// @brief The offset matrix of the bone
        glm::mat4 offset;
    };

    /**
     * @brief A struct that represents a model attribute
     * @see ModelAttrs
     * 
     * This struct is used to store data on model attributes.
     */
    enum ModelAttrType {
        POSITION,
        NORMAL,
        TEXTURE,
        BONE_IDS,
        BONE_WEIGHTS
    };

    /**
     * @brief A struct that represents a model attribute
     * @see ModelAttrs
     * 
     * This struct is used to store data on model attributes.
     */
    struct ModelAttr {
        /// @brief The GL type of the attribute
        GLenum type;

        /// @brief The size of the attribute (for example, a vec3 has size 3 * eogllSizeOf(GL_FLOAT))
        GLint size;

        /// @brief The attribute type
        ModelAttrType attr;

        /**
         * @brief Construct a new Model Attr object
         * @see ModelAttrs
         */
        ModelAttr();

        /**
         * @brief Construct a new Model Attr object
         * @param type The GL type of the attribute
         * @param size The size of the attribute
         * @param attr The attribute type
         * @see ModelAttrs
         */
        ModelAttr(GLenum type, GLint size, ModelAttrType attr);

        /**
         * @brief Get the size of the attribute
         * @return The size of the attribute
         */
        int num();
    };

    /**
     * @brief A struct that represents model attributes
     * 
     * This struct is used to store data on model attributes.
     */
    class ModelAttrs {
    public:
        /**
         * @brief Construct an empty Model Attrs object
         */
        ModelAttrs();

        /**
         * @brief Construct a new Model Attrs object from a list of model attributes
         * @param args The model attributes
         */
        ModelAttrs(std::initializer_list<ModelAttr> args);

        /**
         * @brief Construct a new Model Attrs object from a list of object attributes
         * @param obj_attrs The object attributes
         */
        ModelAttrs(ObjectAttrs obj_attrs);

        /**
         * @brief Add a model attribute
         * @param type The GL type of the attribute
         * @param size The size of the attribute
         * @param attr The attribute type
         * 
         * This function adds a model attribute to the list of model attributes.
         */
        void add(GLenum type, GLint size, ModelAttrType attr);

        /**
         * @brief Get the model attributes
         * @return The model attributes
         */
        EOGLL_NO_DISCARD std::vector<ModelAttr> getAttrs();

        /**
         * @brief Get the number of objects in the model attributes
         * @return The number of objects in the model attributes
         * 
         * Sums up the number of objects in each attribute.
         */
        EOGLL_NO_DISCARD int num();

        /**
         * @brief Get the amount of attributes
         * @return Number of attributes
         */
        EOGLL_NO_DISCARD int size();

        /**
         * @brief Build the model attributes
         * @param vao The VAO to build the model attributes on
         */
        void build(int vao);

        /**
         * @brief Get the model attribute at the specified index
         * @param i The index
         * @return The model attribute at the specified index
         */
        ModelAttr& operator[](int i);

    private:
        /**
         * @brief Get the attribute type from the object attribute type
         * @param type The object attribute type
         * @return The attribute type
         * 
         * A helper function to convert object attribute types to model attribute types.
         */
        ModelAttrType getAttrType(EogllObjectAttrType type);

        /// @brief The model attributes
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