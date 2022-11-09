#pragma once
#include "v8-forward.h"
#ifndef SBROWSER2_CONVERT_ANY_HPP
#define SBROWSER2_CONVERT_ANY_HPP

#include "ext/any.hpp"
#include "ext/optional.hpp"
#include "ext/symbol.hpp"

#include "web_idl/detail/type_mapping_internals.hpp"

#include <v8-container.h>
#include <v8-context.h>
#include <v8-isolate.h>
#include <v8-object.h>
#include <v8-primitive.h>
#include <v8-typed-array.h>
#include <v8-value.h>
#include <v8pp/convert.hpp>


template <>
struct v8pp::convert<ext::any>
{
    using from_type = ext::any;
    using to_type = v8::Local<v8::Value>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty();}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, from_type cpp_value) -> to_type;
};


template <>
struct v8pp::convert<void>
{
    using from_type = void;
    using to_type = v8::Local<v8::Primitive>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && v8_value->IsUndefined();}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate) -> to_type;
};


template <>
struct v8pp::convert<ext::boolean>
{
    using from_type = ext::boolean;
    using to_type = v8::Local<v8::Boolean>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && (v8_value->IsBoolean() || v8_value->IsBooleanObject());}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type
    {return v8_value->ToBoolean(isolate)->Value();}

    static auto to_v8(v8::Isolate* isolate, from_type cpp_value) -> to_type
    {return v8::Boolean::New(isolate, cpp_value);}
};


template <std::integral T, bool unrestricted> requires unrestricted
struct v8pp::convert<ext::number<T, unrestricted>>
{
    using from_type = ext::number<int8_t>;
    using to_type = v8::Local<v8::Number>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && (v8_value->IsNumber() || v8_value->IsNumberObject());}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type
    {return web_idl::detail::convert_to_int<sizeof(T), std::is_signed_v<T>>(v8_value->ToInteger(isolate->GetCurrentContext()).ToLocalChecked());}

    static auto to_v8(v8::Isolate* isolate, from_type cpp_value) -> to_type
    {return v8::Integer::New(isolate, cpp_value);}
};


template <>
struct v8pp::convert<ext::number<float, true>>
{
    using from_type = ext::number<float, true>;
    using to_type = v8::Local<v8::Number>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && (v8_value->IsNumber() || v8_value->IsNumberObject());}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, from_type cpp_value) -> to_type;
};


template <>
struct v8pp::convert<ext::number<float, false>>
{
    using from_type = ext::number<float, false>;
    using to_type = v8::Local<v8::Number>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && (v8_value->IsNumber() || v8_value->IsNumberObject());}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, from_type cpp_value) -> to_type;
};


template <>
struct v8pp::convert<ext::number<double, true>>
{
    using from_type = ext::number<double, true>;
    using to_type = v8::Local<v8::Number>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && (v8_value->IsNumber() || v8_value->IsNumberObject());}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, from_type cpp_value) -> to_type;
};


template <>
struct v8pp::convert<ext::number<double, false>>
{
    using from_type = ext::number<double, false>;
    using to_type = v8::Local<v8::Number>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && (v8_value->IsNumber() || v8_value->IsNumberObject());}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, from_type cpp_value) -> to_type;
};


template <>
struct v8pp::convert<ext::number<bigint>>
{
    using from_type = ext::number<bigint>;
    using to_type = v8::Local<v8::Number>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && (v8_value->IsBigInt() || v8_value->IsBigIntObject());}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, from_type cpp_value) -> to_type;
};


template <>
struct v8pp::convert<ext::string>
{
    using from_type = ext::string;
    using to_type = v8::Local<v8::String>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && v8_value->IsString();}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, from_type& cpp_value) -> to_type;
};


auto v8pp::convert<ext::any>::from_v8(v8::Isolate* isolate, v8pp::convert<ext::any>::to_type v8_value) -> from_type
{
    return_if (v8_value->IsUndefined()) v8pp::convert<void>::from_v8(isolate, v8_value);
    return_if (v8_value->IsNull()) nullptr;
    return_if (v8_value->IsBoolean() || v8_value->IsBooleanObject()) v8pp::from_v8<ext::boolean>(isolate, v8_value);
    return_if (v8_value->IsNumber() || v8_value->IsNumberObject()) v8pp::from_v8<ext::number<double>>(isolate, v8_value);
    return_if (v8_value->IsBigInt() || v8_value->IsBigIntObject()) v8pp::from_v8<ext::number<bigint>>(isolate, v8_value);
    return_if (v8_value->IsString() || v8_value->IsStringObject()) v8pp::from_v8<ext::string>(isolate, v8_value);
    return_if (v8_value->IsSymbol() || v8_value->IsSymbolObject()) v8pp::from_v8<ext::symbol>(isolate, v8_value);
}


#endif //SBROWSER2_CONVERT_ANY_HPP
