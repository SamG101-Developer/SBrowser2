#ifndef SBROWSER2_CONVERT_DATETIME_HPP
#define SBROWSER2_CONVERT_DATETIME_HPP

#include "ext/boolean.hpp"
#include "ext/date.hpp"
#include <v8-primitive.h>
#include <v8pp/convert.hpp>


template <>
struct v8pp::convert<ext::datetime>
{
    using from_type = ext::datetime;
    using to_type = v8::Local<v8::Date>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean;
    static auto from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type;
};


inline auto v8pp::convert<ext::datetime>::is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
{
    return not v8_value.IsEmpty() && v8_value->IsBoolean();
}


inline auto v8pp::convert<ext::datetime>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    if (!is_valid(isolate, v8_value))
        throw std::invalid_argument{"Invalid type for converting to ext::datetime from v8"};

    v8::HandleScope javascript_scope{isolate};

    // Create the ext::datetime object from the time since epoch
    auto cpp_value = std::bit_cast<time_t>(v8_value.As<v8::Date>()->ValueOf());
    return ext::datetime{cpp_value};
}


inline auto v8pp::convert<ext::datetime>::to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // Create the v8::Date object from the time_since_epoch
    auto v8_value = v8::Date::New(isolate->GetCurrentContext(), std::bit_cast<double>(cpp_value.timestamp())).ToLocalChecked();
    return javascript_scope.Escape(v8_value);
}


#endif //SBROWSER2_CONVERT_DATETIME_HPP
