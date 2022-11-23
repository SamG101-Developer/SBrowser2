#include "text_update_event.hpp"
#include "ext/property.hpp"


edit_context::events::text_update_event::text_update_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event(std::move(event_type), std::move(event_init))
{
    INIT_PIMPL(text_update_event);

    ACCESS_PIMPL(text_update_event);
    d->update_range_start = event_init[u"updateRangeStart"].to<decltype(d->update_range_start)>();
    d->update_range_end = event_init[u"updateRangeEnd"].to<decltype(d->update_range_end)>();
    d->selection_start = event_init[u"selectionStart"].to<decltype(d->selection_start)>();
    d->selection_end = event_init[u"selectionEnd"].to<decltype(d->selection_end)>();
    d->composition_start = event_init[u"compositionStart"].to<decltype(d->composition_start)>();
    d->composition_end = event_init[u"compositionEnd"].to<decltype(d->composition_end)>();
    d->text = event_init[u"text"].to<decltype(d->text)>();
}


auto edit_context::events::text_update_event::get_update_range_start() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL(const text_update_event);
    return d->update_range_start;
}


auto edit_context::events::text_update_event::get_update_range_end() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL(const text_update_event);
    return d->update_range_end;
}


auto edit_context::events::text_update_event::get_selection_start() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL(const text_update_event);
    return d->selection_start;
}


auto edit_context::events::text_update_event::get_selection_end() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL(const text_update_event);
    return d->selection_end;
}


auto edit_context::events::text_update_event::get_composition_start() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL(const text_update_event);
    return d->composition_start;
}


auto edit_context::events::text_update_event::get_composition_end() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL(const text_update_event);
    return d->composition_end;
}


auto edit_context::events::text_update_event::get_text() const -> ext::string_view
{
    ACCESS_PIMPL(const text_update_event);
    return d->text;
}


auto edit_context::events::text_update_event::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::events::event>()
        .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
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
