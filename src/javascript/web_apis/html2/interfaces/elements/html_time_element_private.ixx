module;
#include "ext/macros.hpp"


export module apis.html.html_time_element:p;
import apis.html.html_element;


DEFINE_PRIVATE_CLASS(html, html_time_element)
        : html::html_element_private
{
public:
    MAKE_QIMPL(html_time_element);
};
