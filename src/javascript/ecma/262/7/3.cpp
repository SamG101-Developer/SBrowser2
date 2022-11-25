#include "3.hpp"

#include <v8-exception.h>
#include <v8-internal.h>
#include <v8-isolate.h>
#include <v8-object.h>
#include <v8pp/convert.hpp>


auto js::ecma::Get(v8::Local<v8::Object> O, v8::Local<v8::Value> P) -> v8::Local<v8::Value>
{
    decltype(auto) isolate = v8::Isolate::GetCurrent();
    auto context = isolate->GetCurrentContext();
    return O->Get(context, P).ToLocalChecked();
}


auto js::ecma::GetV(v8::Local<v8::Value> V, v8::Local<v8::Symbol> P) -> v8::Local<v8::Value>
{
    auto context = v8::Isolate::GetCurrent()->GetCurrentContext();
    auto O = V->ToObject(context).ToLocalChecked();
    return O->Get(context, V).ToLocalChecked();
}


auto js::ecma::CreateDataProperty(v8::Local<v8::Object> O, v8::Local<v8::String> P, v8::Local<v8::Value> V)
{
    auto isolate = v8::Isolate::GetCurrent();
    auto context = isolate->GetCurrentContext();

    auto new_descriptor = v8::PropertyDescriptor{V, true};
    new_descriptor.set_enumerable(true);
    new_descriptor.set_configurable(true);
    return O->DefineProperty(context, P, new_descriptor); // TODO : DefineOwnProperty?
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

