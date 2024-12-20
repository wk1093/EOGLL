#include "hogll/shadergen.hpp"

namespace ogl {
    EogllShaderProgram* basicShaderGenerator(ModelAttrs attrs, bool defaultUniforms) { // defaultUniforms means model/view/projection
        // this will just generate a shader that works for the given attributes
        // this shader has a requirement of the position attribute
        std::string vertexShader = "#version 330 core\n";

        std::string positionAttr;
        bool hasNormal = false;
        std::string normalAttr;
        for (int i = 0; i < attrs.size(); i++) {
            ModelAttr type = attrs[i];
            if (type.type != GL_FLOAT) {
                EOGLL_LOG_ERROR(stderr, "Attribute type is not GL_FLOAT");
                return nullptr;
            }
            std::string name = "eogll_attr_"+std::to_string(i);
            std::string t = "layout(location="+std::to_string(i)+") in vec"+std::to_string(type.size/eogllSizeOf(type.type))+" "+name+";\n";
            vertexShader += t;
            if (type.attr == POSITION) {
                positionAttr = name;
            } else if (type.attr == NORMAL) {
                hasNormal = true;
                normalAttr = name;
            }
        }

        if (defaultUniforms) {
            vertexShader += "uniform mat4 model;\n";
            vertexShader += "uniform mat4 view;\n";
            vertexShader += "uniform mat4 projection;\n";
        }

        if (hasNormal) {
            vertexShader += "out vec3 Normal;\n";
        }

        vertexShader += "void main() {\n";
        vertexShader += "    gl_Position = ";
        if (defaultUniforms) {
            vertexShader += "projection * view * model * ";
        }
        vertexShader += "vec4("+positionAttr+", 1.0);\n";
        if (hasNormal) {
            if (defaultUniforms) {
                vertexShader += "    Normal = mat3(transpose(inverse(model))) * "+normalAttr+";\n";
            } else {
                vertexShader += "    Normal = "+normalAttr+";\n";
            }
        }
        vertexShader += "}\n";

        std::string fragmentShader = "#version 330 core\n";
        // if we happen to have the normal attribute, we will make a simple shader that just has static directional lighting
        // if not, we will just make a simple shader that just has a static color
        fragmentShader += "out vec4 FragColor;\n";

        if (hasNormal) {
            fragmentShader += "in vec3 Normal;\n";
        }

        fragmentShader += "void main() {\n";
        if (hasNormal) {
            fragmentShader += "    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));\n";
            fragmentShader += "    float diff = max(dot(Normal, lightDir), 0.0);\n";
            fragmentShader += "    vec3 color = vec3(1.0, 0.5, 0.2);\n";
            fragmentShader += "    FragColor = vec4(color * diff, 1.0);\n";
        } else {
            fragmentShader += "    FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n";
        }
        fragmentShader += "}\n";
        EogllShaderProgram* shader = eogllLinkProgram(vertexShader.c_str(), fragmentShader.c_str());

        return shader;
    }
}