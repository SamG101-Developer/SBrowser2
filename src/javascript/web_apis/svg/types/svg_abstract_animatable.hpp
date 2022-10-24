#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_ABSTRACT_ANIMATABLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_ABSTRACT_ANIMATABLE_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace svg::types {template <typename T> class svg_abstract_animatable;}
namespace svg::types {template <typename T> class svg_abstract_animatable_private;}


template <typename T>
class svg::types::svg_abstract_animatable
        : public dom_object
{
public constructors:
    svg_abstract_animatable();
    MAKE_PIMPL_TEMPLATED(svg_abstract_animatable, T);
    MAKE_V8_AVAILABLE;

public js_properties:
    virtual DEFINE_GETTER(base_val, T) = 0;
    virtual DEFINE_GETTER(anim_val, T) = 0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_ABSTRACT_ANIMATABLE_HPP
