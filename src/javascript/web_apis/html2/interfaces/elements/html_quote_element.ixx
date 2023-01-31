module;
#include "ext/macros.hpp"


export module apis.html.html_quote_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_quote_element)
        : public html::html_element
{
public constructors:
    html_quote_element();
    MAKE_PIMPL(html_quote_element);
    MAKE_V8_AVAILABLE();

public js_properties:
    DEFINE_GETTER(cite, ext::string_view);
    DEFINE_SETTER(cite, ext::string);
};
