#ifndef SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_REALMS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_REALMS_HPP

#include "ext/concepts.hpp"
#include "ext/keywords.hpp"
#include "javascript/environment/environment_settings.hpp"
#include "javascript/environment/global_slots.hpp"

#include <v8-context.h>
#include <v8-isolate.h>
#include <v8-maybe.h>
#include <v8-object.h>
#include <v8-persistent-handle.h>
#include <v8pp/convert.hpp>

namespace js::env {struct env;}
namespace js::env
{
    template <typename T> auto get_slot(const env& e, int slot) -> T;
    template <typename T> auto set_slot(const env& e, int slot, T&& value) -> void;
    auto del_slot(const env& e, int slot) -> void; // TODO : return deleted?
}


struct js::env::env
{
    template <ext::callable F>
    env(v8::Isolate* isolate, F&& context)
    {
        m_agent = isolate;
        m_realm = std::mem_fn(context)(isolate);
        m_global = m_realm->Global();
        m_settings = v8pp::to_v8(m_agent, get_settings());
    };

public:
    struct
    {
        _EXT_NODISCARD auto agent() const -> v8::Isolate*;
        _EXT_NODISCARD auto realm() const -> v8::Local<v8::Context>;
        _EXT_NODISCARD auto global() const -> v8::Local<v8::Object>;
        _EXT_NODISCARD auto settings() const -> v8::Local<v8::Object>;
    } js;


    struct
    {
        template <typename T>
        _EXT_NODISCARD auto global() const -> T;
        _EXT_NODISCARD auto settings() const -> settings_t*;
    } cpp;

public:
    static auto current() -> env;
    static auto implied() -> env;
    static auto incumbent() -> env;

    template <typename T> static auto entry(T&& cpp_object) -> env;
    template <typename T> static auto relevant(T&& cpp_object) -> env;
    template <typename T> static auto surrounding(T&& cpp_object) -> env;
    template <typename T> static auto associated(T&& cpp_object) -> env;
    template <typename T> static auto creation(T&& cpp_object) -> env;
    
    static auto from_global_object(v8::Local<v8::Value> js_object) -> env;

private:
    _EXT_NODISCARD auto get_settings() const -> settings_t*
    {return get_slot<settings_t*>(*this, js::global_slots::settings);}

    v8::Isolate* m_agent = nullptr;
    v8::Local<v8::Context> m_realm;
    v8::Local<v8::Object> m_global;
    v8::Local<v8::Object> m_settings;
};


template <typename T>
inline auto js::env::get_slot(const js::env::env& e, int slot) -> T
{
    return v8pp::from_v8<T>(e.js.agent(), e.js.global()->GetInternalField(slot));
}


template <typename T>
inline auto js::env::set_slot(const js::env::env& e, int slot, T&& value) -> void
{
    e.js.global()->SetInternalField(slot, v8pp::to_v8(e.js.agent(), std::forward<T>(value)));
}


inline auto js::env::del_slot(const js::env::env& e, int slot) -> void
{
    e.js.global()->GetInternalField(slot).Clear();
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


#endif //SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_REALMS_HPP
