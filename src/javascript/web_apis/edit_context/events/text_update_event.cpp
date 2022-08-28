#include "text_update_event.hpp"
#include "ext/property.hpp"


edit_context::events::text_update_event::text_update_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event(std::move(event_type), std::move(event_init))
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(event_init, update_range_start)
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(event_init, update_range_end)
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(event_init, selection_start)
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(event_init, selection_end)
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(event_init, composition_start)
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(event_init, composition_end)
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(event_init, text)
{}


auto edit_context::events::text_update_event::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<text_update_event>{isolate}
        .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
        .var("updateRangeStart", &text_update_event::update_range_start, true)
        .var("updateRangeEnd", &text_update_event::update_range_end, true)
        .var("selectionStart", &text_update_event::selection_start, true)
        .var("selectionEnd", &text_update_event::selection_end, true)
        .var("compositionStart", &text_update_event::composition_start, true)
        .var("compositionEnd", &text_update_event::composition_end, true)
        .var("text", &text_update_event::text, true)
        .auto_wrap_objects();
}
