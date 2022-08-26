#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_NUMBER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_NUMBER_HPP

#include "dom_object.hpp"
namespace svg::types {class svg_number;}


class svg::types::svg_number
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(svg_number);
    svg_number() = default;

public js_properties:
    ext::property<ext::number<float>> value;

private cpp_accessors:
    DEFINE_SETTER(value);
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_NUMBER_HPP
