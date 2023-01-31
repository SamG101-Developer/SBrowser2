module;
#include "ext/macros.hpp"


export module apis.html.html_olist_element:p;
import apis.html.html_element;


DEFINE_PRIVATE_CLASS(html, html_olist_element)
        : html::html_element_private
{
public:
    MAKE_QIMPL(html_olist_element);

public:
    ext::boolean reversed;
    ext::number<long> start;
    ext::string type;
};
