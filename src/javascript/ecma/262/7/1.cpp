#include "1.hpp"

#include <limits>

#include "ext/initializer_list.hpp"

#include <v8-exception.h>
#include <v8-internal.h>
#include <v8-isolate.h>
#include <v8-forward.h>
#include <v8-local-handle.h>
#include <v8-object.h>
#include <v8-primitive.h>

#include <v8pp/convert.hpp>

#include "javascript/ecma/262/7/3.hpp"
#include "javascript/environment/realms.hpp"


auto js::ecma::ToPrimitive(v8::Local<v8::Value> input, ConversionHint hint) -> v8::Local<v8::Value>
{
    ISOLATE_AND_CONTEXT

    if (input->IsObject())
    {
        if (auto exotic = GetMethod(input, v8::Symbol::GetToPrimitive(isolate)); !exotic->IsUndefined())
        {
            auto result = Call(exotic, input, hint == kNone ? kDefault : hint);
            return_if (!result->IsObject()) result;
            isolate->ThrowException(v8::Exception::TypeError(v8pp::to_v8(isolate, "Primitive cannot be an Object")));
        }

        return OrdinaryToPrimitive(input, hint == kNone ? kNumber : hint);
    }

    return input;
}


auto js::ecma::OrdinaryToPrimitive(v8::Local<v8::Object> O, ConversionHint hint) -> v8::Local<v8::Value>
{
    ISOLATE_AND_CONTEXT

    using namespace ext::literals;
    auto method_names = hint == kString
            ? ext::initializer_list("toString", "valueOf")
            : ext::initializer_list("valueOf", "toString");

    for (auto&& name: method_names)
    {
        auto method = Get(O, v8pp::to_v8(isolate, name));
        if (IsCallable(method))
        {
            auto result = Call(method, O);
            return_if (!result->IsObject()) result;
        }
    }

    isolate->ThrowException(v8::Exception::TypeError(v8pp::to_v8(isolate, "Must be convertible to a non-Object primitive type")));
}


auto js::ecma::ToBoolean(
        v8::Local<v8::Value> argument)
        -> v8::Local<v8::Boolean>
{
    ISOLATE_AND_CONTEXT;

    return_if (argument->IsNullOrUndefined()) v8::Boolean::New(isolate, false);
    return_if (argument->IsBoolean()) argument.As<v8::Boolean>();
    return_if (argument->IsNumber()) v8::Boolean::New(isolate, argument.As<v8::Number>()->Value() != 0.0);
    return_if (argument->IsString()) v8::Boolean::New(isolate, argument.As<v8::String>()->Length() == 0);
    return_if (argument->IsSymbol()) v8::Boolean::New(isolate, true);
    return_if (argument->IsBigInt()) v8::Boolean::New(isolate, argument.As<v8::BigInt>()->Int64Value() == 0);
    return_if (argument->IsObject()) v8::Boolean::New(isolate, true);
}


auto js::ecma::ToNumeric(
        v8::Local<v8::Value> value)
        -> v8::Local<v8::Primitive>
{
    auto primitive = ToPrimitive(value, kNumber);
    return primitive->IsBigInt()
            ? primitive.As<v8::Number>()
            : ToNumber(primitive);
}


auto js::ecma::ToNumber(
        v8::Local<v8::Value> value)
        -> v8::Local<v8::Number>
{
    ISOLATE_AND_CONTEXT;

    return_if (value->IsUndefined()) v8::Number::New(isolate, ext::number<double>::nan());
    return_if (value->IsNull()) v8::Number::New(isolate, ext::number<double>::inf());
    return_if (value->IsNumber()) value.As<v8::Number>();
    return_if (value->IsString()) StringToNumber(value.As<v8::String>());
    return_if (value->IsObject()) ToNumber(ToPrimitive(value, kNumber));

    if (value->IsSymbol())
        isolate->ThrowException(v8::Exception::TypeError(v8pp::to_v8(isolate, "Cannot convert v8::Symbol -> v8::Number")));

    if (value->IsBigInt())
        isolate->ThrowException(v8::Exception::TypeError(v8pp::to_v8(isolate, "Cannot convert v8::BigInt -> v8::Number")));
}


template <typename T>
auto js::ecma::ToString(T&& argument) -> v8::Local<v8::String>
{
    auto isolate = v8::Isolate::GetCurrent();

    if constexpr (ext::type_is<v8::Local<v8::String>, T>)
        return std::forward<T>(argument);

    if constexpr (ext::type_is<v8::Local<v8::Symbol>, T>)
        isolate->ThrowException(v8pp::to_v8(isolate, "Cannot convert Symbol to String"));

    if (argument->IsUndefined())
        return v8pp::to_v8(isolate, "undefined");

    if (argument->IsNull())
        return v8pp::to_v8(isolate, "null");

    if (argument->IsNumber() || argument->IsBigInt())
        return argument.ToString(isolate->GetCurrentContext());

    auto primitive = ToPrimitive<v8::String>(std::forward<T>(argument));
    ASSERT(argument->IsObject());
    ASSERT(!primitive->IsObject());
    return ToString(primitive);
}

