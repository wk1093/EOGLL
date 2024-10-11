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

#include <initializer_list>

namespace ogl {
    struct ObjectAttrs {
    private:
        EogllObjectAttrs buffer;
    public:
        ObjectAttrs();

        struct AttrInput {
            GLenum type;
            GLint size;
            EogllObjectAttrType attr;
        };
        ObjectAttrs(std::initializer_list<AttrInput> args);

        void add(GLenum type, GLint size, EogllObjectAttrType attr);

        EogllObjectAttrs* getBuffer();
    };
}

#endif