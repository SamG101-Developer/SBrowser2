module;
#include "ext/macros.hpp"


export module apis.html.html_style_element:p;
import apis.html.html_element;


DEFINE_PRIVATE_CLASS(html, html_style_element)
        : html::html_element_private
        , cssom::mixins::link_style_private
{
public:
    MAKE_QIMPL(html_style_element);

public:
    ext::string media;
    ext::vector<ext::string> blocking;
};
