#ifndef SBROWSER2_CONVERT_VECTOR_LIKE_HPP
#define SBROWSER2_CONVERT_VECTOR_LIKE_HPP

#include "ext/vector_like.ixx"
#include <range/v3/to_container.hpp>
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <v8-container.h>
#include <v8pp/convert.hpp>


template <typename T>
struct v8pp::convert<ext::vector_like_linked<T>>
{
    using from_type = ext::vector_like_linked<T>;
    using to_type   = v8::Local<v8::Object>;

    auto static is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean;
    static auto from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value_datetime_object) -> to_type;
};


template <typename T>
inline auto v8pp::convert<ext::vector_like_linked<T>>::is_valid(
        v8::Isolate* isolate,
        v8::Local<v8::Value> v8_value)
        -> ext::boolean
{
    return not v8_value.IsEmpty() && v8_value->IsObject();
}


template <typename T>
inline auto v8pp::convert<ext::vector_like_linked<T>>::from_v8(
        v8::Isolate* isolate,
        v8::Local<v8::Value> v8_value)
        -> from_type
{
    if (!is_valid(isolate, v8_value))
        throw std::invalid_argument{"Invalid type for converting to ext::vector_like_linked<_Tx> from v8"};

    v8::HandleScope javascript_scope{isolate};

    // save the current context, and get the property names of the object
    auto v8_context    = isolate->GetCurrentContext();
    auto v8_object     = v8_value.template As<v8::Object>();
    auto v8_properties = v8_object->GetPropertyNames(v8_context).ToLocalChecked();

    // get the values at the numerical attributes - ie object[0] = object.0, and convert them to a cpp vector
    ext::vector<T> cpp_value = v8pp::convert<ext::vector<ext::string>>::from_v8(isolate, v8_properties)
            | ranges::views::filter([](auto property_name) {return std::isdigit(property_name);})
            | ranges::views::transform([](auto property_name) {return std::stoll(property_name);})
            | ranges::views::transform([v8_object, v8_context](auto index) {return v8pp::convert<T>::from_v8(v8_object->Get(v8_context, index));})
            | ranges::to<ext::vector<T>>;

    return from_type{cpp_value};
}


template <typename T>
inline auto v8pp::convert<ext::vector_like_linked<T>>::to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};
    
    auto v8_value = v8::Object::New(
            isolate, v8::Null(isolate),
            cpp_value.d_func()->linked_vector | ranges::views::enumerate | ranges::views::keys,
            cpp_value.d_func()->linked_vector,
            cpp_value.d_func()->linked_vector.size());

    return javascript_scope.template Escape(v8_value);
}


#endif //SBROWSER2_CONVERT_VECTOR_LIKE_HPP
