#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BASE_EXCEPTION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BASE_EXCEPTION_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"


#include "ext/string.hpp"


template <ext::type_is_enum T>
struct base_exception_private : virtual dom_object_private
{
    ext::u8string message;
    T code;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BASE_EXCEPTION_PRIVATE_HPP
