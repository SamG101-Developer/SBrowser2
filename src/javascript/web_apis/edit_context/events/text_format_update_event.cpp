#include "text_format_update_event.hpp"
#include "text_format_update_event_private.hpp"

#include "ext/functional.ixx"


edit_context::events::text_format_update_event::text_format_update_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
        , text_format{std::move(event_init)}
{
    INIT_PIMPL(text_format_update_event);
    ACCESS_PIMPL(text_format_update_event);

    d->text_formats = event_init[u"textFormats"].to<decltype(d->text_formats)>();
}


auto edit_context::events::text_format_update_event::get_text_formats() -> ranges::any_helpful_view<text_format*>
{
    ACCESS_PIMPL(text_format_update_event);
    return d->text_formats | ranges::views::transform(ext::underlying);
}


auto edit_context::events::text_format_update_event::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::events::event>()
        .inherit<text_format>()
        .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
