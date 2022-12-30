module;
#include "ext/macros.hpp"


module apis.edit_context.text_format_update_event;
import apis.dom.event;

import ext.core;
import js.env.module_type;


edit_context::text_format_update_event::text_format_update_event(
        ext::string&& event_type,
        text_format_update_event_init_t&& event_init)
        : dom::event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL; ACCESS_PIMPL;

    d->text_formats = event_init[u"textFormats"].to<decltype(d->text_formats)>();
}


auto edit_context::text_format_update_event::get_text_formats() -> ranges::any_helpful_view<text_format*>
{
    ACCESS_PIMPL;
    return d->text_formats | ranges::views::transform(ext::underlying);
}


auto edit_context::text_format_update_event::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::event>()
        .ctor<ext::string&&, text_format_update_event_init_t&&>()
        .function("textFormats", &text_format_update_event::get_text_formats)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
