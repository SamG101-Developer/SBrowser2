#ifndef SBROWSER2_SRC_JAVASCRIPT_ECMA_SPEC_262_7_ABSRACT_OPERATIONS_7_3_OPERATIONS_ON_OBJECTS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_ECMA_SPEC_262_7_ABSRACT_OPERATIONS_7_3_OPERATIONS_ON_OBJECTS_HPP

#include "2.hpp"

#include <v8-exception.h>
#include <v8-internal.h>
#include <v8-isolate.h>
#include <v8-object.h>
#include <v8pp/convert.hpp>


namespace js::ecma
{
    /* 7.3.03 */ auto GetV(v8::Local<v8::Value> V, v8::Local<v8::Symbol> P) -> v8::Local<v8::Value>;
    /* 7.3.11 */ auto GetMethod(v8::Local<v8::Value> V, v8::Local<v8::Symbol> P) -> v8::Local<v8::Value>;
}


auto js::ecma::GetV(v8::Local<v8::Value> V, v8::Local<v8::Symbol> P) -> v8::Local<v8::Value>
{
    auto context = v8::Isolate::GetCurrent()->GetCurrentContext();
    auto O = V->ToObject(context).ToLocalChecked();
    return O->Get(context, V).ToLocalChecked();
}


auto js::ecma::GetMethod(v8::Local<v8::Value> V, v8::Local<v8::Symbol> P) -> v8::Local<v8::Value>
{
    auto isolate = v8::Isolate::GetCurrent();
    auto func = GetV(V, P);

    if (func->IsUndefined() || func->IsNull())
        return v8::Undefined(isolate);

    if (!IsCallable(func))
        isolate->ThrowException(v8::Exception::TypeError(v8pp::to_v8(isolate, "Function must be callable")));

    return func;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_ECMA_SPEC_262_7_ABSRACT_OPERATIONS_7_3_OPERATIONS_ON_OBJECTS_HPP
