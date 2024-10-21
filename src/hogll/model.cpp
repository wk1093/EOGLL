#include "hogll/model.hpp"

namespace ogl {
    inline glm::mat4 convertToGLM(aiMatrix4x4 mat) {
        glm::mat4 result;
        result[0][0] = mat.a1; result[0][1] = mat.a2; result[0][2] = mat.a3; result[0][3] = mat.a4;
        result[1][0] = mat.b1; result[1][1] = mat.b2; result[1][2] = mat.b3; result[1][3] = mat.b4;
        result[2][0] = mat.c1; result[2][1] = mat.c2; result[2][2] = mat.c3; result[2][3] = mat.c4;
        result[3][0] = mat.d1; result[3][1] = mat.d2; result[3][2] = mat.d3; result[3][3] = mat.d4;
        return result;
    }

    ModelAttr::ModelAttr() {}
    ModelAttr::ModelAttr(GLenum type, GLint num, ModelAttrType attr) : type(type), size(num*eogllSizeOf(type)), attr(attr) {}

    int ModelAttr::num() {
        return size / eogllSizeOf(type);
    }

    ModelAttrs::ModelAttrs() {}

    ModelAttrs::ModelAttrs(std::initializer_list<ModelAttr> args) : attrs(args) {}

    ModelAttrs::ModelAttrs(ObjectAttrs obj_attrs) {
        for (int i = 0; i < obj_attrs.size(); i++) {
            EogllObjectAttr attr = obj_attrs.attrs()[i];
            EogllVertAttribData vab = obj_attrs.getBuffer()->builder.attribs[i];
            add(vab.type, vab.size, getAttrType(attr.type));
        }
    }

    void ModelAttrs::add(GLenum type, GLint size, ModelAttrType attr) {
        attrs.push_back({type, size*eogllSizeOf(type), attr});
    }

    std::vector<ModelAttr> ModelAttrs::getAttrs() {
        return attrs;
    }

    int ModelAttrs::num() {
        int s = 0;
        for (ModelAttr a : attrs) {
            s += a.size / eogllSizeOf(a.type);
        }
        return s;
    }

    int ModelAttrs::size() {
        return attrs.size();
    }

    ModelAttr& ModelAttrs::operator[](int i) {
        return attrs[i];
    }



    void ModelAttrs::build(int vao) {
        GLsizei stride = 0;
        for (ModelAttr a : attrs) {
            stride += a.size;
        }
        glBindVertexArray(vao);
        uint64_t offset = 0;
        for (int i = 0; i < attrs.size(); i++) {
            ModelAttr a = attrs[i];
            glVertexAttribPointer(i, a.size / eogllSizeOf(a.type), a.type, GL_FALSE, stride, (void*)offset);
            glEnableVertexAttribArray(i);
            offset += a.size;
        }
    }

    ModelAttrType ModelAttrs::getAttrType(EogllObjectAttrType type) {
        switch (type) {
            case EOGLL_ATTR_POSITION: return POSITION;
            case EOGLL_ATTR_NORMAL: return NORMAL;
            case EOGLL_ATTR_TEXTURE: return TEXTURE;
            default:
                EOGLL_LOG_ERROR(stderr, "Invalid attribute type");
                return POSITION;
        }
        return POSITION;
    }



    namespace internal {
        GlMesh packMesh(Mesh mesh, ModelAttrs attrs) {
            GlMesh glMesh;

            glMesh.vert.reserve(attrs.num());
            
            for (const Vertex& vert : mesh.vert) {
                for (int i = 0; i < attrs.size(); i++) {
                    ModelAttr a = attrs[i];
                    switch (a.attr) {
                        case POSITION: {
                            if (a.num() >= 1) glMesh.vert.push_back(vert.pos.x);
                            if (a.num() >= 2) glMesh.vert.push_back(vert.pos.y);
                            if (a.num() >= 3) glMesh.vert.push_back(vert.pos.z);
                            break;
                        }
                        case NORMAL: {
                            if (a.num() >= 1) glMesh.vert.push_back(vert.norm.x);
                            if (a.num() >= 2) glMesh.vert.push_back(vert.norm.y);
                            if (a.num() >= 3) glMesh.vert.push_back(vert.norm.z);
                            break;
                        }
                        case TEXTURE: {
                            if (a.num() >= 1) glMesh.vert.push_back(vert.tex.x);
                            if (a.num() >= 2) glMesh.vert.push_back(vert.tex.y);
                            break;
                        }
                        case BONE_IDS: {
                            // reinterpret cast ints to a float
                            if (a.num() >= 1) glMesh.vert.push_back(reinterpret_cast<const float*>(&vert.bone_ids)[0]);
                            if (a.num() >= 2) glMesh.vert.push_back(reinterpret_cast<const float*>(&vert.bone_ids)[1]);
                            if (a.num() >= 3) glMesh.vert.push_back(reinterpret_cast<const float*>(&vert.bone_ids)[2]);
                            if (a.num() >= 4) glMesh.vert.push_back(reinterpret_cast<const float*>(&vert.bone_ids)[3]);
                            break;
                        }
                        case BONE_WEIGHTS: {
                            if (a.num() >= 1) glMesh.vert.push_back(vert.bone_weights.x);
                            if (a.num() >= 2) glMesh.vert.push_back(vert.bone_weights.y);
                            if (a.num() >= 3) glMesh.vert.push_back(vert.bone_weights.z);
                            if (a.num() >= 4) glMesh.vert.push_back(vert.bone_weights.w);
                            break;
                        }
                        default:
                            EOGLL_LOG_ERROR(stderr, "Invalid attribute type");
                            break;

                    }
                }
            }
            glMesh.indices = mesh.indices;
            return glMesh;
        }
    }

    RenderModel::RenderModel(std::string path, ModelAttrs attrs, std::string relpath, bool relative_to_obj) : attrs(attrs) {
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

    void RenderModel::draw(EogllShaderProgram* shader, std::function<void(EogllShaderProgram*)> preDraw) {
        for (internal::Mesh& mesh : meshes) {
            if (mesh.render == nullptr) {
                EOGLL_LOG_WARN(stderr, "Mesh has no render object, skipping");
                continue;
            }
            std::unordered_map<std::string, int> texturesLoaded;
            int totalTextures = 0;
            eogllUseProgram(shader);
            preDraw(shader);
            for (internal::Texture tex : mesh.textures) {
                eogllBindTextureUniform(tex.texture, shader, (std::string("sampler_") + tex.type + std::to_string(texturesLoaded[tex.type]++)).c_str(), totalTextures++);
            }
            mesh.render->draw(GL_TRIANGLES);
        }
    }


    void RenderModel::loadModel(const std::string& p) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(p, aiProcessPreset_TargetRealtime_MaxQuality);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            EOGLL_LOG_ERROR(stderr, "Failed to load model '%s': %s", p.c_str(), importer.GetErrorString());
            return;
        }

        processNode(scene->mRootNode, scene);
    }

    void RenderModel::processNode(aiNode* node, const aiScene* scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene, node->mTransformation));
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

    internal::Mesh RenderModel::processMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4 transform) {
        std::vector<internal::Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<internal::Texture> textures;
        vertices.reserve(mesh->mNumVertices);
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            internal::Vertex vertex;
            vertex.pos = (glm::vec4(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z, 1.0f) * convertToGLM(transform));
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

            vertex.bone_ids = glm::ivec4(-1, -1, -1, -1);
            vertex.bone_weights = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
            
            vertices.push_back(vertex);
        }

        extractBones(vertices, mesh, scene);
        
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

    void RenderModel::extractBones(std::vector<internal::Vertex>& vertices, aiMesh* mesh, const aiScene* scene) {
        for (unsigned int i = 0; i < mesh->mNumBones; i++) {
            int boneID = -1;
            std::string boneName = mesh->mBones[i]->mName.C_Str();
            if (boneInfoMap.find(boneName) == boneInfoMap.end()) {
                BoneInfo newBoneInfo;
                newBoneInfo.id = boneCounter;
                newBoneInfo.offset = convertToGLM(mesh->mBones[i]->mOffsetMatrix);
                boneInfoMap[boneName] = newBoneInfo;
                boneID = boneCounter++;
            } else {
                boneID = boneInfoMap[boneName].id;
            }
            assert(boneID != -1);
            auto weights = mesh->mBones[i]->mWeights;
            int numWeights = mesh->mBones[i]->mNumWeights;

            for (int j = 0; j < numWeights; j++) {
                int vertexID = weights[j].mVertexId;
                float weight = weights[j].mWeight;
                assert(vertexID <= vertices.size());
                for (int k = 0; k < 4; k++) {
                    if (vertices[vertexID].bone_ids[k] == -1) {
                        vertices[vertexID].bone_ids[k] = boneID;
                        vertices[vertexID].bone_weights[k] = weight;
                        break;
                    }
                }
            }
        }
    }
}