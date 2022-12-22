module;
#include "ext/macros/extended_attributes.hpp"
#include <functional>
#include <v8-forward.h>
#include <v8pp/convert.hpp>


export module js.env.realms;
import ext.core;


namespace js::env
{
    struct settings_t;
    export struct env;
    export _EXT_NODISCARD auto get_settings(v8::Local<v8::Object> object) -> settings_t*;
}


struct js::env::env
{
    template <ext::callable F>
    env(v8::Isolate* isolate, F&& context);

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
