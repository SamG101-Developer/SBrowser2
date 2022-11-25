#pragma once
#include "v8-exception.h"
#include "v8-local-handle.h"
#ifndef SBROWSER2_CONVERT_ANY_HPP
#define SBROWSER2_CONVERT_ANY_HPP

#include "ext/array_buffer.hpp"
#include "ext/any.hpp"
#include "ext/optional.hpp"
#include "ext/functional.hpp"
#include "ext/span.hpp"
#include "ext/symbol.hpp"

#include "javascript/ecma/262/7/1.hpp"
#include "javascript/ecma/262/7/2.hpp"
#include "javascript/ecma/262/7/3.hpp"
#include "javascript/ecma/262/7/4.hpp"

#include <magic_enum.hpp>
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


/* [3.2.1] - any */
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


/* [3.2.2] - undefined */
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


/* [3.2.3] - boolean */
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


/* [3.2.4] - integer types */
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


/* [3.2.5] - restricted float */
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


/* [3.2.6] - unrestricted float */
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


/* [3.2.7] - restricted double */
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


/* [3.2.8] - unrestricted double */
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


/* [3.2.9] - bigint */
template <>
struct v8pp::convert<ext::number<ulonglong>>
{
    using from_type = ext::number<ulonglong>;
    using to_type = v8::Local<v8::Number>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && (v8_value->IsBigInt() || v8_value->IsBigIntObject());}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, from_type cpp_value) -> to_type;
};


/* [3.2.10] [3.2.12] - domstring usvstring */
template <>
struct v8pp::convert<ext::u16string>
{
    using from_type = ext::u16string;
    using from_view_type = ext::u16string_view;
    using to_type = v8::Local<v8::String>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && (v8_value->IsString() || v8_value->IsStringObject());}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type
    {return reinterpret_cast<const char16_t*>(*v8::String::Utf8Value(isolate, v8_value));}

    static auto to_v8(v8::Isolate* isolate, from_view_type cpp_value) -> to_type
    {return v8::String::NewFromTwoByte(isolate, cpp_value.data(), v8::NewStringType::kNormal, cpp_value.length());}
};


/* [3.2.11] - bytestring */
template <>
struct v8pp::convert<ext::u8string>
{
    using from_type = ext::u8string;
    using from_view_type = ext::u8string_view;
    using to_type = v8::Local<v8::String>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && v8_value->IsString() || v8_value->IsStringObject();}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type
    {return reinterpret_cast<const char8_t*>(*v8::String::Utf8Value(isolate, v8_value));}

    static auto to_v8(v8::Isolate* isolate, from_view_type cpp_value) -> to_type
    {return v8::String::NewFromUtf8(isolate, cpp_value.data(), v8::NewStringType::kNormal, cpp_value.length());}
};


/* [3.2.14] - symbol */
template <>
struct v8pp::convert<ext::symbol>
{
    using from_type = ext::symbol;
    using to_type = v8::Local<v8::Symbol>;

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type;
};


/* [3.2.15] [3.2.16] [3.2.19] - function */
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


/* [3.2.17] [3.2.22] - dictionary record */
template <typename K, typename V>
struct v8pp::convert<ext::map<K, V>>
{
    using from_type = ext::map<K, V>;
    using from_view_type = ext::map_span<K, V>;
    using to_type = v8::Local<v8::Object>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && (v8_value->IsUndefined() || v8_value->IsNull() || v8_value->IsObject());}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value, ext::optional<K>&& default_value = ext::nullopt) -> from_type
    {
        auto v8_scope = v8::HandleScope{isolate};
        auto context = isolate->GetCurrentContext();

        auto v8_keys = v8_value->GetPropertyNames(context).ToLocalChecked(); // TODO : Lexigraphical Order
        auto cpp_value = ext::map<K, V>{v8_keys->Length()};

        for (auto i = 0; i < v8_keys->Length(); ++i)
        {
            auto v8_key = v8_keys->Get(context, i).ToLocalChecked();
            auto v8_val = v8_value->Get(context, v8_key).ToLocalChecked();
            auto cpp_key = v8pp::from_v8<K>(isolate, v8_key);

            if (!v8_val->IsUndefined())
                cpp_value.template emplace(cpp_key, v8pp::from_v8<V>(isolate, v8_val));

            else if (v8_val->IsUndefined() && default_value.has_value())
                cpp_value.template emplace(cpp_key, *default_value);
        }

        return cpp_value;
    }

    static auto to_v8(v8::Isolate* isolate, from_view_type cpp_value) -> to_type
    {
        auto v8_scope = v8::EscapableHandleScope{isolate};
        auto context = isolate->GetCurrentContext();

        auto v8_value = v8::Object::New(isolate);

        for (auto&& [cpp_key, cpp_val]: cpp_value)
        {
            auto v8_key = v8pp::to_v8(isolate, cpp_key);
            auto v8_val = v8pp::to_v8(isolate, cpp_val);
            v8_value->CreateDataProperty(context, v8_key, v8_val);
        }

        return v8_scope.Escape(v8_value);
    }
};


/* [3.2.18] - enumerations */
template <ext::type_is_enum T>
struct v8pp::convert<T>
{
    using from_type = T;
    using to_type = v8::Local<v8::String>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && (v8_value->IsString() || v8_value->IsStringObject());}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type
    {
        auto v8_scope = v8::HandleScope{isolate};

        auto cpp_value = magic_enum::enum_cast<T>(v8pp::from_v8<ext::string>(isolate, v8_value));
        if (!cpp_value.has_value())
            isolate->ThrowException(v8::Exception::TypeError(v8pp::to_v8(isolate, "Invalid enum value (" + magic_enum::enum_names<T>() + ")")));

        return magic_enum::enum_cast<T>(std::move(*cpp_value));
    };

    static auto to_v8(v8::Isolate* isolate, from_type cpp_value) -> to_type
    {
        auto v8_scope = v8::EscapableHandleScope{isolate};
        auto v8_value = v8pp::to_v8(isolate, magic_enum::enum_name(cpp_value));
        return v8_scope.template Escape(v8_value);
    };
};


/* [3.2.20] - nullable (optional) */
template <typename T>
struct v8pp::convert<ext::optional<T>>
{
    using from_type = ext::optional<T>;
    using to_type = v8::Local<v8::Value>;

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
    {return !v8_value.IsEmpty() && (v8_value->IsValue() || v8_value->IsNull() || v8_value->IsUndefined());}

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type
    {
        auto v8_scope = v8::HandleScope{isolate};
        if (v8_value->IsNull() || v8_value->IsUndefined())
            return ext::nullopt;
        return v8pp::from_v8<T>(isolate, v8_value);
    }

    static auto to_v8(v8::Isolate* isolate, from_type&& cpp_value) -> to_type
    {
        auto v8_scope = v8::EscapableHandleScope{isolate};
        if (!cpp_value.has_value())
            return v8_scope.template Escape(v8::Null(isolate));
        return v8_scope.template Escape(v8pp::to_v8(isolate, std::move(*cpp_value)));
    }
};


/* [3.2.21] - sequence (vector) */
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
        auto v8_scope = v8::HandleScope{isolate};
        auto context = isolate->GetCurrentContext();
        auto method = js::ecma::GetMethod(v8_value, v8::Symbol::GetIterator(isolate));

        if (method->IsUndefined())
            isolate->ThrowException(v8::Exception::TypeError(v8pp::to_v8(isolate, "Iterator cannot be undefined")));

        auto cpp_value = from_type{};
        auto iterator = js::ecma::GetIterator(v8_value, js::ecma::IteratorHint::kSync, method);
        while (true)
        {
            auto next = js::ecma:IteratorStep(iterator);
            if (!next) return cpp_value;
            auto next_item = js::ecma::IteratorValue(next);
            cpp_value.template emplace(v8pp::from_v8<T>(next_item));
        }
    }

    static auto to_v8(v8::Isolate* isolate, from_view_type cpp_value) -> to_type
    {
        auto v8_scope = v8::EscapableHandleScope{isolate};
        auto v8_value = v8::Array::New(isolate, cpp_value.size());
        for (auto i = 0; i < cpp_value.size(); ++i)
        {
            auto v8_val = v8pp::to_v8(isolate, cpp_value[i]);
            auto v8_property = js::ecma::ToString(i);
            js::ecma::CreateDataProperty(v8_value, v8_property, v8_val);
        }
        return v8_scope.Escape(v8_value);
    };
};


template <typename T>
struct v8pp::convert<ext::set<T>> // TODO
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


/* [3.2.23] - promise */
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

    static auto from_v8(v8::Isolate* isolate, to_type v8_value) -> from_type
    {
        auto v8_scope = v8::HandleScope{isolate};
        auto cpp_value = ext::visit([isolate]<typename T>(v8::Local<v8::Value> v8_subvalue) {return v8pp::from_v8<T>(isolate, v8_subvalue);}, from_type{});
        return cpp_value;
    }

    static auto to_v8(v8::Isolate* isolate, from_type&& cpp_value) -> to_type
    {
        auto v8_scope = v8::EscapableHandleScope{isolate};
        auto v8_value = ext::visit([isolate]<typename T>(T&& cpp_subvalue) {return v8pp::to_v8(isolate, std::forward<T>(cpp_subvalue));}, std::move(cpp_value));
        return v8_scope.template Escape(v8_value);
    }
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
    return_if (v8_value->IsBigInt() || v8_value->IsBigIntObject()) v8pp::from_v8<ext::number<ulonglong>>(isolate, v8_value);
    return_if (v8_value->IsString() || v8_value->IsStringObject()) v8pp::from_v8<ext::string>(isolate, v8_value);
    return_if (v8_value->IsSymbol() || v8_value->IsSymbolObject()) v8pp::from_v8<ext::symbol>(isolate, v8_value);
}


#endif //SBROWSER2_CONVERT_ANY_HPP
