#include "touch_event.hpp"
#include "ui_events/mixins/modifier_event.hpp"


touch_events::touch_event::touch_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : ui_events::mixins::modifier_event(std::move(event_type), std::move(event_init))
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(event_init, touches)
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(event_init, target_touches)
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(event_init, changed_touches)
{}


auto touch_events::touch_event::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<touch_event>{isolate}
            .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
            .inherit<ui_events::mixins::modifier_event>()
            .var("touches", &touch_event::touches, true)
            .var("targetTouches", &touch_event::target_touches, true)
            .var("changedTouches", &touch_event::changed_touches, true)
            .auto_wrap_objects();
}
