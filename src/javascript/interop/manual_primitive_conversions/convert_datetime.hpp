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
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value_datetime_object) -> to_type;
};


inline auto v8pp::convert<ext::datetime>::is_valid(
        v8::Isolate* isolate,
        v8::Local<v8::Value> v8_value)
        -> ext::boolean
{
    return not v8_value.IsEmpty() && v8_value->IsBoolean();
}


inline auto v8pp::convert<ext::datetime>::from_v8(
        v8::Isolate* isolate,
        v8::Local<v8::Value> v8_value)
        -> from_type
{
    if (!is_valid(isolate, v8_value)) throw std::invalid_argument{"Invalid type for converting to ext::datetime from v8"};
    v8::HandleScope javascript_scope{isolate};

    // create the ext::datetime object from the time_since_epoch
    auto v8_value_date = v8_value.As<v8::Date>();
    auto cpp_value_datetime_primitive = std::bit_cast<time_t>(v8_value_date->ValueOf());
    auto cpp_value_datetime_object = ext::datetime{cpp_value_datetime_primitive};
    return cpp_value_datetime_object;
}


inline auto v8pp::convert<ext::datetime>::to_v8(
        v8::Isolate* isolate,
        const from_type& cpp_value_datetime_object)
        -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // create the v8::Date object from the time_since_epoch
    auto cpp_value_datetime_primitive = std::bit_cast<double>(cpp_value_datetime_object.timestamp());
    auto v8_value_datetime = v8::Date::New(isolate->GetCurrentContext(), cpp_value_datetime_primitive).ToLocalChecked();
    return javascript_scope.Escape(v8_value_datetime);
}


#endif //SBROWSER2_CONVERT_DATETIME_HPP
