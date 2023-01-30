module;
#include "ext/macros.hpp"


export module apis.html.html_element:p;
import apis.dom.element;


DEFINE_PRIVATE_CLASS(html, html_element)
        : dom::element_private
{
public:
    MAKE_QIMPL(html_element);
};
