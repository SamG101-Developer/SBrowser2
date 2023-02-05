module;
#include "ext/macros.hpp"


export module apis.html.html_hr_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_hr_element) final
        : public html::html_element
{
public constructors:
    html_hr_element();
    MAKE_PIMPL(html_hr_element);
    MAKE_V8_AVAILABLE();
};
