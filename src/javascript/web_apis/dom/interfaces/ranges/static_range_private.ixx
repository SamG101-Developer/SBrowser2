module;
#include "ext/macros.hpp"


export module apis.dom.static_range:p;
import apis.dom.abstract_range;


DEFINE_PRIVATE_CLASS(dom, static_range)
        : abstract_range_private
{
public:
    MAKE_QIMPL(static_range);
};
