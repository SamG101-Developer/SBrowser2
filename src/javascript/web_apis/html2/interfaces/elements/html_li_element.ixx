module;
#include "ext/macros.hpp"


export module apis.html.html_li_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_li_element)
        : public html::html_element
{
public constructors:
    html_li_element();
    MAKE_PIMPL(html_li_element);
    MAKE_V8_AVAILABLE();

public js_properties:
    DEFINE_GETTER(value, ext::number<long>);
    DEFINE_SETTER(value, ext::number<long>);
};
