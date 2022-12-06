module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <memory>
#include <utility>
#include <magic_enum.hpp>
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis._.base_exception;
import apis._.base_exception_private;
import ext.concepts;
import ext.number;
import ext.string;
import ext.tuple;
import js.env.module_type;


template <ext::type_is_enum T>
base_exception<T>::base_exception()
{
    INIT_PIMPL;
}


template <ext::type_is_enum T>
base_exception<T>::base_exception(
        ext::u8string&& message,
        T&& code)
{
    INIT_PIMPL;

    // Set the "message" and "code" attributes to their respective parameter values - use move / forward<T> as
    // necessary.
    ACCESS_PIMPL;
    d->message = std::move(message);
    d->code = std::forward<T>(code);
}


template <ext::type_is_enum T>
auto base_exception<T>::get_message() const -> ext::string
{
    // Reflect the "message" attribute from the private class.
    ACCESS_PIMPL;
    return d->message;
}


template <ext::type_is_enum T>
auto base_exception<T>::get_code() const -> ext::number<size_t>
{
    // Take the "code" attribute from the private class, and return the enum-integer associated with it.
    ACCESS_PIMPL;
    return magic_enum::enum_integer(d->code);
}


template <ext::type_is_enum T>
auto base_exception<T>::get_name() const -> ext::string_view
{
    // Take the "name" attribute from the private class, and return the enum-name associated with it.
    ACCESS_PIMPL;
    return magic_enum::enum_name(d->code);
}


template <ext::type_is_enum T>
auto base_exception<T>::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .template inherit<dom_object>()
        .property("message", &base_exception<T>::get_message)
        .property("code", &base_exception<T>::get_code)
        .property("name", &base_exception<T>::get_name)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
