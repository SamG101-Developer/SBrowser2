module;
#include "ext/macros.hpp"


module apis.edit_context.text_update_event;
import apis.dom.event;

import ext.core;
import js.env.module_type;


edit_context::text_update_event::text_update_event(
        ext::string&& event_type,
        text_update_event_init_t&& event_init)
        : dom::event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL; ACCESS_PIMPL;
    
    d->update_range_start = event_init[u"updateRangeStart"].to<ulonglong>();
    d->update_range_end = event_init[u"updateRangeEnd"].to<ulonglong>();
    d->selection_start = event_init[u"selectionStart"].to<ulonglong>();
    d->selection_end = event_init[u"selectionEnd"].to<ulonglong>();
    d->composition_start = event_init[u"compositionStart"].to<ulonglong>();
    d->composition_end = event_init[u"compositionEnd"].to<ulonglong>();
    d->text = event_init[u"text"].to<ext::string>();
}


auto edit_context::text_update_event::get_update_range_start() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL;
    return d->update_range_start;
}


auto edit_context::text_update_event::get_update_range_end() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL;
    return d->update_range_end;
}


auto edit_context::text_update_event::get_selection_start() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL;
    return d->selection_start;
}


auto edit_context::text_update_event::get_selection_end() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL;
    return d->selection_end;
}


auto edit_context::text_update_event::get_composition_start() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL;
    return d->composition_start;
}


auto edit_context::text_update_event::get_composition_end() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL;
    return d->composition_end;
}


auto edit_context::text_update_event::get_text() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->text;
}


auto edit_context::text_update_event::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::event>()
        .ctor<ext::string&&, text_update_event_init_t&&>()
        .property("updateRangeStart", &text_update_event::get_update_range_start)
        .property("updateRangeEnd", &text_update_event::get_update_range_end)
        .property("selectionStart", &text_update_event::get_selection_start)
        .property("selectionEnd", &text_update_event::get_selection_end)
        .property("compositionStart", &text_update_event::get_composition_start)
        .property("compositionEnd", &text_update_event::get_composition_end)
        .property("text", &text_update_event::get_text)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
