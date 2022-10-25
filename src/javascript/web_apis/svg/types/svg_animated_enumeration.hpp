#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_ANIMATED_ENUMERATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_ANIMATED_ENUMERATION_HPP

// Inheritance Includes & This Class
#include "svg/types/svg_abstract_animatable.hpp"
namespace svg::types {class svg_animated_enumeration;}
namespace svg::types {class svg_animated_enumeration_private;}

// Other Includes & Forward Declarations


class svg::types::svg_animated_enumeration
        : public svg::types::svg_abstract_animatable<ext::number<ushort>>
{
public constructors:
    svg_animated_enumeration();
    MAKE_PIMPL(svg_animated_enumeration);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_SETTER(base_val, ext::number<ushort>) override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_ANIMATED_ENUMERATION_HPP
