#include "2.hpp"

#include "javascript/interop/error_macros.hpp"
#include <cassert>

#include <v8-callbacks.h>
#include <v8-exception.h>
#include <v8-isolate.h>
#include <v8-local-handle.h>
#include <v8-primitive.h>
#include <v8-proxy.h>
#include <v8-value.h>


auto js::ecma::IsArray(
        v8::Local<v8::Value> value) -> ext::boolean
{
    JS_BLOCK_ENTER
        return_if (!value->IsObject()) false;
        return_if (value->IsArray()) true;
        if (auto proxy = value.As<v8::Proxy>(); value->IsProxy())
        {
            auto* isolate = v8::Isolate::GetCurrent();
            if (proxy->GetHandler()->IsNull())
                isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8Literal(isolate, "")));
            return IsArray(proxy->GetTarget());
        }
        return false;
    JS_BLOCK_EXIT
}


auto js::ecma::IsCallable(
        v8::Local<v8::Value> value) -> ext::boolean
{
    JS_BLOCK_ENTER
        if (!value->IsObject()) return false;
        return value.As<v8::Object>()->IsCallable();
    JS_BLOCK_EXIT
}


auto js::ecma::IsConstructor(
        v8::Local<v8::Value> value) -> ext::boolean
{
    JS_BLOCK_ENTER
        if (!value->IsObject()) return false;
        return value.As<v8::Object>()->IsConstructor();
    JS_BLOCK_EXIT
}


auto js::ecma::IsExtensible(
        v8::Local<v8::Object> value) -> ext::boolean
{
    JS_BLOCK_ENTER
        if (!value.IsEmpty()) return false;
        return value.As<v8::Object>()->(); // TODO
    JS_BLOCK_EXIT
}


auto js::ecma::IsIntegralNumber(
        v8::Local<v8::Value> value) -> ext::boolean
{
    JS_BLOCK_ENTER
        if (!value->IsNumber()) return false;
        auto number = value.As<v8::Number>();

        // TODO : NaN, +infinity, -infinity check
        // TODO : Floor test to differentiate integer against decimal
        return true;
    JS_BLOCK_EXIT
}


auto js::ecma::IsPropertyKey(
        v8::Local<v8::Value> value) -> ext::boolean
{
    JS_BLOCK_ENTER
        return value->IsString() || value->IsSymbol();
    JS_BLOCK_EXIT
}


auto js::ecma::IsRegExp(
        v8::Local<v8::Value> value) -> ext::boolean
{
    JS_BLOCK_ENTER
        if (!value->IsObject()) return false;

        auto* isolate = v8::Isolate::GetCurrent();
        auto matcher = value.As<v8::Object>()->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8Literal(isolate, "@@match")).ToLocalChecked();
        if (!matcher->IsUndefined())
            return matcher->ToBoolean(isolate)->Value();
        // TODO : [[RegExpMatcher]] slot check
        return false;
    JS_BLOCK_EXIT
}


auto js::ecma::IsStringWellFormedUnicode(
        v8::Local<v8::String> value) -> ext::boolean
{
    JS_BLOCK_ENTER
        auto length = value->Length();
        auto k = 0;
        while (k != length)
        {
            // TODO : GetCodePoint(...)
            // TODO [[IsUnpairedSurrogate]]
            // TODO [[CodeUnitCount]]
        }
        return true;
    JS_BLOCK_EXIT
}


auto js::ecma::SameValue(
        v8::Local<v8::Value> value_x, v8::Local<v8::Value> value_y) -> ext::boolean
{
    JS_BLOCK_ENTER
        auto* isolate = v8::Isolate::GetCurrent();
        if (value_x->TypeOf(isolate) != value_y->TypeOf(isolate)) return false;
        if (value_x->IsNumber()) return value_x.As<v8::Number>()->SameValue(value_y.As<v8::Number>());
        if (value_x->IsBigInt()) return value_x.As<v8::BigInt>()->SameValue(value_y.As<v8::BigInt>());
        return SameValueNonNumeric(value_x, value_y);
    JS_BLOCK_EXIT
}


auto js::ecma::SameValueZero(
        v8::Local<v8::Value> value_x, v8::Local<v8::Value> value_y) -> ext::boolean
{
    JS_BLOCK_ENTER
        auto* isolate = v8::Isolate::GetCurrent();
        if (value_x->TypeOf(isolate) != value_y->TypeOf(isolate)) return false;
        if (value_x->IsNumber()) return value_x.As<v8::Number>()->SameValueZero(value_y.As<v8::Number>());
        if (value_x->IsBigInt()) return value_x.As<v8::BigInt>()->SameValueZero(value_y.As<v8::BigInt>());
        return SameValueNonNumeric(value_x, value_y);
    JS_BLOCK_EXIT
}


auto js::ecma::SameValueNonNumeric(
        v8::Local<v8::Value> value_x, v8::Local<v8::Value> value_y) -> ext::boolean
{
    JS_BLOCK_ENTER
        auto* isolate = v8::Isolate::GetCurrent();
        assert(value_x->TypeOf(isolate) != value_y->TypeOf(isolate));

        if (value_x->IsUndefined() || value_x->IsNull()) return true;
        if (value_x->IsString()) return value_x.As<v8::String>()->StringEquals(value_y.As<v8::String>());
        if (value_x->IsBoolean()) return value_x.As<v8::Boolean>()->StrictEquals(value_y.As<v8::Boolean>());
        if (value_x->IsSymbol()) return value_x.As<v8::Symbol>()->StrictEquals(value_y.As<v8::Symbol>());
        return value_x.As<v8::Object>()->Equals(isolate->GetCurrentContext(), value_y.As<v8::Object>()).FromJust();
    JS_BLOCK_EXIT
}

