#ifndef SBROWSER2_SRC_JAVASCRIPT_INTEROP_MANUAL_PRIMITIVE_CONVERSIONS_CONVERT_STRING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_INTEROP_MANUAL_PRIMITIVE_CONVERSIONS_CONVERT_STRING_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include <v8pp/convert.hpp>

template<>
struct v8pp::convert<const char8_t*> : v8pp::convert<ext::string_view>
{
    using from_type = const char8_t*;
    using to_type = v8::Local<v8::String>;

    auto static is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {return not v8_value.IsEmpty() && v8_value->IsString();}
    auto static from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    auto static to_v8(v8::Isolate* isolate, from_type cpp_value_datetime_object) -> to_type;
};


inline auto v8pp::convert<const char8_t*>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    if (!is_valid(isolate, v8_value))
        throw std::invalid_argument{"Invalid type for converting to ext::optional<_Tx> from v8"};
    v8::HandleScope javascript_scope{isolate};

    return v8pp::from_v8<ext::string_view>(isolate, v8_value);
}


inline auto v8pp::convert<const char8_t*>::to_v8(v8::Isolate* isolate, from_type string) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    return javascript_scope.Escape(v8pp::to_v8(isolate, ext::string_view{string}));
}


#endif //SBROWSER2_SRC_JAVASCRIPT_INTEROP_MANUAL_PRIMITIVE_CONVERSIONS_CONVERT_STRING_HPP
