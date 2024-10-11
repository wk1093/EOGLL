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

}