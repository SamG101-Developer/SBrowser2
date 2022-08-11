#include "composition_event.hpp"


ui_events::composition_event::composition_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : ui_event(std::move(event_type), std::move(event_init))
        , data(event_init.try_emplace("data", "").first->second.to<ext::string>())
{}


auto ui_events::composition_event::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<composition_event>{isolate}
            .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
            .inherit<ui_event>()
            .var("data", &composition_event::data, true)
            .auto_wrap_objects();
}
