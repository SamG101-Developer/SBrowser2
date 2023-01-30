module;
#include "ext/macros.hpp"


export module apis.html.html_element;
import apis.dom.element;


DEFINE_PUBLIC_CLASS(html, html_element)
        : public dom::element
{
public constructors:
    html_element();
    MAKE_PIMPL(html_element);
    MAKE_V8_AVAILABLE();
};
