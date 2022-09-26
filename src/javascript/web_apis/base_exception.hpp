#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BASE_EXCEPTION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BASE_EXCEPTION_HPP

#include "dom_object.hpp"

#include "ext/concepts.hpp"

#include "base_exception_private.hpp"


template <type_is_enum T>
class base_exception : public virtual dom_object
{
public aliases:
    using exception_t = T;

public constructors:
    base_exception();
    base_exception(ext::string&& message, T&& code);
    MAKE_PIMPL_TEMPLATED(base_exception, T);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(message, ext::string);
    DEFINE_GETTER(code, ext::number<size_t>);
    DEFINE_GETTER(name, ext::string_view);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BASE_EXCEPTION_HPP
