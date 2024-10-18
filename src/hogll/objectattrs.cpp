#include "hogll/objectattrs.hpp"

namespace ogl {

    ObjectAttrs::ObjectAttrs() {
        buffer = eogllCreateObjectAttrs();
    }

    ObjectAttrs::ObjectAttrs(std::initializer_list<AttrInput> args) {
        buffer = eogllCreateObjectAttrs();
        for (auto& arg : args) {
            eogllAddObjectAttr(&buffer, arg.type, arg.size, arg.attr);
        }
    }

    void ObjectAttrs::add(GLenum type, GLint size, EogllObjectAttrType attr) {
        eogllAddObjectAttr(&buffer, type, size, attr);
    }

    EogllObjectAttrs* ObjectAttrs::getBuffer() {
        return &buffer;
    }

    int ObjectAttrs::size() {
        return buffer.numTypes;
    }

    std::vector<EogllObjectAttr> ObjectAttrs::attrs() {
        std::vector<EogllObjectAttr> types;
        for (int i = 0; i < buffer.numTypes; i++) {
            types.push_back(buffer.types[i]);
        }
        return types;
    }

}