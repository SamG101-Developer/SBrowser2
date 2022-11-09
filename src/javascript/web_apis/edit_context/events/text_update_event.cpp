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


auto edit_context::events::text_update_event::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<text_update_event>{isolate}
        .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
        .var("updateRangeStart", &text_update_event::update_range_start, true)
        .var("updateRangeEnd", &text_update_event::update_range_end, true)
        .var("selectionStart", &text_update_event::selection_start, true)
        .var("selectionEnd", &text_update_event::selection_end, true)
        .var("compositionStart", &text_update_event::composition_start, true)
        .var("compositionEnd", &text_update_event::composition_end, true)
        .var("text", &text_update_event::text, true)
        .auto_wrap_objects();

    return std::move(conversion);
}
