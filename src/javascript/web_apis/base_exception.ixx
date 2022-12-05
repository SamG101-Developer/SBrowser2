module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.base_exception;
import apis.dom_object;
import ext.concepts;
import ext.number;
import ext.string;
import ext.tuple;

template <ext::type_is_enum T>
class base_exception_private;


export template <ext::type_is_enum T>
class base_exception : public virtual dom_object
{
public typedefs:
    using exception_t = T;

public constructors:
    base_exception();
    base_exception(ext::u8string&& message, T&& code);
    base_exception(const base_exception&) = default;
    base_exception(base_exception&&) noexcept = default;
    MAKE_PIMPL_T(base_exception, T);
    MAKE_V8_AVAILABLE(ALL);

private js_properties:
    DEFINE_GETTER(message, ext::string);
    DEFINE_GETTER(code, ext::number<size_t>);
    DEFINE_GETTER(name, ext::string_view);
};
