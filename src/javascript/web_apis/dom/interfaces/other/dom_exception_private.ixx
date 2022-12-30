module;
#include "ext/macros.hpp"


export module apis.dom.dom_exception:p;
import apis.base_exception;

import apis.dom.types;


DEFINE_PRIVATE_CLASS(dom, dom_exception)
        : base_exception_private<detail::dom_exception_error_t>
{
public:
    MAKE_QIMPL(dom_exception);
};
