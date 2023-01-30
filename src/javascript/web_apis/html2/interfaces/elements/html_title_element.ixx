module;
#include "ext/macros.hpp"


export module apis.html.html_title_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_title_element)
        : public html::html_element
{
public constructors:
    html_title_element();
    MAKE_PIMPL(html_title_element);
    MAKE_V8_AVAILABLE();

public js_properties:
    DEFINE_GETTER(text, ext::string);
    DEFINE_SETTER(text, ext::string);
};
