#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_OTHER_DOM_EXCEPTION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_OTHER_DOM_EXCEPTION_PRIVATE_HPP

#include "dom_object_private.hpp"

#include "ext/pimpl.hpp"
#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(dom)


DEFINE_PRIVATE_CLASS(dom::other, dom_exception) : virtual dom_object_private
{
    ext::string message;
    v8_custom_error_t code;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_OTHER_DOM_EXCEPTION_PRIVATE_HPP
