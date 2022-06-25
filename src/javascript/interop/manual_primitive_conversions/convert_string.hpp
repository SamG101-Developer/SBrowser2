#pragma once
#ifndef SBROWSER2_CONVERT_STRING_HPP
#define SBROWSER2_CONVERT_STRING_HPP

#include <ext/string.hpp>
#include <v8-primitive.h>
#include <v8pp/convert.hpp>


template <>
struct v8pp::convert<ext::string>
{
    using from_type = ext::string;
    using to_type = v8::Local<v8::String>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {return not v8_value.IsEmpty();}
    static auto from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value_string_object) -> to_type;
};


inline auto v8pp::convert<ext::string>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    if (not is_valid(isolate, v8_value)) throw std::invalid_argument{"Invalid type for converting to ext::string from v8"};
    v8::HandleScope javascript_scope{isolate};

    // create the ext::string object from the primitive string conversion
    auto v8_value_string            = v8_value->IsString() ? v8_value.As<v8::String>() : v8_value->ToString(isolate->GetCurrentContext()).ToLocalChecked();
    auto cpp_value_string_primitive = v8pp::convert<std::string>::from_v8(isolate, v8_value_string);
    auto cpp_value_string_object    = from_type{std::move(cpp_value_string_primitive)};
    return cpp_value_string_object;
}


inline auto v8pp::convert<ext::string>::to_v8(v8::Isolate* isolate, const from_type& cpp_value_string_object) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // create the v8::String object from the primitive string conversion
    auto cpp_value_string_primitive = static_cast<std::string>(cpp_value_string_object);
    auto v8_value                   = v8pp::convert<std::string>::to_v8(isolate, cpp_value_string_primitive);
    auto v8_value_string            = v8_value.As<v8::String>();
    return javascript_scope.Escape(v8_value_string);
}



template <>
struct v8pp::convert<ext::string_view>
{
    using from_type = ext::string_view;
    using to_type = v8::Local<v8::String>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {return not v8_value.IsEmpty();}
    static auto from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value_string_object) -> to_type;
};


inline auto v8pp::convert<ext::string_view>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    return v8pp::convert<ext::string>::from_v8(isolate, v8_value);
}


inline auto v8pp::convert<ext::string_view>::to_v8(v8::Isolate* isolate, const from_type& cpp_value_string_object) -> to_type
{
    return v8pp::convert<ext::string>::to_v8(isolate, cpp_value_string_object);
}


#endif //SBROWSER2_CONVERT_STRING_HPP
