#ifndef SBROWSER2_HTML_ELEMENT_HPP
#define SBROWSER2_HTML_ELEMENT_HPP

#include "dom/nodes/element.hpp"
#include "html/mixins/content_editable.hpp"
#include "html/mixins/html_or_svg_element.hpp"
namespace html::elements {class html_element;}

namespace html::other {class element_internals;}


class html::elements::html_element
        : public dom::nodes::element
        , public mixins::content_editable
        , public mixins::html_or_svg_element
{
public constructors:
    html_element();

public js_methods:
    auto click() -> void;
    auto attach_internals() -> other::element_internals;

public js_properties:
    ext::property<ext::string> title; // TODO : CE_REACTIONS
    ext::property<ext::string> lang; // TODO : CE_REACTIONS
    ext::property<ext::string> translate; // TODO : CE_REACTIONS
    ext::property<ext::string> dir; // TODO : CE_REACTIONS

    ext::property<ext::string> access_key_label;
    ext::property<ext::string> access_key; // TODO : CE_REACTIONS
    ext::property<ext::string> autocapitalize; // TODO : CE_REACTIONS
    ext::property<ext::string> inner_text; // TODO : CE_REACTIONS
    ext::property<ext::string> outer_text; // TODO : CE_REACTIONS

    ext::property<ext::boolean> hidden; // TODO : CE_REACTIONS
    ext::property<ext::boolean> inert; // TODO : CE_REACTIONS
    ext::property<ext::boolean> draggable; // TODO : CE_REACTIONS
    ext::property<ext::boolean> spellcheck; // TODO : CE_REACTIONS

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    DEFINE_GETTER(inner_text);
    DEFINE_GETTER(outer_text) {return inner_text();};

    DEFINE_SETTER(inner_text);
    DEFINE_SETTER(outer_text);
};


#endif //SBROWSER2_HTML_ELEMENT_HPP
