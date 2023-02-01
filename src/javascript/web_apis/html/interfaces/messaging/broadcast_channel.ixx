module;
#include "ext/macros.hpp"


export module apis.html.broadcast_channel;
import apis.dom.event_target;

import ext.any;
import ext.enums;
import ext.string;
import ext.tuple;

import js.env.module_type;


DEFINE_PUBLIC_CLASS(html, broadcast_channel)
        : public dom::event_target
{
public constructors:
    broadcast_channel(ext::string&& name);
    MAKE_PIMPL(broadcast_channel);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);

private js_methods:
    auto post_message(ext::any&& message) -> void;
    auto close() -> void;

private js_properties:
    DEFINE_GETTER(name, ext::string_view);
};
