#ifndef SBROWSER2_CONVERT_PROPERTY_HPP
#define SBROWSER2_CONVERT_PROPERTY_HPP

#include <ext/property.hpp>
#include <v8-primitive.h>
#include <v8pp/convert.hpp>


template <typename T>
struct v8pp::convert<ext::property<T>>
{
    using from_type = ext::property<T>;
    using to_type = v8::Local<v8::Value>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {not v8_value.IsEmpty();}
    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type;
};


template <typename T>
inline auto v8pp::convert<ext::property<T>>::from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type
{
    if (not is_valid(isolate, v8_value)) throw std::invalid_argument{"Invalid type for converting to ext::any from v8"};
    v8::HandleScope javascript_scope{isolate};

    // create the cpp value from the property setter - implicit value::operator=(...) call in convert<T>
    auto cpp_value = v8pp::convert<T>::from_v8(isolate, v8_value);
    return cpp_value;
}


template <typename T>
inline auto v8pp::convert<ext::property<T>>::to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // create the v8 value from the property getter - implicit value::operator T() call in convert<T>
    auto v8_value = v8pp::convert<T>::to_v8(isolate, static_cast<T>(cpp_value));
    return javascript_scope.template Escape(v8_value);
}


#endif //SBROWSER2_CONVERT_PROPERTY_HPP
