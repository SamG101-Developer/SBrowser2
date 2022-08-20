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
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value_map_like) -> to_type;
};


template <typename K, typename V>
inline auto v8pp::convert<ext::map<K, V>>::is_valid(
        v8::Isolate* isolate,
        v8::Local<v8::Value> v8_value)
        -> ext::boolean
{
    return not v8_value.IsEmpty() && v8_value->IsMap() && not v8_value->IsArray();
}


template <typename K, typename V>
inline auto v8pp::convert<ext::map<K, V>>::from_v8(
        v8::Isolate* isolate,
        v8::Local<v8::Value> v8_value)
        -> from_type
{
    if (!is_valid(isolate, v8_value)) throw std::invalid_argument{"Invalid type for converting to ext::map<K, V> from v8"};
    v8::HandleScope javascript_scope{isolate};

    // save the current context, and get the keys in the v8 map
    auto v8_context        = isolate->GetCurrentContext();
    auto v8_value_map      = v8_value.template As<v8::Map>();
    auto v8_value_map_keys = v8_value_map->GetPropertyNames(v8_context).ToLocalChecked();
    from_type cpp_value_map;

    // iterate through the numeric positions of the keys, in the v8 map keys list
    for (auto v8_value_map_key_index = 0; v8_value_map_key_index < v8_value_map_keys->Length(); ++v8_value_map_key_index)
    {
        // get the key from the index, and the value that it corresponds to
        auto v8_value_map_key = v8_value_map_keys->Get(v8_context, v8_value_map_key_index).ToLocalChecked();
        auto v8_value_map_val = v8_value_map->Get(v8_context, v8_value_map_key).ToLocalChecked();

        // convert the key and value to cpp values, and save them back into the cpp map
        auto cpp_value_map_key = v8pp::convert<K>::from_v8(isolate, v8_value_map_key);
        auto cpp_value_map_val = v8pp::convert<V>::from_v8(isolate, v8_value_map_val);
        cpp_value_map.at(cpp_value_map_key) = cpp_value_map_val;
    }

    return cpp_value_map;
}


template <typename K, typename V>
inline auto v8pp::convert<ext::map<K, V>>::to_v8(
        v8::Isolate* isolate,
        const from_type& cpp_value_map)
        -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // save the current context
    auto v8_context   = isolate->GetCurrentContext();
    auto v8_value_map = v8::Map::New(isolate);

    // iterate through the keys and values in the cpp map
    for (const auto& [cpp_value_map_key, cpp_value_map_val]: cpp_value_map)
    {
        // convert the key and value to v8 values, and save them back into the v8 map
        auto v8_value_map_key = v8pp::convert<K>::to_v8(isolate, cpp_value_map_key);
        auto v8_value_map_val = v8pp::convert<V>::to_v8(isolate, cpp_value_map_val);
        v8_value_map->Set(v8_context, v8_value_map_key, cpp_value_map_val);
    }

    return javascript_scope.template Escape(v8_value_map);
}


#endif //SBROWSER2_CONVERT_MAP_HPP
