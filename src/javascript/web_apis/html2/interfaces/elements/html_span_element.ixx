module;
#include "ext/macros.hpp"


export module apis.html.html_span_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_span_element) final
        : public html::html_element
{
public constructors:
    html_span_element();
    MAKE_PIMPL(html_span_element);
    MAKE_V8_AVAILABLE(WINDOW);
};
