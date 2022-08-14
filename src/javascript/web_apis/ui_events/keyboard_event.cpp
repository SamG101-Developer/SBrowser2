#include "keyboard_event.hpp"


ui_events::keyboard_event::keyboard_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : mixins::modifier_event{std::move(event_type), std::move(event_init)}
        , SET_PROPERTY_FROM_OPTIONS(event_init, key, "")
        , SET_PROPERTY_FROM_OPTIONS(event_init, code, "")
        , SET_PROPERTY_FROM_OPTIONS(event_init, location, 0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, repeat, false)
        , SET_PROPERTY_FROM_OPTIONS(event_init, is_composing, false)
{}


auto ui_events::keyboard_event::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<keyboard_event>{isolate}
            .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
            .inherit<mixins::modifier_event>()
            .static_("DOM_KEY_LOCATION_STANDARD", keyboard_event::DOM_KEY_LOCATION_STANDARD, true)
            .static_("DOM_KEY_LOCATION_STANDARD", keyboard_event::DOM_KEY_LOCATION_STANDARD, true)
            .static_("DOM_KEY_LOCATION_STANDARD", keyboard_event::DOM_KEY_LOCATION_STANDARD, true)
            .static_("DOM_KEY_LOCATION_STANDARD", keyboard_event::DOM_KEY_LOCATION_STANDARD, true)
            .var("key", &keyboard_event::key, true)
            .var("code", &keyboard_event::code, true)
            .var("location", &keyboard_event::location, true)
            .var("repeat", &keyboard_event::repeat, true)
            .var("isComposing", &keyboard_event::is_composing, true)
            .auto_wrap_objects();
}
