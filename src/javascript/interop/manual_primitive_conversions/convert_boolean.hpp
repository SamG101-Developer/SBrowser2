#pragma once
#ifndef SBROWSER2_CONVERT_BOOLEAN_HPP
#define SBROWSER2_CONVERT_BOOLEAN_HPP
//
// #include "ext/boolean.hpp"
// #include <v8-primitive.h>
// #include <v8pp/convert.hpp>
//
//
// template <>
// struct v8pp::convert<ext::boolean>
// {
//     using from_type = ext::boolean;
//     using to_type = v8::Local<v8::Boolean>;
//
//     static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean;
//     static auto from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
//     static auto to_v8(v8::Isolate* isolate, from_type cpp_value) -> to_type;
// };
//
//
// inline auto v8pp::convert<ext::boolean>::is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
// {
//     return not v8_value.IsEmpty() && v8_value->IsBoolean();
// }
//
//
// inline auto v8pp::convert<ext::boolean>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
// {
//     if (!is_valid(isolate, v8_value))
//         throw std::invalid_argument{"Invalid type for converting to ext::boolean from v8"};
//
//     v8::HandleScope javascript_scope{isolate};
//
//     // Create the ext::boolean object from the primitive bool conversion.
//     auto cpp_value = convert<bool>::from_v8(isolate, v8_value.As<v8::Boolean>());
//     return from_type{cpp_value};
// }
//
//
// auto v8pp::convert<ext::boolean>::to_v8(v8::Isolate* isolate, from_type cpp_value) -> to_type
// {
//     v8::EscapableHandleScope javascript_scope{isolate};
//
//     // Create the v8::Boolean object from the primitive bool conversion.
//     auto v8_value = convert<bool>::to_v8(isolate, static_cast<bool>(cpp_value));
//     return javascript_scope.Escape(v8_value.As<v8::Boolean>());
// }


#endif //SBROWSER2_CONVERT_BOOLEAN_HPP
