#include "focus_event.hpp"


ui_events::focus_event::focus_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : ui_event(std::move(event_type), std::move(event_init))
{}


auto ui_events::focus_event::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<focus_event>{isolate}
            .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
            .inherit<ui_event>()
            .auto_wrap_objects();
}
