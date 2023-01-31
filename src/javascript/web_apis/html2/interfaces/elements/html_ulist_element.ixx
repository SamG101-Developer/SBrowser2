module;
#include "ext/macros.hpp"


export module apis.html.html_ulist_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_ulist_element)
        : public html::html_element
{
public constructors:
    html_ulist_element();
    MAKE_PIMPL(html_ulist_element);
    MAKE_V8_AVAILABLE();
};
