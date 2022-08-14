#include "ui_event.hpp"

#include "dom/nodes/window.hpp"


ui_events::ui_event::ui_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event(std::move(event_type), std::move(event_init))
        , SET_PROPERTY_FROM_OPTIONS(event_init, view, nullptr)
        , SET_PROPERTY_FROM_OPTIONS(event_init, detail, 0)
{}


auto ui_events::ui_event::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<ui_event>{isolate}
            .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
            .inherit<dom::events::event>()
            .var("view", &ui_event::view, true)
            .var("detail", &ui_event::detail, true)
            .auto_wrap_objects();
}
