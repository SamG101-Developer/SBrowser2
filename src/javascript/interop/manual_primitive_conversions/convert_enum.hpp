#ifndef SBROWSER2_SRC_JAVASCRIPT_INTEROP_MANUAL_PRIMITIVE_CONVERSIONS_CONVERT_ENUM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_INTEROP_MANUAL_PRIMITIVE_CONVERSIONS_CONVERT_ENUM_HPP

#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/string.hpp"
#include "ext/ranges.hpp"

#include <stdexcept>

#include <magic_enum.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/view/replace.hpp>
#include <v8-primitive.h>
#include <v8-object.h>
#include <v8pp/convert.hpp>


template <type_is_enum T>
struct v8pp::convert<T>
{
    using from_type = T;
    using to_type = v8::Local<v8::String>;

    static auto is_valid(
            v8::Isolate* isolate,
            v8::Local<v8::Value> v8_value)
            -> ext::boolean;

    static auto from_v8(
            v8::Isolate* isolate,
            to_type v8_value)
            -> from_type;

    static auto to_v8(
            v8::Isolate* isolate,
            const from_type& cpp_value)
            -> to_type;
};


template <type_is_enum T>
inline auto v8pp::convert<T>::is_valid(
        v8::Isolate* isolate,
        v8::Local<v8::Value> v8_value) -> ext::boolean
{
    return !v8_value.IsEmpty() && v8_value->IsString();
}


template <type_is_enum T>
auto v8pp::convert<T>::from_v8(
        v8::Isolate* isolate,
        to_type v8_value)
        -> from_type
{
    if (!is_valid(isolate, v8_value))
        throw std::invalid_argument{"Invalid type for converting to an enum value from v8"};

    v8::HandleScope javascript_scope{isolate};

    auto v8_value_string = v8_value.template As<v8::String>();
    auto cpp_value_string = v8pp::convert<ext::string>::from_v8(isolate, v8_value_string);
    auto cpp_value_formatted_string = cpp_value_string == "" ? "_" : cpp_value_string
            | ranges::views::replace('-', '_')
            | ranges::views::uppercase()
            | ranges::to<ext::string>;

    auto cpp_value_enum = magic_enum::enum_cast<T>(std::move(cpp_value_formatted_string));

    if (!cpp_value_enum.has_value())
        throw std::invalid_argument{"Invalid enumeration value (valid values: " + (magic_enum::enum_names<T> | ranges::to<ext::string>) + ")"};

    return *cpp_value_enum;
}


template <type_is_enum T>
auto v8pp::convert<T>::to_v8(
        v8::Isolate* isolate,
        const from_type& cpp_value)
        -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    auto cpp_value_string = ext::string{magic_enum::enum_name(cpp_value)};
    auto cpp_value_formatted_string = cpp_value_string == "_" ? "" : cpp_value_string
            | ranges::views::replace('_', '-')
            | ranges::views::lowercase()
            | ranges::to<ext::string>;

    auto v8_value_string = v8::String::NewFromUtf8(isolate, cpp_value_formatted_string.c_str()).ToLocalChecked();
    return javascript_scope.template Escape(v8_value_string);
}


#endif //SBROWSER2_SRC_JAVASCRIPT_INTEROP_MANUAL_PRIMITIVE_CONVERSIONS_CONVERT_ENUM_HPP
