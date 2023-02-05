module;
#include "ext/macros.hpp"


export module apis.html.html_div_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_div_element) final
        : public html::html_element
{
public constructors:
    html_div_element();
    MAKE_PIMPL(html_div_element);
    MAKE_V8_AVAILABLE();
};
