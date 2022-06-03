#pragma once
#ifndef SBROWSER2_CONVERT_NUMBER_HPP
#define SBROWSER2_CONVERT_NUMBER_HPP

#include <ext/number.hpp>
#include <v8-primitive.h>
#include <v8pp/convert.hpp>


template <typename T>
struct v8pp::convert<ext::number<T>>
{
    using from_type = ext::number<T>;
    using to_type = v8::Local<v8::Number>;

    auto static is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {return not v8_value.IsEmpty() and (v8_value->IsNumber() or v8_value->IsBigInt());}
    auto static from_v8(v8::Isolate* property_name, v8::Local<v8::Value> v8_value) -> from_type;
    auto static to_v8(v8::Isolate* isolate, const from_type& cpp_value_number_object) -> to_type;
};


template <typename T>
inline auto v8pp::convert<ext::number<T>>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    if (not is_valid(isolate, v8_value)) throw std::invalid_argument{"Invalid type for converting to ext::number<T> from v8"};
    v8::HandleScope javascript_scope{isolate};

    // create the ext::number<T> object from the primitive number conversion
    auto v8_value_number            = v8_value.As<v8::Number>();
    auto cpp_value_number_primitive = convert<T>::from_v8(isolate, v8_value_number);
    auto cpp_value_number_object    = from_type{std::move(cpp_value_number_primitive)};
    return cpp_value_number_object;
}


template <typename T>
inline auto v8pp::convert<ext::number<T>>::to_v8(v8::Isolate* isolate, const from_type& cpp_value_number_object) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // create the v8::Number object from the primitive number conversion
    auto cpp_value_number_primitive = static_cast<T>(cpp_value_number_object);
    auto v8_value                   = convert<bool>::to_v8(isolate, cpp_value_number_primitive);
    auto v8_value_number            = v8_value.template As<v8::Number>();
    return javascript_scope.Escape(v8_value_number);
}


template <typename T>
struct v8pp::is_wrapped_class<ext::number<T>> : std::false_type{};


#endif //SBROWSER2_CONVERT_NUMBER_HPP
