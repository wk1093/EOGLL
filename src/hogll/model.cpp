#include "hogll/model.hpp"

namespace ogl {
    namespace internal {
        GlMesh packMesh(Mesh mesh, ObjectAttrs attrs) {
            GlMesh glMesh;

            int num = 0;
            for (EogllObjectAttr a : attrs.attrs()) {
                num += a.num;
            }
            glMesh.vert.reserve(num);
            
            for (const Vertex& vert : mesh.vert) {
                for (int i = 0; i < attrs.size(); i++) {
                    EogllObjectAttr a = attrs.attrs()[i];
                    switch (a.type) {
                        case EOGLL_ATTR_POSITION: {
                            if (a.num >= 1) glMesh.vert.push_back(vert.pos.x);
                            if (a.num >= 2) glMesh.vert.push_back(vert.pos.y);
                            if (a.num >= 3) glMesh.vert.push_back(vert.pos.z);
                            break;
                        }
                        case EOGLL_ATTR_NORMAL: {
                            if (a.num >= 1) glMesh.vert.push_back(vert.norm.x);
                            if (a.num >= 2) glMesh.vert.push_back(vert.norm.y);
                            if (a.num >= 3) glMesh.vert.push_back(vert.norm.z);
                            break;
                        }
                        case EOGLL_ATTR_TEXTURE: {
                            if (a.num >= 1) glMesh.vert.push_back(vert.tex.x);
                            if (a.num >= 2) glMesh.vert.push_back(vert.tex.y);
                            break;
                        }
                    }
                }
            }
            glMesh.indices = mesh.indices;
            return glMesh;
        }
    }

    RenderModel::RenderModel(std::string path, ObjectAttrs attrs, std::string relpath, bool relative_to_obj) : attrs(attrs) {
        this->attrs = attrs;
        if (relative_to_obj) {
            std::string objpath = path.substr(0, path.find_last_of("/\\"));
            this->path = objpath + "/" + relpath;
        } else {
            this->path = relpath;
        }
        if (this->path.back() != '/') {
            this->path += "/";
        }
        loadModel(path);

        // the model is loaded into Meshes but we need to generate all the GlMeshes and then put them into the BufferObjects
        // we want to do all this ahead of time so that the model can just be drawn when needed and we don't have to do much processing
        // *speed intensifies*
        for (internal::Mesh& mesh : meshes) {
            internal::GlMesh glMesh = internal::packMesh(mesh, attrs);

            int vao, vbo, ebo;
            vao = eogllGenVertexArray();
            vbo = eogllGenBuffer(vao, GL_ARRAY_BUFFER, glMesh.vert.size() * sizeof(float), glMesh.vert.data(), GL_STATIC_DRAW);
            ebo = eogllGenBuffer(vao, GL_ELEMENT_ARRAY_BUFFER, glMesh.indices.size() * sizeof(unsigned int), glMesh.indices.data(), GL_STATIC_DRAW);
            attrs.build(vao);
            mesh.render = new BufferObject(vao, vbo, ebo, glMesh.indices.size()*sizeof(unsigned int), GL_UNSIGNED_INT);
            // we are going to use malloc instead
            std::unordered_map<std::string, int> texturesLoaded;
            for (internal::Texture tex : mesh.textures) {
                // std::cout << "Uniform '" << (std::string("sampler_") + tex.type + std::to_string(texturesLoaded[tex.type]++)) << "' loaded" << std::endl;
                EOGLL_LOG_DEBUG(stdout, "Uniform '%s' loaded\n", (std::string("sampler_") + tex.type + std::to_string(texturesLoaded[tex.type]++)).c_str());
            }
        }
    }

    RenderModel::~RenderModel() {
        for (internal::Mesh& mesh : meshes) {
            for (internal::Texture tex : mesh.textures) {
                eogllDeleteTexture(tex.texture);
            }
        }

        // TODO: delete whatever needs to be deleted
    }

    void RenderModel::draw(Window* window, EogllShaderProgram* shader, Camera camera, Projection projection, Model model) {
        for (internal::Mesh& mesh : meshes) {
            if (mesh.render == nullptr) {
                continue;
            }
            std::unordered_map<std::string, int> texturesLoaded;
            int totalTextures = 0;
            eogllUseProgram(shader);
            camera.update(shader);
            projection.update(shader, "projection", *window);
            model.update(shader);
            for (internal::Texture tex : mesh.textures) {
                eogllBindTextureUniform(tex.texture, shader, (std::string("sampler_") + tex.type + std::to_string(texturesLoaded[tex.type]++)).c_str(), totalTextures++);
            }
            mesh.render->draw(GL_TRIANGLES);
        }
    }

    void RenderModel::draw(Window* window, EogllShaderProgram* shader) {
        for (internal::Mesh& mesh : meshes) {
            if (mesh.render == nullptr) {
                EOGLL_LOG_WARN(stderr, "Mesh has no render object, skipping");
                continue;
            }
            std::unordered_map<std::string, int> texturesLoaded;
            int totalTextures = 0;
            eogllUseProgram(shader);
            for (internal::Texture tex : mesh.textures) {
                eogllBindTextureUniform(tex.texture, shader, (std::string("sampler_") + tex.type + std::to_string(texturesLoaded[tex.type]++)).c_str(), totalTextures++);
            }
            mesh.render->draw(GL_TRIANGLES);
        }
    }


    void RenderModel::loadModel(const std::string& p) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(p, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_GenUVCoords | aiProcess_OptimizeGraph | aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            EOGLL_LOG_ERROR(stderr, "Failed to load model '%s': %s", p.c_str(), importer.GetErrorString());
            return;
        }

        processNode(scene->mRootNode, scene);
    }

    void RenderModel::processNode(aiNode* node, const aiScene* scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

    internal::Mesh RenderModel::processMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<internal::Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<internal::Texture> textures;
        vertices.reserve(mesh->mNumVertices);
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            internal::Vertex vertex;
            vertex.pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            if (mesh->HasNormals()) {
                vertex.norm = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            } else {
                vertex.norm = glm::vec3(0.0f, 0.0f, 0.0f);
            }
            if (mesh->mTextureCoords[0]) {
                vertex.tex = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            } else {
                vertex.tex = glm::vec2(0.0f, 0.0f);
            }
            
            vertices.push_back(vertex);
        }
        indices.reserve(3 * mesh->mNumFaces);
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            if (face.mNumIndices != 3) {
                EOGLL_LOG_ERROR(stderr, "Face is not a triangle, skipping");
                continue;
            }
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        if (mesh->mMaterialIndex >= 0) {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            std::vector<std::pair<aiTextureType, std::string>> textureTypes = {
                {aiTextureType_DIFFUSE, "diffuse"},
                {aiTextureType_SPECULAR, "specular"},
                {aiTextureType_AMBIENT, "ambient"},
                {aiTextureType_EMISSIVE, "emissive"},
                {aiTextureType_HEIGHT, "height"},
                {aiTextureType_NORMALS, "normals"},
                {aiTextureType_SHININESS, "shininess"},
                {aiTextureType_OPACITY, "opacity"},
                {aiTextureType_DISPLACEMENT, "displacement"},
                {aiTextureType_LIGHTMAP, "lightmap"},
                {aiTextureType_REFLECTION, "reflection"},
                {aiTextureType_BASE_COLOR, "base_color"},
                {aiTextureType_NORMAL_CAMERA, "normal_camera"},
                {aiTextureType_EMISSION_COLOR, "emission_color"},
                {aiTextureType_METALNESS, "metalness"},
                {aiTextureType_DIFFUSE_ROUGHNESS, "diffuse_roughness"},
                {aiTextureType_AMBIENT_OCCLUSION, "ambient_occlusion"}
            };
            for (std::pair<aiTextureType, std::string> textureType : textureTypes) {
                std::vector<internal::Texture> maps = loadMaterialTextures(material, textureType.first, textureType.second);
                textures.insert(textures.end(), maps.begin(), maps.end());
            }
        }
        internal::Mesh m;
        m.indices = indices;
        m.textures = textures;
        m.vert = vertices;
        m.render = nullptr;

        return m;
    }

    std::vector<internal::Texture> RenderModel::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
        std::vector<internal::Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);
            bool skip = false;
            for (internal::Texture tex : textures_loaded) {
                if (tex.path == str.C_Str()) {
                    textures.push_back(tex);
                    skip = true;
                    break;
                }
            }
            if (!skip) {
                internal::Texture tex;
                std::string path = this->path + str.C_Str();
                tex.texture = eogllCreateTexture(path.c_str());
                tex.type = typeName;
                tex.path = str.C_Str();
                textures.push_back(tex);
                textures_loaded.push_back(tex);
            }
        }
        return textures;
    }
}