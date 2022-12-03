#include "1.hpp"

#include <limits>


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
        v8::Local<v8::Value> argument)
        -> v8::Local<v8::Primitive>
{
    ISOLATE_AND_CONTEXT;

    auto primitive = ToPrimitive(argument, kNumber);
    return primitive->IsBigInt()
            ? primitive.As<v8::BigInt>()->ToNumber(context).ToLocalChecked()
            : ToNumber(primitive);
}


auto js::ecma::ToNumber(
        v8::Local<v8::Value> argument)
        -> v8::Local<v8::Number>
{
    ISOLATE_AND_CONTEXT;

    return_if (argument->IsUndefined()) v8::Number::New(isolate, ext::number<double>::nan());
    return_if (argument->IsNull()) v8::Number::New(isolate, ext::number<double>::inf());
    return_if (argument->IsNumber()) argument.As<v8::Number>();
    return_if (argument->IsString()) StringToNumber(argument.As<v8::String>());
    return_if (argument->IsObject()) ToNumber(ToPrimitive(argument, kNumber));

    if (argument->IsSymbol())
        isolate->ThrowException(v8::Exception::TypeError(v8pp::to_v8(isolate, "Cannot convert v8::Symbol -> v8::Number")));

    if (argument->IsBigInt())
        isolate->ThrowException(v8::Exception::TypeError(v8pp::to_v8(isolate, "Cannot convert v8::BigInt -> v8::Number")));
}


auto js::ecma::ToString(v8::Local<v8::Value> argument) -> v8::Local<v8::String>
{
    ISOLATE_AND_CONTEXT;

    return_if (argument->IsUndefined()) v8pp::to_v8(isolate, "undefined");
    return_if (argument->IsNumber()) v8pp::to_v8(isolate, "null");
    return_if (argument->IsBoolean()) v8pp::to_v8(isolate, argument->BooleanValue(isolate) ? "true" : "false");
    return_if (argument->IsNumber()) argument.As<v8::Number>()->ToString(context).ToLocalChecked();
    return_if (argument->IsString()) argument.As<v8::String>();
    return_if (argument->IsBigInt()) argument.As<v8::BigInt>()->ToString(context).ToLocalChecked();
    return_if (argument->IsObject()) ToString(ToPrimitive(argument, kString));

    if (argument->IsSymbol())
        isolate->ThrowException(v8::Exception::TypeError(v8pp::to_v8(isolate, "Cannot convert v8::Symbol -> v8::String")));
}


auto js::ecma::ToObject(v8::Local<v8::Value> argument) -> v8::Local<v8::Object>
{
    ISOLATE_AND_CONTEXT;

    return_if (argument->IsBoolean()) v8::BooleanObject::New(isolate, argument->BooleanValue(isolate));
    return_if (argument->IsNumber()) v8::NumberObject::New(isolate, argument->NumberValue(context).ToChecked());
    return_if (argument->IsString()) v8::StringObject::New(isolate, argument.As<v8::String>());
    return_if (argument->IsSymbol()) v8::SymbolObject::New(isolate, argument.As<v8::Symbol>());
    return_if (argument->IsBigInt()) v8::BigIntObject::New(isolate, argument.As<v8::BigInt>()->Int64Value());
    return_if (argument->IsObject()) argument.As<v8::Object>();

    if (argument->IsUndefined())
        isolate->ThrowException(v8::Exception::TypeError(v8pp::to_v8(isolate, "Cannot convert v8::Undefined -> v8::Object")));

    if (argument->IsNull())
        isolate->ThrowException(v8::Exception::TypeError(v8pp::to_v8(isolate, "Cannot convert v8::Null -> v8::Object")));
}

