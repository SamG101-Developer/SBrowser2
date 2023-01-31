module;
#include "ext/macros.hpp"


export module apis.html.html_meta_element:p;
import apis.html.html_element;


DEFINE_PRIVATE_CLASS(html, html_meta_element)
        : html::html_element_private
{
public:
    html_meta_element_private(); // TODO : Insertion steps
    MAKE_QIMPL(html_meta_element);

public:
    ext::string name;
    ext::string http_equiv;
    ext::string content;
    ext::string media;
};
