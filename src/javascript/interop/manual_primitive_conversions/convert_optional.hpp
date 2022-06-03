#ifndef SBROWSER2_CONVERT_OPTIONAL_HPP
#define SBROWSER2_CONVERT_OPTIONAL_HPP

#include <ext/optional.hpp>
#include <v8-primitive.h>
#include <v8pp/convert.hpp>


template <typename T>
struct v8pp::convert<ext::optional<T>>
{
    using from_type = ext::optional<T>;
    using to_type = v8::Local<v8::Value>;

    auto static is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {return not v8_value.IsEmpty();}
    auto static from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    auto static to_v8(v8::Isolate* isolate, const from_type& cpp_value_optional) -> to_type;
};


template <typename T>
inline auto v8pp::convert<ext::optional<T>>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    if (not is_valid(isolate, v8_value)) throw std::invalid_argument{"Invalid type for converting to ext::optional<T> from v8"};
    v8::HandleScope javascript_scope{isolate};

    // create the ext::optional<T> object, with either null for javascript Null, or the converted object
    auto cpp_value_optional = from_type{v8_value->IsNull() ? ext::null : convert<T>::from_v8(isolate, v8_value)};
    return cpp_value_optional;
}


template <typename T>
inline auto v8pp::convert<ext::optional<T>>::to_v8(v8::Isolate* isolate, const from_type& cpp_value_optional) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // create the v8::Value or Null object from the ext::optional<T>, given its current state - has_key()
    auto v8_value_optional = cpp_value_optional.has_value() ? convert<T>::to_v8(isolate, cpp_value_optional) : v8::Null(isolate);
    return v8_value_optional;
}


template <typename T>
struct v8pp::is_wrapped_class<ext::optional<T>> : std::false_type{};


#endif //SBROWSER2_CONVERT_OPTIONAL_HPP
