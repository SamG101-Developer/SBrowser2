module;
#include "ext/macros.hpp"


export module apis.html.html_time_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_time_element)
        : public html::html_element
{
public constructors:
    html_time_element();
    MAKE_PIMPL(html_time_element);
    MAKE_V8_AVAILABLE();

public js_properties:
    DEFINE_GETTER(date_time, ext::string);
};
