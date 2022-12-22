module;
#include <v8-local-handle.h>
#include <v8-object.h>
#include <v8pp/convert.hpp>


module js.env.realms;
import js.env.slots;
import ext.core;


template <ext::callable F>
js::env::env(v8::Isolate* isolate, F&& context)
{
    m_agent = isolate;
    m_realm = std::mem_fn(context)(isolate);
    m_global = m_realm->Global();
    m_settings = v8pp::to_v8(m_agent, get_settings(m_global));
};


auto js::env::get_settings(v8::Local<v8::Object> object) -> settings_t*
{
    return get_slot(js::env::env::from_global_object(object), js::env::slots::settings);
}


auto js::env::env::current() -> env
{
    return env{v8::Isolate::GetCurrent(), &v8::Isolate::GetCurrentContext};
}

auto js::env::env::implied() -> env
{
    return current(); /* TODO : For now */
}

auto js::env::env::incumbent() -> env
{
    return env{v8::Isolate::GetCurrent(), &v8::Isolate::GetIncumbentContext};
}

template <typename T>
auto js::env::env::entry(T&& cpp_object) -> env
{
    return env{v8pp::to_v8(v8::Isolate::GetCurrent(), std::forward<T>(cpp_object))->GetIsolate(), &v8::Isolate::GetEnteredOrMicrotaskContext};
}

template <typename T>
auto js::env::env::relevant(T&& cpp_object) -> env
{
    return env{v8pp::to_v8(v8::Isolate::GetCurrent(), std::forward<T>(cpp_object))->GetIsolate(), &v8::Isolate::GetCurrentContext};
}

