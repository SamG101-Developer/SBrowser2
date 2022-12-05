#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_NUMBER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_NUMBER_HPP


namespace svg::types {class svg_number;}
namespace svg::types {class svg_number_private;}


class svg::types::svg_number
        : public virtual dom_object
{
public constructors:
    svg_number();
    MAKE_PIMPL(svg_number);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(value, ext::number<float>);
    DEFINE_SETTER(value, ext::number<float>);
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_NUMBER_HPP
