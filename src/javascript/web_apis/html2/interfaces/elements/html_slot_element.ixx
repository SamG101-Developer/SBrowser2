module;
#include "ext/macros.hpp"


export module apis.html.html_slot_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_slot_element)
        : public html::html_element
{
public constructors:
    html_slot_element();
    MAKE_PIMPL(html_slot_element);
    MAKE_V8_AVAILABLE();
};
