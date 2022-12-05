#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_OTHER_DOM_EXCEPTION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_OTHER_DOM_EXCEPTION_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "base_exception_private.ixx"

#include INCLUDE_INNER_TYPES(dom)


DEFINE_PRIVATE_CLASS(dom::other, dom_exception)
        : base_exception_private<detail::dom_exception_error_t>
{
    MAKE_QIMPL(dom_exception);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_OTHER_DOM_EXCEPTION_PRIVATE_HPP
