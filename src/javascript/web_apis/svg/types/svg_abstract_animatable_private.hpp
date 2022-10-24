#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_ABSTRACT_ANIMATABLE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_ABSTRACT_ANIMATABLE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"


DEFINE_PRIVATE_CLASS_TEMPLATED(svg::types, svg_abstract_animatable, typename T) : virtual dom_object_private
{
    T base_value;
    T anim_value;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_ABSTRACT_ANIMATABLE_PRIVATE_HPP
