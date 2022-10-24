#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_LENGTH_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_LENGTH_HPP

#include "dom_object.hpp"
namespace svg::types {class svg_length;}
namespace svg::types {class svg_length_private;}


class svg::types::svg_length
        : public virtual dom_object
{
public constructors:
    svg_length();
    MAKE_PIMPL(svg_length);
    MAKE_V8_AVAILABLE;

public js_static_constants:
    constexpr static ext::number<ushort> SVG_LENGTHTYPE_UNKNOWN = 0;
    constexpr static ext::number<ushort> SVG_LENGTHTYPE_NUMBER = 1;
    constexpr static ext::number<ushort> SVG_LENGTHTYPE_PERCENTAGE = 2;
    constexpr static ext::number<ushort> SVG_LENGTHTYPE_EMS = 3;
    constexpr static ext::number<ushort> SVG_LENGTHTYPE_EXS = 4;
    constexpr static ext::number<ushort> SVG_LENGTHTYPE_PX = 5;
    constexpr static ext::number<ushort> SVG_LENGTHTYPE_CM = 6;
    constexpr static ext::number<ushort> SVG_LENGTHTYPE_MM = 7;
    constexpr static ext::number<ushort> SVG_LENGTHTYPE_IN = 8;
    constexpr static ext::number<ushort> SVG_LENGTHTYPE_PT = 9;
    constexpr static ext::number<ushort> SVG_LENGTHTYPE_PC = 10;

public js_methods:
    auto new_value_specified_uniutes(ext::number<ushort> unit_type, ext::number<float> valie_in_pecified_units) -> void;
    auto convert_to_specified_units(ext::number<ushort> unit_type) -> void;

public js_properties:
    DEFINE_GETTER(unit_type, ext::number<ushort>);
    DEFINE_GETTER(value, ext::number<float>);
    DEFINE_GETTER(value_in_sepcified_units, ext::number<float>);
    DEFINE_GETTER(value_as_string, ext::string_view);

    DEFINE_SETTER(value, ext::number<float>);
    DEFINE_SETTER(value_in_sepcified_units, ext::number<float>);
    DEFINE_SETTER(value_as_string, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_LENGTH_HPP
