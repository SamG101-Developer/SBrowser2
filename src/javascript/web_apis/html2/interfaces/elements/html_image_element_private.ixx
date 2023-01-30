module;
#include "ext/macros.hpp"


export module apis.html.html_image_element:p;
import apis.html.html_element;


DEFINE_PRIVATE_CLASS(html, html_image_element)
        : html::html_element_private
{
public:
    MAKE_QIMPL(html_image_element);

public:
    detail::lazy_loading_steps_t lazy_loading_steps;
};
