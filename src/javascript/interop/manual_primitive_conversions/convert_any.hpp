#pragma once
#ifndef SBROWSER2_CONVERT_ANY_HPP
#define SBROWSER2_CONVERT_ANY_HPP

#include <javascript/environment/manual_primitive_conversions/convert_boolean.hpp>
#include <javascript/environment/manual_primitive_conversions/convert_number.hpp>
#include <javascript/environment/manual_primitive_conversions/convert_string.hpp>

#include <ext/any.hpp>
#include <v8-primitive.h>
#include <v8pp/convert.hpp>


template <>
struct v8pp::convert<ext::any>
{
    using from_type = ext::any;
    using to_type = v8::Local<v8::Value>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {return true;}
    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type;
};


inline auto v8pp::convert<ext::any>::from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type
{
    if (not is_valid(isolate, v8_value)) throw std::invalid_argument{"Invalid type for converting to ext::any from v8"};
    v8::HandleScope javascript_scope{isolate};

    // create the value of the correct type based on the type of v8 value passed into the method
    if (v8_value->IsUndefined() || v8_value.IsEmpty()) return from_type{};
    if (v8_value->IsNull()) return from_type{nullptr};
    if (v8_value->IsBoolean()) return from_type{convert<ext::boolean>::from_v8(isolate, v8_value.As<v8::Boolean>())};
    if (v8_value->IsNumber()) return from_type{convert<ext::number<double>>::from_v8(isolate, v8_value.As<v8::Number>())};
    if (v8_value->IsBigInt()) return from_type{convert<ext::number<size_t>>::from_v8(isolate, v8_value.As<v8::BigInt>())};
    if (v8_value->IsString()) return from_type{convert<ext::string>::from_v8(isolate, v8_value.As<v8::String>())};
    if (v8_value->IsSymbol()); /* TODO */
    if (v8_value->IsObject()); /* TODO */

    // if the data type is unknown (ie hint to implement)
    throw std::invalid_argument{"Unknown type being converted to ext::any from v8"};
}


inline auto v8pp::convert<ext::any>::to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // create the value of the correct type based n the type of the cpp value passed into the method
    if (cpp_value.is_empty()) return javascript_scope.Escape(v8::Undefined(isolate));
    if (cpp_value.type() == typeid(void)) return javascript_scope.Escape(v8::Null(isolate));
    if (cpp_value.type() == typeid(ext::boolean)) return javascript_scope.Escape(convert<ext::boolean>::to_v8(isolate, cpp_value.to<ext::boolean>()));
    if (cpp_value.is_arithmetic_type()) return javascript_scope.Escape(convert<ext::number<double>>::to_v8(isolate, cpp_value.to<ext::number<double>>())); // TODO : Number()/BigInt()?
    if (cpp_value.type() == typeid(ext::string)) return javascript_scope.Escape(convert<ext::string>::to_v8(isolate, cpp_value.to<ext::string>()));
    if (/* TODO : SYMBOL */ false);
    if (/* TODO : Object */ false);

    // if the data type is unknown (ie hint to implement)
    throw std::invalid_argument{"Unknown type being converted to ext::any from v8"};
}

#endif //SBROWSER2_CONVERT_ANY_HPP
