module;
#include "ext/macros.hpp"


export module apis.dom.dom_exception;
import apis.base_exception;

import apis.dom.types;
import ext.core;
import js.env.module_type;

namespace dom {class abort_signal;}


DEFINE_PUBLIC_CLASS(dom, dom_exception)
        : public base_exception<detail::dom_exception_error_t>
{
public friends:
    friend class dom::abort_signal;

public constructors:
    dom_exception(ext::u8string&& message, exception_t type);
    MAKE_PIMPL(dom_exception);
    MAKE_V8_AVAILABLE(ALL);
    MAKE_SERIALIZABLE;
};
