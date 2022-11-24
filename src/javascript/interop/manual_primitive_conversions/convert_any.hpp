#pragma once
#ifndef SBROWSER2_CONVERT_ANY_HPP
#define SBROWSER2_CONVERT_ANY_HPP

#include "ext/array_buffer.hpp"
#include "ext/any.hpp"
#include "ext/optional.hpp"
#include "ext/functional.hpp"
#include "ext/span.hpp"
#include "ext/symbol.hpp"

#include <v8-array-buffer.h>
#include <v8-container.h>
#include <v8-context.h>
#include <v8-forward.h>
#include <v8-internal.h>
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
struct v8pp::convert<ext::u8string>
{
    using from_type = ext::u8string;
    using from_view_type = ext::u8string_view;
    using to_type = v8::Local<v8::String>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && v8_value->IsString();}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type
    {return reinterpret_cast<const char8_t*>(*v8::String::Utf8Value(isolate, v8_value));}

    static auto to_v8(v8::Isolate* isolate, from_view_type cpp_value) -> to_type
    {return v8::String::NewFromUtf8(isolate, cpp_value.data(), v8::NewStringType::kNormal, cpp_value.length());}
};


template <>
struct v8pp::convert<ext::u16string>
{
    using from_type = ext::u16string;
    using from_view_type = ext::u16string_view;
    using to_type = v8::Local<v8::String>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && v8_value->IsString();}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type
    {return reinterpret_cast<const char16_t*>(*v8::String::Utf8Value(isolate, v8_value));}

    static auto to_v8(v8::Isolate* isolate, from_view_type cpp_value) -> to_type
    {return v8::String::NewFromTwoByte(isolate, cpp_value.data(), v8::NewStringType::kNormal, cpp_value.length());}
};


template <typename ...Ts>
struct v8pp::convert<ext::function<Ts...>>
{
    using from_type = ext::function<Ts...>;
    using from_view_type = ext::function_view<Ts...>;
    using to_type = v8::Local<v8::Function>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && v8_value->IsFunction();}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;

    static auto to_v8(v8::Isolate* isolate, from_view_type cpp_value) -> to_type
    {return v8::Function::New(isolate->GetCurrentContext(), cpp_value).ToLocalChecked();}
};


template <typename T>
struct v8pp::convert<ext::optional<T>>
{
    using from_type = ext::optional<T>;
    using to_type = v8::Local<v8::Value>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && (v8_value->IsValue() || v8_value->IsNull() || v8_value->IsUndefined());}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type
    {return ext::optional<T>{v8_value->IsNull() || v8_value->IsUndefined() ? ext::nullopt : v8pp::from_v8<T>(isolate, v8_value)};}

    static auto to_v8(v8::Isolate* isolate, from_type&& cpp_value) -> to_type
    {return cpp_value.has_value() ? v8::Null(isolate) : v8pp::to_v8(isolate, std::move(*cpp_value));}
};


template <typename T>
struct v8pp::convert<ext::vector<T>>
{
    using from_type = ext::vector<T>;
    using from_view_type = ext::vector_span<T>;
    using to_type = v8::Local<v8::Array>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && v8_value->IsArray();}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type
    {
        auto cpp_value = ext::vector<T>{v8_value->Length()};
        for (auto i = 0; i < v8_value->Length(); ++i)
            cpp_value.template emplace_back(v8pp::from_v8<T>(isolate, v8_value->Get(isolate->GetCurrentContext(), i).ToLocalChecked()));
        return cpp_value;
    }

    static auto to_v8(v8::Isolate* isolate, from_view_type cpp_value) -> to_type
    {
        auto v8_value = v8::Array::New(isolate, cpp_value.size());
        for (auto i = 0; i < cpp_value.size(); ++i)
            v8_value->Set(isolate->GetCurrentContext(), v8pp::to_v8(isolate, cpp_value.at(i)));
        return v8_value;
    };
};


template <typename T>
struct v8pp::convert<ext::set<T>>
{
    using from_type = ext::set<T>;
    using from_view_type = ext::set_span<T>;
    using to_type = v8::Local<v8::Set>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && v8_value->IsSet();}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type
    {
        auto cpp_value = ext::set<T>(v8_value->Size());
        for (auto i = 0; i < v8_value->Size(); ++i)
            cpp_value.template emplace(v8pp::from_v8<T>(isolate, v8_value->Get(isolate->GetCurrentContext(), i).ToLocalChecked()));
        return cpp_value;
    }

    static auto to_v8(v8::Isolate* isolate, from_view_type cpp_value) -> to_type
    {
        auto v8_value = v8::Set::New(isolate);
        for (auto i = 0; i < cpp_value.size(); ++i)
            v8_value->Add(isolate->GetCurrentContext(), v8pp::to_v8(isolate, cpp_value.at(i)));
        return v8_value;
    }
};


template <typename K, typename V>
struct v8pp::convert<ext::map<K, V>>
{
    using from_type = ext::map<K, V>;
    using from_view_type = ext::map_span<K, V>;
    using to_type = v8::Local<v8::Map>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && v8_value->IsMap();}

    static auto from_v8(v8::Isolate* isolate, to_type v8_vals) -> from_type
    {
        auto cpp_value = ext::map<K, V>{v8_vals->Size()};
        auto v8_keys = cpp_value->GetPropertyNames(isolate->GetCurrentContext()).ToLocalChecked();
        for (auto i = 0; i < cpp_value.size(); ++i)
        {
            auto k = v8pp::from_v8<K>(isolate, v8_keys->Get(isolate->GetCurrentContext(), i));
            auto v = v8pp::from_v8<V>(isolate, v8_vals->Get(isolate->GetCurrentContext(), k));
            cpp_value.template emplace(std::move(k), std::move(v));
        }

        return cpp_value;

    }

    static auto to_v8(v8::Isolate* isolate, from_view_type cpp_value) -> to_type
    {
        auto v8_value = v8::Map::New(isolate);
        for (auto& [k, v]: cpp_value)
            v8_value->Set(isolate->GetCurrentContext(), v8pp::to_v8(isolate, k), v8pp::to_v8(isolate, v));
        return v8_value;
    }
};


template <typename T>
struct v8pp::convert<ext::promise<T>>
{
    using from_type = ext::promise<T>;
    using to_type = v8::Local<v8::Promise>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && v8_value->IsPromise();}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type;
};


template <typename ...Ts>
struct v8pp::convert<ext::variant<Ts...>>
{
    using from_type = ext::variant<Ts...>;
    using to_type = v8::Local<v8::Value>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty();}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, from_type&& cpp_value) -> to_type;
};


template <>
struct v8pp::convert<ext::array_buffer>
{
    using from_type = ext::array_buffer;
    using to_type = v8::Local<v8::ArrayBuffer>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && v8_value->IsArrayBuffer();}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type;
};


template <>
struct v8pp::convert<ext::data_view>
{
    using from_type = ext::data_view;
    using to_type = v8::Local<v8::ArrayBuffer>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && v8_value->IsDataView();}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type;
};


template <ext::type_is<ext::int8_array, ext::int16_array, ext::int32_array, ext::uint8_array, ext::uint16_array,
        ext::uint32_array, ext::uint8_clamped_array, ext::bigint64_array, ext::biguint64_array, ext::float32_array,
        ext::float64_array> T>
struct v8pp::convert<T>
{
    using from_type = T;
    using to_type = v8::Local<v8::ArrayBuffer>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() /* && TODO */;}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type;
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
