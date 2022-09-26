#include "base_exception.hpp"

#include "ext/concepts.hpp"

#include <magic_enum.hpp>


template <type_is_enum T>
base_exception<T>::base_exception(
        ext::string&& message,
        T&& code)
{
    INIT_PIMPL_TEMPLATED(base_exception, T);
    ACCESS_PIMPL_TEMPLATED(base_exception, T);

    d->message = std::move(message);
    d->code = std::forward<T>(code);
}


template <type_is_enum T>
auto base_exception<T>::get_message() const -> ext::string
{
    ACCESS_PIMPL_TEMPLATED(base_exception, T);
    return d->message;
}


template <type_is_enum T>
auto base_exception<T>::get_code() const -> ext::number<size_t>
{
    ACCESS_PIMPL_TEMPLATED(base_exception, T);
    return magic_enum::enum_integer(d->code);
}


template <type_is_enum T>
auto base_exception<T>::get_name() const -> ext::string_view
{
    ACCESS_PIMPL_TEMPLATED(base_exception, T);
    return magic_enum::enum_name(d->code);
}


template <type_is_enum T>
auto base_exception<T>::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<base_exception>{isolate}
        .template inherit<dom_object>()
        .property("message", &base_exception<T>::get_message)
        .property("code", &base_exception<T>::get_code)
        .property("name", &base_exception<T>::get_name)
        .auto_wrap_objects();

    return std::move(conversion);
}
