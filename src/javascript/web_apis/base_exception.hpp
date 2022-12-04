#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BASE_EXCEPTION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BASE_EXCEPTION_HPP

#include "dom_object.hpp"



#include "base_exception_private.hpp"


template <ext::type_is_enum T>
class base_exception : public virtual dom_object
{
public aliases:
    using exception_t = T;

public constructors:
    base_exception();
    base_exception(ext::u8string&& message, T&& code);
    base_exception(const base_exception&) = default;
    base_exception(base_exception&&) noexcept = default;
    MAKE_PIMPL_TEMPLATED(base_exception, T);
    MAKE_V8_AVAILABLE(ALL);

private js_properties:
    DEFINE_GETTER(message, ext::string);
    DEFINE_GETTER(code, ext::number<size_t>);
    DEFINE_GETTER(name, ext::string_view);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BASE_EXCEPTION_HPP
