module;
#include "ext/macros.hpp"


export module apis.html.html_link_element:p;
import apis.html.html_element;


DEFINE_PRIVATE_CLASS(html, html_link_element)
        : html::html_element_private
        , html::mixins::link_style_private
{
public:
    MAKE_QIMPL(html_link_element);
};
