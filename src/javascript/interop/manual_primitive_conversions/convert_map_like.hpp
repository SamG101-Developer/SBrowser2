#ifndef SBROWSER2_CONVERT_MAP_LIKE_HPP
#define SBROWSER2_CONVERT_MAP_LIKE_HPP

#include "ext/map_like.hpp"
#include "ext/vector.hpp"
#include "v8-value.h"

#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <v8-container.h>
#include <v8pp/convert.hpp>


template <typename K, typename V>
struct v8pp::convert<ext::map_like_linked<K, V>>
{
    using from_type = ext::map_like_linked<K, V>;
    using to_type   = v8::Local<v8::Object>;

    auto static is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean;
    static auto from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value_map_like) -> to_type;
};


template <typename K, typename V>
auto v8pp::convert<ext::map_like_linked<K, V>>::is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
{
    return not v8_value.IsEmpty() && v8_value->IsObject();
}

template <typename K, typename V>
inline auto v8pp::convert<ext::map_like_linked<K, V>>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    if (!is_valid(isolate, v8_value))
        throw std::invalid_argument{"Invalid type for converting to ext::map_like<K, V> from v8"};

    v8::HandleScope javascript_scope{isolate};

    // Save the current context, and get the property names of the object.
    auto v8_context = isolate->GetCurrentContext();
    auto v8_object = v8_value.template As<v8::Object>();
    auto v8_properties = v8_object->GetPropertyNames(v8_context).ToLocalChecked();

    // Get the values at the non-enumerable attributes - ie object["a"] = object.a, and convert them to a cpp map.
    auto cpp_map = ext::map<ext::string, V>{};
    v8pp::convert<ext::vector<ext::string>>::from_v8(isolate, v8_properties)
            | ranges::views::filter([v8_object, v8_context](auto v8_property_name) {v8_object->GetPropertyAttributes(v8_context, v8_property_name) & v8::PropertyAttribute::DontEnum;})
            | ranges::views::transform([v8_object, v8_context](auto v8_property_name) {return v8pp::convert<V>::from_v8(v8_object->Get(v8_context, v8_property_name));});

    return from_type{cpp_map};
}


template <typename K, typename V>
inline auto v8pp::convert<ext::map_like_linked<K, V>>::to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    auto v8_value  = v8::Object::New(isolate, v8::Null(isolate),
            cpp_value.d_func()->map | ranges::views::keys,
            cpp_value.d_func()->map | ranges::views::values,
            cpp_value.d_func()->map.size());

    return javascript_scope.template Escape(v8_value);
}


#endif //SBROWSER2_CONVERT_MAP_LIKE_HPP
