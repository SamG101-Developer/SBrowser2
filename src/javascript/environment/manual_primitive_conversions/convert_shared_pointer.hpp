#ifndef SBROWSER2_CONVERT_SHARED_POINTER_HPP
#define SBROWSER2_CONVERT_SHARED_POINTER_HPP

#include <ext/shared_pointer.hpp>
#include <v8-primitive.h>
#include <v8pp/convert.hpp>
#include <v8pp/class.hpp>


template <typename T>
struct v8pp::convert<ext::shared_pointer<T>>
{
    using from_type  = ext::shared_pointer<T>;
    using to_type    = v8::Local<v8::Object>;
    using class_type = typename std::remove_cv<T>::type;

    auto static is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {return not v8_value.IsEmpty() and v8_value->IsObject();}
    static auto from_v8(v8::Isolate* property_name, v8::Local<v8::Value> v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type;
};


template <typename T>
inline auto v8pp::convert<ext::shared_pointer<T>>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    return not is_valid(isolate, v8_value) ? nullptr : class_<class_type, shared_ptr_traits>::unwrap_object(isolate, v8_value);
}


template <typename T>
inline auto v8pp::convert<ext::shared_pointer<T>>::to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type
{
    return class_<class_type, shared_ptr_traits>::find_object(isolate, cpp_value);
}


template <typename T>
struct v8pp::is_wrapped_class<ext::shared_pointer<T>> : std::false_type{};


#endif //SBROWSER2_CONVERT_SHARED_POINTER_HPP
