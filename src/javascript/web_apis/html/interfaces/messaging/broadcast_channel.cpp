module;
#include "ext/macros/macros.hpp"
#include "javascript/macros/expose.hpp"
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.html.broadcast_channel;
import apis.html.broadcast_channel_private;

import apis.dom.event_target;

import ext.string;
import ext.tuple;
import js.env.module_type;


html::broadcast_channel::broadcast_channel(ext::string&& name)
{
    INIT_PIMPL; ACCESS_PIMPL;

    d->channel_name = std::move(name);
    d->closed_flag = false;
}


auto html::broadcast_channel::get_name() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->channel_name;
}


auto html::broadcast_channel::close() -> void
{
    ACCESS_PIMPL;
    d->closed_flag = true;
}


auto html::broadcast_channel::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::event_target>()
        .ctor<ext::string>()
        .function("postMessage", &broadcast_channel::post_message)
        .function("close", &broadcast_channel::close)
        .property("name", &broadcast_channel::get_name)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
