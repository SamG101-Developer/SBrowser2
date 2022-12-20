module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


module apis.dom.custom_event;
import apis.dom.custom_event_private;
import ext.core;
import js.env.module_type;


dom::custom_event::custom_event(
        ext::string&& event_type,
        custom_event_init_t&& event_init)
        : event(std::move(event_type), std::move(event_init))
{
    INIT_PIMPL;

    ACCESS_PIMPL;
    d->detail = 0;
}


auto dom::custom_event::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<event>()
        .ctor<ext::string&&, custom_event_init_t&&>()
        .property("detail", &custom_event::get_detail)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
