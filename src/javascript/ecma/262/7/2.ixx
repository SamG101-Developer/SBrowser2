module;
#include <v8-forward.h>


export module js.ecma._262._7._2;
import ext.core;

export namespace js::ecma
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
    /* 7.2.13 */ auto IsLessThan(v8::Local<v8::Value> value_x, v8::Local<v8::Value> value_y, ext::boolean left_first) -> ext::boolean;
    /* 7.2.14 */ auto IsLooselyEqual(v8::Local<v8::Value> value) -> ext::boolean;
    /* 7.2.15 */ auto IsStrictlyEqual(v8::Local<v8::Value> value) -> ext::boolean;
}
