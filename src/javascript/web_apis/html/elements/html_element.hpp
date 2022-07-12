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
    ext::property<ext::string, _T> title;
    ext::property<ext::string, _T> lang;
    ext::property<ext::string, _T> translate;
    ext::property<ext::string, _T> dir;

    ext::property<ext::string, _F> access_key_label;
    ext::property<ext::string, _T> access_key;
    ext::property<ext::string, _T> autocapitalize;
    ext::property<ext::string, _T> inner_text;
    ext::property<ext::string, _T> outer_text;

    ext::property<ext::boolean, _T> hidden;
    ext::property<ext::boolean, _T> inert;
    ext::property<ext::boolean, _T> draggable;
    ext::property<ext::boolean, _T> spellcheck;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_accessors:
    [[nodiscard]] auto get_inner_text() const -> ext::string;
    [[nodiscard]] auto get_outer_text() const -> ext::string {return inner_text();};

    auto set_inner_text(ext::string_view val) -> void;
    auto set_outer_text(ext::string_view val) -> void;
};


#endif //SBROWSER2_HTML_ELEMENT_HPP
