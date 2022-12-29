module;
#include "ext/macros/pimpl.hpp"


export module apis.dom_parsing.mixins.inner_html_private;
import apis.dom_object_private;


DEFINE_PRIVATE_CLASS(dom_parsing::mixins, inner_html)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(inner_html);
};
