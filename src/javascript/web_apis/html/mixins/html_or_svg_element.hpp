#pragma once
#ifndef SBROWSER2_HTML_OR_SVG_ELEMENT_HPP
#define SBROWSER2_HTML_OR_SVG_ELEMENT_HPP

#include "dom_object.hpp"
namespace html::mixins {class html_or_svg_element;}
namespace html::mixins {class html_or_svg_element_private;}

#include "ext/map.hpp"


class html::mixins::html_or_svg_element
        : public virtual dom_object
{
public constructors:
    html_or_svg_element();
    MAKE_PIMPL(html_or_svg_element);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto focus(detail::focus_options_t&& options = {}) -> void;
    auto blur();

private js_properties:
    DEFINE_GETTER(dataset, ext::map<ext::string COMMA ext::any>);
    DEFINE_GETTER(nonce, ext::string_view);
    DEFINE_GETTER(autofocus, ext::boolean);
    DEFINE_GETTER(tab_index, ext::number<long>);

    DEFINE_SETTER(nonce, ext::string);
    DEFINE_SETTER(autofocus, ext::boolean);
    DEFINE_SETTER(tab_index, ext::number<long>);
};


#endif //SBROWSER2_HTML_OR_SVG_ELEMENT_HPP
