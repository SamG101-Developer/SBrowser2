#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_ANIMATED_BOOLEAN_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_ANIMATED_BOOLEAN_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "svg/types/svg_abstract_animatable_private.hpp"

#include "ext/boolean.ixx"


DEFINE_PRIVATE_CLASS(svg::types, svg_animated_boolean) : svg::types::svg_abstract_animatable_private<ext::boolean> {};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_ANIMATED_BOOLEAN_PRIVATE_HPP
