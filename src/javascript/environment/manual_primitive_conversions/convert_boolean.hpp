#pragma once
#ifndef SBROWSER2_CONVERT_BOOLEAN_HPP
#define SBROWSER2_CONVERT_BOOLEAN_HPP

#include <ext/boolean.hpp>
#include <v8-primitive.h>
#include <v8pp/convert.hpp>


template <>
struct v8pp::convert<ext::boolean>
{
    using from_type = ext::boolean;
    using to_type = v8::Local<v8::Boolean>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {return not v8_value.IsEmpty() and v8_value->IsBoolean();}
    static auto from_v8(v8::Isolate* property_name, v8::Local<v8::Value> v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type;
};


inline auto v8pp::convert<ext::boolean>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    if (not is_valid(isolate, v8_value)) throw std::invalid_argument{"Invalid type for converting to ext::boolean from v8"};
    v8::HandleScope javascript_scope{isolate};

    // create the ext::boolean object from the primitive bool conversion
    auto v8_value_bool            = v8_value.As<v8::Boolean>();
    auto cpp_value_bool_primitive = convert<bool>::from_v8(isolate, v8_value_bool);
    auto cpp_value_bool_object    = from_type{std::move(cpp_value_bool_primitive)};
    return cpp_value_bool_object;
}


auto v8pp::convert<ext::boolean>::to_v8(v8::Isolate* isolate, const from_type& cpp_value_bool_object) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // create the v8::Boolean object from the primitive bool conversion
    auto cpp_value_bool_primitive = static_cast<bool>(cpp_value_bool_object);
    auto v8_value                 = convert<bool>::to_v8(isolate, cpp_value_bool_primitive);
    auto v8_value_bool            = v8_value.As<v8::Boolean>();
    return javascript_scope.Escape(v8_value_bool);
}


#endif //SBROWSER2_CONVERT_BOOLEAN_HPP
