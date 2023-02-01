module;
#include "ext/macros.hpp"


export module apis.html.html_style_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_style_element)
        : public html::html_element
        , public cssom::mixins::link_style
{
public constructors:
    html_style_element();
    MAKE_PIMPL(html_style_element);
    MAKE_V8_AVAILABLE();

private js_properties:
    DEFINE_GETTER(disabled, ext::boolean);
    DEFINE_GETTER(media, ext::string_view);
    DEFINE_GETTER(blocking, ext::span<ext::string>);

    DEFINE_SETTER(disabled, ext::boolean);
    DEFINE_SETTER(media, ext::string);
};
