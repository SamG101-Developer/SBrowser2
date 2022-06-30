#ifndef SBROWSER2_CONVERT_VECTOR_LIKE_HPP
#define SBROWSER2_CONVERT_VECTOR_LIKE_HPP

#include <ranges>

#include <ext/vector_like.hpp>
#include <v8-container.h>
#include <v8pp/convert.hpp>


template <typename _Tx>
struct v8pp::convert<ext::vector_like<T>>
{
    using from_type = ext::vector_like<T>;
    using to_type   = v8::Local<v8::Object>;

    auto static is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {return not v8_value.IsEmpty() && v8_value->IsObject();}
    static auto from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value_vector_like) -> to_type;
};


template <typename _Tx>
inline auto v8pp::convert<ext::vector_like<T>>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    if (not is_valid(isolate, v8_value)) throw std::invalid_argument{"Invalid type for converting to ext::vector_like<_Tx> from v8"};
    v8::HandleScope javascript_scope{isolate};

    // save the current context, and get the property names of the object
    auto v8_context = isolate->GetCurrentContext();
    auto v8_value_object = v8_value.template As<v8::Object>();
    auto v8_value_object_property_names = v8_value_object->GetPropertyNames(v8_context).ToLocalChecked();

    // get the values at the numerical attributes - ie object[0] = object.0, and convert them to a cpp vector
    ext::vector<T> cpp_value_vector;
    std::ranges::copy(v8pp::convert<ext::vector<std::string>>::from_v8(isolate, v8_value_object_property_names)
            | std::ranges::views::filter([](auto property_name) {return std::isdigit(property_name);})
            | std::ranges::views::transform([](auto property_name) {return std::stoll(property_name);})
            | std::ranges::views::transform([v8_value_object, v8_context](auto index) {return v8pp::convert<T>::from_v8(v8_value_object->Get(v8_context, index));})
            , cpp_value_vector);

    from_type cpp_value_vector_like {cpp_value_vector};
    return cpp_value_vector_like;
}


template <typename _Tx>
inline auto v8pp::convert<ext::vector_like<T>>::to_v8(v8::Isolate* isolate, const from_type& cpp_value_vector_like) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // save the current context
    auto v8_context      = isolate->GetCurrentContext();
    auto v8_value_object = v8::Object::New(isolate);

    // iterate through the values in the cpp vector
    for (auto cpp_value_vector_index = 0; cpp_value_vector_index < cpp_value_vector_like.length; ++cpp_value_vector_index)
    {
        // convert the value to v8 a value, and save it back into the v8 vector
        auto v8_value_vector_idx = static_cast<uint32_t>(cpp_value_vector_index);
        auto v8_value_vector_val = v8pp::convert<T>::to_v8(cpp_value_vector_like[cpp_value_vector_index]);
        v8_value_object->Set(v8_context, v8_value_vector_idx, v8_value_vector_val);
    }

    return javascript_scope.template Escape(v8_value_object);
}


#endif //SBROWSER2_CONVERT_VECTOR_LIKE_HPP
