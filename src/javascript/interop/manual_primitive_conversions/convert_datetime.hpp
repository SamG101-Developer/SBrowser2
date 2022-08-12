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

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {return not v8_value.IsEmpty() && v8_value->IsDate();}
    static auto from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type;
};


#endif //SBROWSER2_CONVERT_DATETIME_HPP
