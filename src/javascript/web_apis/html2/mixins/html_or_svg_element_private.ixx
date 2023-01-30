module;
#include "ext/macros.hpp"


export module apis.html::mixins.html_or_svg_element:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(html::mixins, html_or_svg_element)
        : dom_object_private
{
public:
    MAKE_QIMPL(html_or_svg_element);
};
