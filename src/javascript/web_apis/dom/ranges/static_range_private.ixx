module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.static_range_private;
import apis.dom.abstract_range_private;


DEFINE_PRIVATE_CLASS(dom, static_range)
        : abstract_range_private
{
    MAKE_QIMPL(static_range);
};
