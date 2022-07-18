#ifndef SBROWSER2_CONVERT_MAP_LIKE_HPP
#define SBROWSER2_CONVERT_MAP_LIKE_HPP

#include "ext/map_like.hpp"
#include "ext/vector.hpp"

#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <v8-container.h>
#include <v8pp/convert.hpp>


template <typename K, typename V>
struct v8pp::convert<ext::map_like<K, V>>
{
    using from_type = ext::map_like<K, V>;
    using to_type   = v8::Local<v8::Object>;

    auto static is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {return not v8_value.IsEmpty() && v8_value->IsObject();}
    static auto from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value_map_like) -> to_type;
};


template <typename K, typename V>
inline auto v8pp::convert<ext::map_like<K, V>>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    if (not is_valid(isolate, v8_value)) throw std::invalid_argument{"Invalid type for converting to ext::map_like<K, V> from v8"};
    v8::HandleScope javascript_scope{isolate};

    // save the current context, and get the property names of the object
    auto v8_context = isolate->GetCurrentContext();
    auto v8_value_object = v8_value.template As<v8::Object>();
    auto v8_value_object_property_names = v8_value_object->GetPropertyNames(v8_context).ToLocalChecked();

    // get the values at the non-enumerable attributes - ie object["a"] = object.a, and convert them to a cpp map
    ext::map<std::string, V> cpp_value_map;
    v8pp::convert<ext::vector<ext::string>>::from_v8(isolate, v8_value_object_property_names)
            | ranges::views::filter([v8_value_object, v8_context](auto v8_property_name) {v8_value_object->GetPropertyAttributes(v8_context, v8_property_name) & v8::PropertyAttribute::DontEnum;})
            | ranges::views::transform([v8_value_object, v8_context](auto v8_property_name) {return v8pp::convert<V>::from_v8(v8_value_object->Get(v8_context, v8_property_name));});

    from_type cpp_value_map_like{cpp_value_map};
    return cpp_value_map_like;
}


template <typename K, typename V>
inline auto v8pp::convert<ext::map_like<K, V>>::to_v8(v8::Isolate* isolate, const from_type& cpp_value_map_like) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // save the current context
    auto v8_context      = isolate->GetCurrentContext();
    auto v8_value_object = v8::Object::New(isolate);

    // iterate through the keys and values in the cpp map
    for (const auto& [cpp_value_map_key, cpp_value_map_val]: cpp_value_map_like)
    {
        // convert the key and value to v8 values, and save them back into the v8 map
        auto v8_value_map_key = v8pp::convert<std::string>::to_v8(isolate, cpp_value_map_key);
        auto v8_value_map_val = v8pp::convert<V>::to_v8(isolate, cpp_value_map_key);
        v8_value_object->DefineOwnProperty(v8_context, v8_value_map_key, v8_value_map_val, v8::PropertyAttribute::DontEnum);
    }

    return javascript_scope.template Escape(v8_value_object);
}


#endif //SBROWSER2_CONVERT_MAP_LIKE_HPP
