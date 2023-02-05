module;
#include "ext/macros.hpp"


export module apis.html.html_html_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_html_element) final
        : public html::html_element
{
public constructors:
    html_html_element();
    MAKE_PIMPL(html_html_element);
    MAKE_V8_AVAILABLE();
};
