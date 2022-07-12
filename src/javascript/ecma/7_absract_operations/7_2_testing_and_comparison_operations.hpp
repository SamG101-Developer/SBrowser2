#ifndef SBROWSER2_7_2_TESTING_AND_COMPARISON_OPERATIONS_HPP
#define SBROWSER2_7_2_TESTING_AND_COMPARISON_OPERATIONS_HPP

#include "ext/boolean.hpp"
#include "javascript/interop/annotations.hpp"

#include <cassert>

#include <v8-callbacks.h>
#include <v8-exception.h>
#include <v8-isolate.h>
#include <v8-local-handle.h>
#include <v8-primitive.h>
#include <v8-proxy.h>
#include <v8-value.h>

namespace javascript::ecma
{
    /* 7.2.02 */ auto IsArray(v8::Local<v8::Value> value) -> ext::boolean;
    /* 7.2.03 */ auto IsCallable(v8::Local<v8::Value> value) -> ext::boolean;
    /* 7.2.04 */ auto IsConstructor(v8::Local<v8::Value> value) -> ext::boolean;
    /* 7.2.05 */ auto IsExtensible(v8::Local<v8::Object> value) -> ext::boolean;
    /* 7.2.06 */ auto IsIntegralNumber(v8::Local<v8::Value> value) -> ext::boolean;
    /* 7.2.07 */ auto IsPropertyKey(v8::Local<v8::Value> value) -> ext::boolean;
    /* 7.2.08 */ auto IsRegExp(v8::Local<v8::Value> value) -> ext::boolean;
    /* 7.2.09 */ auto IsStringWellFormedUnicode(v8::Local<v8::String> value) -> ext::boolean;
    /* 7.2.10 */ auto SameValue(v8::Local<v8::Value> value_x, v8::Local<v8::Value> value_y) -> ext::boolean;
    /* 7.2.11 */ auto SameValueZero(v8::Local<v8::Value> value_x, v8::Local<v8::Value> value_y) -> ext::boolean;
    /* 7.2.12 */ auto SameValueNonNumeric(v8::Local<v8::Value> value_x, v8::Local<v8::Value> value_y) -> ext::boolean;
    /* 7.2.13 */ auto IsLessThan(v8::Local<v8::Value> value_x, v8::Local<v8::Value> value_y, ext::boolean_view left_first) -> ext::boolean;
    /* 7.2.14 */ auto IsLooselyEqual(v8::Local<v8::Value> value) -> ext::boolean;
    /* 7.2.15 */ auto IsStrictlyEqual(v8::Local<v8::Value> value) -> ext::boolean;
}


auto javascript::ecma::IsArray(
        v8::Local<v8::Value> value) -> ext::boolean
{
    JS_BLOCK_ENTER
        if (!value->IsObject()) return false;
        if (value->IsArray()) return true;
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


auto javascript::ecma::IsCallable(
        v8::Local<v8::Value> value) -> ext::boolean
{
    JS_BLOCK_ENTER
        if (!value->IsObject()) return false;
        return value.As<v8::Object>()->IsCallable();
    JS_BLOCK_EXIT
}


auto javascript::ecma::IsConstructor(
        v8::Local<v8::Value> value) -> ext::boolean
{
    JS_BLOCK_ENTER
        if (!value->IsObject()) return false;
        return value.As<v8::Object>()->IsConstructor();
    JS_BLOCK_EXIT
}


auto javascript::ecma::IsExtensible(
        v8::Local<v8::Object> value) -> ext::boolean
{
    JS_BLOCK_ENTER
        if (!value.IsEmpty()) return false;
        return value.As<v8::Object>()->(); // TODO
    JS_BLOCK_EXIT
}


auto javascript::ecma::IsIntegralNumber(
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


auto javascript::ecma::IsPropertyKey(
        v8::Local<v8::Value> value) -> ext::boolean
{
    JS_BLOCK_ENTER
        return value->IsString() || value->IsSymbol();
    JS_BLOCK_EXIT
}


auto javascript::ecma::IsRegExp(
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


auto javascript::ecma::IsStringWellFormedUnicode(
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


auto javascript::ecma::SameValue(
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


auto javascript::ecma::SameValueZero(
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


auto javascript::ecma::SameValueNonNumeric(
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


#endif //SBROWSER2_7_2_TESTING_AND_COMPARISON_OPERATIONS_HPP
