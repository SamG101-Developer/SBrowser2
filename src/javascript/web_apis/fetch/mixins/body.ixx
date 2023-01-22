module;
#include "ext/macros.hpp"
#include <v8-forward.h>


export module apis.fetch.mixins.body;
import apis.dom_object;

import apis.file_api.types;
import apis.streams.types;
import apis.xhr.types;

import ext.js;


DEFINE_PUBLIC_CLASS(fetch::mixins, body)
        : public virtual dom_object
{
public constructors:
    body();
    MAKE_PIMPL(body);
    MAKE_V8_AVAILABLE(MIXIN);

public js_methods:
    auto array_buffer() -> ext::promise<v8::Local<v8::ArrayBuffer>>;
    auto blob() -> ext::promise<file_api::blob>;
    auto form_data() -> ext::promise<xhr::form_data>;
    auto json() -> ext::promise<ext::any>;
    auto text() -> ext::promise<ext::string>;

private js_properties:
    DEFINE_GETTER(body, streams::readable_stream*);
    DEFINE_GETTER(body_used, ext::boolean);
};
