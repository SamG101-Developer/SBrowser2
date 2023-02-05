module;
#include "ext/macros.hpp"


export module apis.html.html_mod_element:p;
import apis.html.html_element;


DEFINE_PRIVATE_CLASS(html, html_mod_element)
        : html::html_element_private
{
public:
    MAKE_QIMPL(html_mod_element);

public:
    ext::string cite;
    ext::string date_time;
};
