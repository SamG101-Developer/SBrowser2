#ifndef SBROWSER2_CONVERT_NULLPTR_T_HPP
#define SBROWSER2_CONVERT_NULLPTR_T_HPP

#include "ext/boolean.hpp"
#include <v8pp/convert.hpp>


template <>
struct v8pp::convert<std::nullptr_t>
{
    using from_type = std::nullptr_t;
    using to_type = v8::Local<v8::Value>;

    auto static is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean;
    auto static from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    auto static to_v8(v8::Isolate* isolate, from_type cpp_value) -> to_type;
};


inline auto v8pp::convert<std::nullptr_t>::is_valid(
        v8::Isolate* isolate,
        v8::Local<v8::Value> v8_value)
        -> ext::boolean
{
    return !v8_value.IsEmpty() && v8_value->IsNull();
}


inline auto v8pp::convert<std::nullptr_t>::from_v8(
        v8::Isolate* isolate,
        v8::Local<v8::Value> v8_value)
        -> from_type
{
    if (!is_valid(isolate, v8_value)) throw std::invalid_argument{"Invalid type for converting to nullptr from v8"};
    v8::HandleScope javascript_scope{isolate};

    // return nullptr (no other options derived from the v8_value)
    auto cpp_value_nullptr = nullptr;
    return cpp_value_nullptr;
}


auto v8pp::convert<std::nullptr_t>::to_v8(
        v8::Isolate* isolate,
        from_type cpp_value)
        -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // create the v8 value Null (no other options derived from the cpp_value)
    auto js_value_none = v8::Null(isolate);
    return javascript_scope.Escape(js_value_none);
}


#endif //SBROWSER2_CONVERT_NULLPTR_T_HPP
