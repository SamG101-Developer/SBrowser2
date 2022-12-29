module;
#include "ext/macros/language_shorthand.hpp"
#include "ext/macros/macros.hpp"
#include "javascript/macros/expose.hpp"

module apis.event_timing.performance_event_timing;
import apis.event_timing.performance_event_timing_private;

import apis.dom.node;
import apis.dom.node_private;
import apis.dom.shadow_root;
import apis.dom.shadow_root_private;

import apis.hr_time.types;
import apis.performance_timeline.performance_entry;

import ext.core;

import js.env.module_type;


event_timing::performance_event_timing::performance_event_timing()
{
    INIT_PIMPL;
}


auto event_timing::performance_event_timing::get_processing_start() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL;
    return d->processing_start;
}


auto event_timing::performance_event_timing::get_processing_end() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL;
    return d->processing_end;
}


auto event_timing::performance_event_timing::get_cancelable() const -> ext::boolean
{
    ACCESS_PIMPL;
    return d->event->d_func()->cancelable;
}


auto event_timing::performance_event_timing::get_target() const -> dom::node*
{
    ACCESS_PIMPL;
    decltype(auto) node = dynamic_cast<dom::node*>(d->event_target);
    return node
            && !node->d_func()->is_connected()
            && !dom_cast<dom::shadow_root*>(node->d_func()->shadow_including_root())
            ? node : nullptr;
}


auto event_timing::performance_event_timing::get_interaction_id() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL;
    return_if (decltype(auto) pointer_event = dom_cast<pointer_events::pointer_event*>(d->event)) pointer_event->d_func()->pointer_id;
    return_if (decltype(auto) key_event = dom_cast<ui_events::keyboard_event*>(d->event)) key_event->d_func()->code;
    return 0;
}


auto event_timing::performance_event_timing::get_name() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->event->d_func()->type;
}


auto event_timing::performance_event_timing::get_entry_type() const -> ext::string_view
{
    ACCESS_PIMPL;
    return u"event"; // TODO : u"first-input"?
}


auto event_timing::performance_event_timing::get_start_time() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL;
    return d->event->d_func()->time_stamp;
}


auto event_timing::performance_event_timing::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<performance_timeline::performance_entry>()
        .property("processingStart", &performance_event_timing::get_processing_start)
        .property("processingEnd", &performance_event_timing::get_processing_end)
        .property("cancelable", &performance_event_timing::get_cancelable)
        .property("target", &performance_event_timing::get_target)
        .property("interactionId", &performance_event_timing::get_interaction_id)
        .function("toJSON", &performance_event_timing::operator ext::string)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
