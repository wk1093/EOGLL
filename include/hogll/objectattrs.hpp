/**
 * @file objectattrs.hpp
 * @brief HOGLL object attributes header file
 * @date 2024-10-9
 *
 * HOGLL object attributes header file
 */

#pragma once
#ifndef _HOGLL_OBJECT_ATTRS_HPP_
#define _HOGLL_OBJECT_ATTRS_HPP_

#include "pch.hpp"

namespace ogl {
    struct ObjectAttrs {
    private:
        EogllObjectAttrs buffer;
    public:
        inline ObjectAttrs(EogllObjectAttrs ebo) : buffer(ebo) {}
        ObjectAttrs();

        struct AttrInput {
            GLenum type;
            GLint size;
            EogllObjectAttrType attr;
        };
        ObjectAttrs(std::initializer_list<AttrInput> args);

        void add(GLenum type, GLint size, EogllObjectAttrType attr);

        EogllObjectAttrs* getBuffer();

        int size();

        std::vector<EogllObjectAttr> attrs();

        void build(int vao);
    };
}

#endif