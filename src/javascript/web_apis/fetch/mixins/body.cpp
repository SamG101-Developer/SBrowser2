module;
#include "ext/macros.hpp"


module apis.fetch.mixins.body;

import js.env.module_type;
import js.env.realms;
import ext.core;


auto fetch::mixins::body::get_body() const -> streams::readable_stream*
{
    ACCESS_PIMPL;
    return d->body() ? d->body()->stream.get() : nullptr;
}


auto fetch::mixins::body::get_body_used() const -> ext::boolean
{
    ACCESS_PIMPL;
    return d->body() && streams::detail::is_disturbed(d->body()->stream.get());
}


auto fetch::mixins::body::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .function("arrayBuffer", &body::array_buffer)
        .function("blob", &body::blob)
        .function("formData", &body::form_data)
        .function("json", &body::json)
        .function("text", &body::text)
        .property("body", &body::get_body)
        .property("bodyUsed", &body::get_body_used)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
