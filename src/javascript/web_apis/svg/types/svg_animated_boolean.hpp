#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_ANIMATED_BOOLEAN_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_ANIMATED_BOOLEAN_HPP

// Inheritance Includes & This Class
#include "svg/types/svg_abstract_animatable.hpp"
namespace svg::types {class svg_animated_boolean;}
namespace svg::types {class svg_animated_boolean_private;}

// Other Includes & Forward Declarations


class svg::types::svg_animated_boolean
: public svg::types::svg_abstract_animatable<ext::boolean>
{
public constructors:
    svg_animated_boolean();
    MAKE_PIMPL(svg_animated_boolean);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_ANIMATED_BOOLEAN_HPP
