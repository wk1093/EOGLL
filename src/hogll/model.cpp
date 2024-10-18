#include "hogll/model.hpp"

#include <iostream>

namespace ogl {
    namespace internal {
        GlMesh packMesh(Mesh mesh, ObjectAttrs attrs) {
            GlMesh glMesh;
            
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
            return glMesh;
        }
    }

    Model::Model(std::string path, ObjectAttrs attrs) : path(path), attrs(attrs) {
        std::cout << "Not implemented!" << std::endl;
    }

    Model::~Model() {
        std::cout << "Not implemented!" << std::endl;
    }

    void Model::draw() {
        std::cout << "Not implemented!" << std::endl;
    }


}