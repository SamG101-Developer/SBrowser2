module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.dom_exception_private;
import apis.base_exception_private;

import apis.dom.types;


DEFINE_PRIVATE_CLASS(dom, dom_exception)
        : base_exception_private<detail::dom_exception_error_t>
{
    MAKE_QIMPL(dom_exception);
};
