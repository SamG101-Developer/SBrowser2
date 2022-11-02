#pragma once
#ifndef SBROWSER2_CONVERT_MAP_HPP
#define SBROWSER2_CONVERT_MAP_HPP

#include "ext/map.hpp"

#include <v8-container.h>
#include <v8-object.h>
#include <v8pp/convert.hpp>


template <typename K, typename V>
struct v8pp::convert<ext::map<K, V>>
{
    using from_type = ext::map<K, V>;
    using to_type = v8::Local<v8::Map>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean;
    static auto from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type;
};


template <typename K, typename V>
inline auto v8pp::convert<ext::map<K, V>>::is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
{
    return not v8_value.IsEmpty() && v8_value->IsMap() && not v8_value->IsArray();
}


template <typename K, typename V>
inline auto v8pp::convert<ext::map<K, V>>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    if (!is_valid(isolate, v8_value))
        throw std::invalid_argument{"Invalid type for converting to ext::map<K, V> from v8"};

    v8::HandleScope javascript_scope{isolate};

    // Save the current context, and get the keys in the v8 map.
    auto v8_context = isolate->GetCurrentContext();
    auto v8_keys    = v8_value.template As<v8::Map>()->GetPropertyNames(v8_context).ToLocalChecked();
    from_type cpp_value;

    // Iterate through the numeric positions of the keys, in the v8 map keys list.
    for (auto i = 0; i < v8_keys->Length(); ++i)
    {
        // Get the key from the index, and the value that it corresponds to.
        auto v8_key = v8_keys->Get(v8_context, i).ToLocalChecked();
        auto v8_val = v8_value.template As<v8::Map>()->Get(v8_context, v8_key).ToLocalChecked();

        // Convert the key and value to cpp values, and save them back into the cpp map.
        auto cpp_key = v8pp::convert<K>::from_v8(isolate, v8_key);
        auto cpp_val = v8pp::convert<V>::from_v8(isolate, v8_val);
        cpp_value.try_emplace(cpp_key, cpp_val);
    }

    return cpp_value;
}


template <typename K, typename V>
inline auto v8pp::convert<ext::map<K, V>>::to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // Save the current context.
    auto v8_context = isolate->GetCurrentContext();
    auto v8_value   = v8::Map::New(isolate);

    // Iterate through the keys and values in the cpp map.
    for (const auto& [cpp_key, cpp_val]: cpp_value)
    {
        // Convert the key and value to v8 values, and save them back into the v8 map.
        auto v8_key = v8pp::convert<K>::to_v8(isolate, cpp_key);
        auto v8_val = v8pp::convert<V>::to_v8(isolate, cpp_val);
        v8_value->Set(v8_context, v8_key, cpp_val);
    }

    return javascript_scope.template Escape(v8_value);
}


#endif //SBROWSER2_CONVERT_MAP_HPP
