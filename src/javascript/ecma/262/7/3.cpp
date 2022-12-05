module;
#include "ext/macros/language_shorthand.hpp"
#include "javascript/macros/expose.hpp"

#include <v8-context.h>
#include <v8-exception.h>
#include <v8-internal.h>
#include <v8-isolate.h>
#include <v8-object.h>
#include <v8pp/convert.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/transform.hpp>


module js.ecma._262._7._3;
import ext.tuple;


auto js::ecma::Get(v8::Local<v8::Object> O, v8::Local<v8::Value> P) -> v8::Local<v8::Value>
{
    ISOLATE_AND_CONTEXT;

    return O->Get(context, P).ToLocalChecked();
}


auto js::ecma::GetV(v8::Local<v8::Value> V, v8::Local<v8::Symbol> P) -> v8::Local<v8::Value>
{
    ISOLATE_AND_CONTEXT;

    auto O = V->ToObject(context).ToLocalChecked();
    return O->Get(context, V).ToLocalChecked();
}


auto js::ecma::CreateDataProperty(v8::Local<v8::Object> O, v8::Local<v8::String> P, v8::Local<v8::Value> V)
{
    ISOLATE_AND_CONTEXT;

    auto new_descriptor = v8::PropertyDescriptor{V, true};
    new_descriptor.set_enumerable(true);
    new_descriptor.set_configurable(true);
    return O->DefineProperty(context, P, new_descriptor); // TODO : DefineOwnProperty?
}


auto js::ecma::GetMethod(v8::Local<v8::Value> V, v8::Local<v8::Symbol> P) -> v8::Local<v8::Value>
{
    ISOLATE_AND_CONTEXT;

    auto func = GetV(V, P);
    return_if (func->IsUndefined() || func->IsNull()) v8::Undefined(isolate);

    if (!IsCallable(func))
        isolate->ThrowException(v8::Exception::TypeError(v8pp::to_v8(isolate, "Function must be callable")));

    return func;
}


template <typename ...Args>
auto js::ecma::Call(v8::Local<v8::Value> F, v8::Local<v8::Value> V, Args&& ...arguments) -> v8::Local<v8::Value>
{
    ISOLATE_AND_CONTEXT;

    if (!IsCallable(F))
        isolate->ThrowException(v8::Exception::TypeError(v8pp::to_v8(isolate, "Function must be callable")));

    auto tuple = ext::make_tuple(std::forward<Args>(arguments)...);
    auto cast_args = ranges::views::closed_iota(0, tuple.N)
            | ranges::views::transform([tuple = std::move(tuple)](auto i) {return ext::get<i>(tuple);})
            | ranges::views::transform([isolate]<typename T>(T&& cpp_value) {return v8pp::to_v8(isolate, std::forward<T>(cpp_value));});

    return F.As<v8::Function>()->Call(context, V, sizeof...(Args), cast_args.data());
}

