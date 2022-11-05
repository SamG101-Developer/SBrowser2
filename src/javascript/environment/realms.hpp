#ifndef SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_REALMS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_REALMS_HPP

#include "ext/concepts.hpp"

#include <v8-context.h>
#include <v8-isolate.h>
#include <v8-maybe.h>
#include <v8-object.h>
#include <v8-persistent-handle.h>
#include <v8pp/convert.hpp>

namespace js {struct env;}

struct js::env
{
    template <ext::callable F>
    env(v8::Isolate* isolate, F&& context)
    {
        agent = isolate;
        realm = std::mem_fn(context)(isolate);
        global = realm->Global();
        settings = get_settings();
    };

    auto get_settings() const
    {
        return global->Get(realm, v8pp::to_v8(agent, "[[Settings]]")).ToLocalChecked().As<v8::Object>();
    }

    v8::Isolate* agent = nullptr;
    v8::Local<v8::Context> realm;
    v8::Local<v8::Object> global;
    v8::Local<v8::Object> settings;

    auto static current() -> env;
    auto static implied() -> env;
    auto static incumbent() -> env;

    template <typename T> auto static entry(T&& cpp_object) -> env;
    template <typename T> auto static relevant(T&& cpp_object) -> env;
    template <typename T> auto static surrounding(T&& cpp_object) -> env;
    template <typename T> auto static associated(T&& cpp_object) -> env;
    template <typename T> auto static creation(T&& cpp_object) -> env;
};


namespace js
{
    template <typename U, typename T>
    auto get(v8::Local<v8::Context> context, v8::Local<v8::Object> object) -> U
    {return v8pp::from_v8<U>(context->GetIsolate(), object);}
}


auto js::env::current() -> env
{return env{v8::Isolate::GetCurrent(), &v8::Isolate::GetCurrentContext};}

auto js::env::implied() -> env
{return current(); /* TODO : For now */}

auto js::env::incumbent() -> env
{return env{v8::Isolate::GetCurrent(), &v8::Isolate::GetIncumbentContext};}

template <typename T>
auto js::env::entry(T&& cpp_object) -> env
{return env{v8pp::to_v8(v8::Isolate::GetCurrent(), std::forward<T>(cpp_object))->GetIsolate(), &v8::Isolate::GetEnteredOrMicrotaskContext};}

template <typename T>
auto js::env::relevant(T&& cpp_object) -> env
{return env{v8pp::to_v8(v8::Isolate::GetCurrent(), std::forward<T>(cpp_object))->GetIsolate(), &v8::Isolate::GetCurrentContext};}


#endif //SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_REALMS_HPP
