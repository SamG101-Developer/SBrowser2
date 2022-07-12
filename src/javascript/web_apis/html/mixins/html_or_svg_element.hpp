#pragma once
#ifndef SBROWSER2_HTML_OR_SVG_ELEMENT_HPP
#define SBROWSER2_HTML_OR_SVG_ELEMENT_HPP

#include "dom_object.hpp"
namespace html::mixins {class html_or_svg_element;}

#include "ext/map.hpp"


class html::mixins::html_or_svg_element
        : public web_apis::dom_object
{
public js_methods:
    auto focus(ext::string_any_map_view options = {}) -> void;
    auto blur();

public js_properties:
    ext::property<ext::string> nonce;
    ext::property<ext::string_string_map> dataset;

    ext::property<ext::boolean> autofocus;
    ext::property<ext::number<long>> tabIndex;
};


#endif //SBROWSER2_HTML_OR_SVG_ELEMENT_HPP
