module;
#include "ext/macros.hpp"


export module apis.html.html_base_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_base_element)
        : public html::html_element
{
public constructors:
    html_base_element();
    MAKE_PIMPL(html_base_element);
    MAKE_V8_AVAILABLE();

public js_properties:
    DEFINE_GETTER(href, ext::string);
    DEFINE_GETTER(target, ext::string_view);

    DEFINE_SETTER(href, ext::string);
    DEFINE_SETTER(target, ext::string);
};
