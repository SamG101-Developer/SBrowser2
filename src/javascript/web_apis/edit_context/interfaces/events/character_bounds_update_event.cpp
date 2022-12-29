module;
#include "ext/macros/macros.hpp"
#include "javascript/macros/expose.hpp"
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.edit_context.character_bounds_update_event;
import apis.edit_context.character_bounds_update_event_private;

import apis.dom.event;

import ext.core;
import js.env.module_type;


edit_context::character_bounds_update_event::character_bounds_update_event(
        ext::string&& event_type,
        character_bounds_update_event_init_t&& event_init)
        : dom::event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL; ACCESS_PIMPL;

    d->range_start = event_init[u"rangeStart"].to<ulong>();
    d->range_end = event_init[u"rangeEnd"].to<ulong>();
}


auto edit_context::character_bounds_update_event::get_range_start() const -> ext::number<ulong>
{
    ACCESS_PIMPL;
    return d->range_start;
}


auto edit_context::character_bounds_update_event::get_range_end() const -> ext::number<ulong>
{
    ACCESS_PIMPL;
    return d->range_end;
}


auto edit_context::character_bounds_update_event::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::event>()
        .ctor<ext::string&&, character_bounds_update_event_init_t&&>()
        .property("rangeStart", &character_bounds_update_event::get_range_start)
        .property("rangeEnd", &character_bounds_update_event::get_range_end)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
