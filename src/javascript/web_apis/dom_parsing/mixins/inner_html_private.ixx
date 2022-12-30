module;
#include "ext/macros.hpp"


export module apis.dom_parsing.mixins.inner_html:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(dom_parsing::mixins, inner_html)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(inner_html);
};
