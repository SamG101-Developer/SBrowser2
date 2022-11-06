#ifndef SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_REALMS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_REALMS_HPP

#include "ext/concepts.hpp"
#include "javascript/environment/environment_settings.hpp"

#include <v8-context.h>
#include <v8-isolate.h>
#include <v8-maybe.h>
#include <v8-object.h>
#include <v8-persistent-handle.h>
#include <v8pp/convert.hpp>

namespace js::env {struct env;}
namespace js::env
{
    auto private_property(const env& e, ext::string_view property) -> v8::Local<v8::Private>;
}


struct js::env::env
{
    template <ext::callable F>
    env(v8::Isolate* isolate, F&& context)
    {
        m_agent = isolate;
        m_realm = std::mem_fn(context)(isolate);
        m_global = m_realm->Global();
        m_settings = get_settings();
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
    auto static current() -> env;
    auto static implied() -> env;
    auto static incumbent() -> env;

    template <typename T> auto static entry(T&& cpp_object) -> env;
    template <typename T> auto static relevant(T&& cpp_object) -> env;
    template <typename T> auto static surrounding(T&& cpp_object) -> env;
    template <typename T> auto static associated(T&& cpp_object) -> env;
    template <typename T> auto static creation(T&& cpp_object) -> env;

private:
    _EXT_NODISCARD auto get_settings() const
    {return m_global->GetPrivate(m_realm, private_property(*this, u8"[[Settings]]")).ToLocalChecked().As<v8::Object>();}

    v8::Isolate* m_agent = nullptr;
    v8::Local<v8::Context> m_realm;
    v8::Local<v8::Object> m_global;
    v8::Local<v8::Object> m_settings;
};


inline auto js::env::private_property(const js::env::env& e, ext::string_view property) -> v8::Local<v8::Private>
{return v8::Private::New(e.js.agent(), v8pp::to_v8(e.js.agent(), property));}

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
