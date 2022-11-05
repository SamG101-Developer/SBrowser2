#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_WINDOW_PROXY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_WINDOW_PROXY_HPP

#include "dom_object.hpp"
#include <v8-object.h>
namespace dom::nodes {class window_proxy;}
namespace dom::nodes {class window_proxy_private;}

namespace dom::nodes {class window;}


class dom::nodes::window_proxy
        : public virtual dom_object
        , public v8::Object
{
public constructors:
    window_proxy();
    MAKE_PIMPL(window_proxy);
    MAKE_V8_AVAILABLE;

public js_properties:
    auto GetPrototype() -> v8::Local<v8::Value>;
    auto SetPrototype(v8::Local<v8::Context> context, v8::Local<v8::Value> prototype) -> v8::Maybe<bool>;
    auto IsExtensible() -> bool;
    auto PreventExtensions() -> bool;
    auto GetOwnPropertyDescriptor(v8::Local<v8::Context> context, v8::Local<v8::Name> key) -> v8::MaybeLocal<v8::Value>;
    auto DefineOwnProperty(v8::Local<v8::Context> context, v8::Local<v8::Name> key, v8::Local<v8::Value> value, v8::PropertyAttribute attributes = v8::None) -> v8::Maybe<bool>;
    auto Get(v8::Local<v8::Context> context, v8::Local<v8::Value> key, v8::Local<v8::Function> receiver) -> v8::MaybeLocal<v8::Value>;
    auto Set(v8::Local<v8::Context> context, v8::Local<v8::Value> key, v8::Local<v8::Value> value, v8::Local<v8::Function> receiver) -> v8::Maybe<bool>;
    auto Delete(v8::Local<v8::Context> context, v8::Local<v8::Value> key) -> v8::Maybe<bool>;
    auto GetOwnPropertyNames(v8::Local<v8::Context> context) -> v8::MaybeLocal<v8::Array>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_WINDOW_PROXY_HPP
