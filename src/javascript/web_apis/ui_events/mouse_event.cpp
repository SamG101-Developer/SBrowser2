#include "mouse_event.hpp"

#include "ui_events/mixins/modifier_event.hpp"


ui_events::mouse_event::mouse_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : mixins::modifier_event(std::move(event_type), std::move(event_init))
        , screen_x{event_init.try_emplace("screenX", 0).first->second.to<ext::number<long>>()}
        , screen_y{event_init.try_emplace("screenY", 0).first->second.to<ext::number<long>>()}
        , client_x{event_init.try_emplace("clientX", 0).first->second.to<ext::number<long>>()}
        , client_y{event_init.try_emplace("clientY", 0).first->second.to<ext::number<long>>()}
        , button{event_init.try_emplace("buttons", 0).first->second.to<ext::number<short>>()}
        , buttons{event_init.try_emplace("button", 0).first->second.to<ext::number<ushort>>()}
{}


auto ui_events::mouse_event::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<mouse_event>{isolate}
            .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
            .inherit<mixins::modifier_event>()
            .var("screenX", &mouse_event::screen_x, true)
            .var("screenY", &mouse_event::screen_y, true)
            .var("clientX", &mouse_event::client_x, true)
            .var("clientY", &mouse_event::client_y, true)
            .var("button", &mouse_event::button, true)
            .var("buttons", &mouse_event::buttons, true)
            .auto_wrap_objects();
}
