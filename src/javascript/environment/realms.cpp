#include "realms.hpp"

#include "javascript/environment/global_slots.hpp"


auto js::env::get_settings(v8::Local<v8::Object> object) -> settings_t*
{
    return get_slot<settings_t*>(js::env::env::from_global_object(object), js::global_slots::settings);
}


auto js::env::env::current() -> env
{return env{v8::Isolate::GetCurrent(), &v8::Isolate::GetCurrentContext};}

auto js::env::env::implied() -> env
{return current(); /* TODO : For now */}

auto js::env::env::incumbent() -> env
{return env{v8::Isolate::GetCurrent(), &v8::Isolate::GetIncumbentContext};}

template <typename T>
auto js::env::env::entry(T&& cpp_object) -> env
{return env{v8pp::to_v8(v8::Isolate::GetCurrent(), std::forward<T>(cpp_object))->GetIsolate(), &v8::Isolate::GetEnteredOrMicrotaskContext};}

template <typename T>
auto js::env::env::relevant(T&& cpp_object) -> env
{return env{v8pp::to_v8(v8::Isolate::GetCurrent(), std::forward<T>(cpp_object))->GetIsolate(), &v8::Isolate::GetCurrentContext};}

