#ifndef SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_REALMS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_REALMS_HPP


#include "ext/keywords.ixx"
#include "javascript/environment/environment_settings.hpp"
#include "javascript/environment/global_slots.hpp"

#include <v8-context.h>
#include <v8-isolate.h>
#include <v8-maybe.h>
#include <v8-object.h>
#include <v8-persistent-handle.h>
#include <v8pp/convert.hpp>

#define ISOLATE_AND_CONTEXT                             \
    decltype(auto) isolate = v8::Isolate::GetCurrent(); \
    auto context = isolate->GetCurrentContext();


namespace js::env
{
    struct env;
    _EXT_NODISCARD auto get_settings(v8::Local<v8::Object> object) -> settings_t*;
}


struct js::env::env
{
    template <ext::callable F>
    env(v8::Isolate* isolate, F&& context)
    {
        m_agent = isolate;
        m_realm = std::mem_fn(context)(isolate);
        m_global = m_realm->Global();
        m_settings = v8pp::to_v8(m_agent, get_settings(m_global));
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
    v8::Isolate* m_agent = nullptr;
    v8::Local<v8::Context> m_realm;
    v8::Local<v8::Object> m_global;
    v8::Local<v8::Object> m_settings;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_REALMS_HPP
