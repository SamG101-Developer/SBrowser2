module;
#include "ext/macros.hpp"


export module apis.html::mixins.html_or_svg_element;
import apis.dom_object;


DEFINE_PUBLIC_CLASS(html::mixins, html_or_svg_element)
        : public dom_object
{
public typedefs:
    using focus_options_t = ext::map<ext::string, ext::any>;

public constructors:
    html_or_svg_element();
    MAKE_PIMPL(html_or_svg_element);
    MAKE_V8_AVAILABLE();

private js_methods:
    auto focus(focus_options_t&& options = {}) -> void;
    auto blur() -> void;

private js_properties:
    DEFINE_GETTER(dataset, ext::map<ext::string, ext::string>);
    DEFINE_GETTER(nonce, ext::string);
    DEFINE_GETTER(autofocus, ext::boolean);
    DEFINE_GETTER(tab_index, ext::number<long>)

    DEFINE_SETTER(nonce, ext::string);
    DEFINE_SETTER(autofocus, ext::boolean);
    DEFINE_SETTER(tab_index, ext::number<long>)
};
