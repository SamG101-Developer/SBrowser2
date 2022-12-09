module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.range_private;
import apis.dom.abstract_range_private;


DEFINE_PRIVATE_CLASS(dom, range) final
        : abstract_range_private
{
    MAKE_QIMPL(range);
};
