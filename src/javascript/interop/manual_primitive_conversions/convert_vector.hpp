#pragma once
#include "v8-internal.h"
#ifndef SBROWSER2_CONVERT_VECTOR_HPP
#define SBROWSER2_CONVERT_VECTOR_HPP

#include "ext/vector.hpp"
#include <v8-container.h>
#include <v8pp/convert.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/range/operations.hpp>


template <typename T>
struct v8pp::convert<ext::vector<T>>
{
    using from_type = ext::vector<T>;
    using to_type = v8::Local<v8::Object>;

    auto static is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {return not v8_value.IsEmpty() && v8_value->IsArray();}
    auto static from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    auto static to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type;
};


template <typename T>
inline auto v8pp::convert<ext::vector<T>>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    if (!is_valid(isolate, v8_value)) throw std::invalid_argument{"Invalid type for converting to ext::vector<T> from v8"};
    v8::HandleScope javascript_scope{isolate};
    // TODO : try and get the internal data pointer

    // Save the current context.
    auto v8_context             = isolate->GetCurrentContext();
    auto v8_value_vector        = v8_value.template As<v8::Array>();
    auto v8_value_vector_length = v8_value_vector->Length();
    from_type cpp_value_vector;

    // Iterate through the numeric positions of the values, in the v8 vector.
    for (auto v8_value_vector_key_index = 0; v8_value_vector_key_index < v8_value_vector_length; ++v8_value_vector_key_index)
    {
        // Get the value from the index.
        auto v8_value_vector_val = v8_value_vector->Get(v8_context, v8_value_vector_key_index);

        // Convert the value to a cpp value, and save it back into the cpp vector.
        auto cpp_value_vector_val = v8pp::convert<T>::from_v8(isolate, v8_value_vector_val);
        cpp_value_vector.insert(cpp_value_vector_val);
    }

    return cpp_value_vector;
}


template <typename T>
inline auto v8pp::convert<ext::vector<T>>::to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // Save the current context.
    auto v8_value = v8::Array::New(isolate, ranges::data(cpp_value | ranges::views::transform(v8pp::convert<T>::to_v8)), cpp_value.length());
    return javascript_scope.template Escape(v8_value);
}


template <typename T>
struct v8pp::is_wrapped_class<ext::vector<T>> : std::false_type{};


#endif //SBROWSER2_CONVERT_VECTOR_HPP
