module;
#include "ext/macros.hpp"


export module apis.html.html_base_element:p;
import apis.html.html_element;


DEFINE_PRIVATE_CLASS(html, html_base_element)
        : html::html_element_private
{
public:
    MAKE_QIMPL(html_base_element);

public:
    ext::string target;
};
