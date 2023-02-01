module;
#include "ext/macros.hpp"


export module apis.dom.window_proxy;
import apis.dom_object;


DEFINE_PUBLIC_CLASS(dom, window_proxy) final
        : public virtual dom_object
{
public constructors:
    window_proxy();
    MAKE_PIMPL(window_proxy);
    MAKE_V8_AVAILABLE(WINDOW); // TODO : check

private js_properties:
    auto get_prototype() -> v8::Local<v8::Value>;
    auto set_prototype(v8::Local<v8::Context> context, v8::Local<v8::Value> prototype) -> v8::Maybe<bool>;
    auto is_extensible() -> bool;
    auto prevent_extensions() -> bool;
    auto get_own_property_descriptor(v8::Local<v8::Context> context, v8::Local<v8::Name> key) -> v8::MaybeLocal<v8::Value>;
    auto define_own_property(v8::Local<v8::Context> context, v8::Local<v8::Name> key, v8::Local<v8::Value> value, v8::PropertyAttribute attributes = v8::None) -> v8::Maybe<bool>;
    auto get(v8::Local<v8::Context> context, v8::Local<v8::Value> key, v8::Local<v8::Function> receiver) -> v8::MaybeLocal<v8::Value>;
    auto set(v8::Local<v8::Context> context, v8::Local<v8::Value> key, v8::Local<v8::Value> value, v8::Local<v8::Function> receiver) -> v8::Maybe<bool>;
    auto delete_(v8::Local<v8::Context> context, v8::Local<v8::Value> key) -> v8::Maybe<bool>;
    auto get_own_property_names(v8::Local<v8::Context> context) -> v8::MaybeLocal<v8::Array>;
};
