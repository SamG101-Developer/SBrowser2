#pragma once
#ifndef SBROWSER2_CONVERT_VECTOR_HPP
#define SBROWSER2_CONVERT_VECTOR_HPP


#include <ext/vector.hpp>
#include <v8-container.h>
#include <v8pp/convert.hpp>


template <typename T>
struct v8pp::convert<ext::vector<T>>
{
    using from_type = ext::vector<T>;
    using to_type = v8::Local<v8::Array>;

    auto static is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {return not v8_value.IsEmpty() and v8_value->IsArray();}
    auto static from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    auto static to_v8(v8::Isolate* isolate, const from_type& cpp_value_vector) -> to_type;
};


template <typename T>
inline auto v8pp::convert<ext::vector<T>>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    if (not is_valid(isolate, v8_value)) throw std::invalid_argument{"Invalid type for converting to ext::vector<T> from v8"};
    v8::HandleScope javascript_scope{isolate};

    // save the current context
    auto v8_context             = isolate->GetCurrentContext();
    auto v8_value_vector        = v8_value.template As<v8::Array>();
    auto v8_value_vector_length = v8_value_vector->Length();
    from_type cpp_value_vector;

    // iterate through the numeric positions of the values, in the v8 vector
    for (auto v8_value_vector_key_index = 0; v8_value_vector_key_index < v8_value_vector_length; ++v8_value_vector_key_index)
    {
        // get the value from the index
        auto v8_value_vector_val = v8_value_vector->Get(v8_context, v8_value_vector_key_index);

        // convert the value to a cpp value, and save it back into the cpp vector
        auto cpp_value_vector_val = v8pp::convert<T>::from_v8(isolate, v8_value_vector_val);
        cpp_value_vector.insert(cpp_value_vector_val);
    }

    return cpp_value_vector;
}


template <typename T>
inline auto v8pp::convert<ext::vector<T>>::to_v8(v8::Isolate* isolate, const from_type& cpp_value_vector) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // save the current context
    auto v8_context      = isolate->GetCurrentContext();
    auto v8_value_vector = v8::Array::New(isolate);

    // iterate through the values in the cpp vector
    for (const auto& cpp_value_vector_val: cpp_value_vector)
    {
        // convert the value to v8 a value, and save it back into the v8 vector
        auto v8_value_vector_val = v8pp::convert<T>::to_v8(isolate, cpp_value_vector_val);
        v8_value_vector->Set(v8_context, v8_value_vector_val);
    }

    return javascript_scope.template Escape(v8_value_vector);
}


template <typename T>
struct v8pp::is_wrapped_class<ext::vector<T>> : std::false_type{};

#endif //SBROWSER2_CONVERT_VECTOR_HPP
