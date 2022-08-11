#include "keyboard_event.hpp"


ui_events::keyboard_event::keyboard_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : mixins::modifier_event{std::move(event_type), std::move(event_init)}
        , key{event_init.try_emplace("key", "").first->second.to<ext::string>()}
        , code{event_init.try_emplace("code", "").first->second.to<ext::string>()}
        , location{event_init.try_emplace("location", 0).first->second.to<ext::number<ulong>>()}
        , repeat{event_init.try_emplace("repeat", ext::boolean::FALSE_()).first->second.to<ext::boolean>()}
        , is_composing{event_init.try_emplace("isComposing", ext::boolean::FALSE_()).first->second.to<ext::boolean>()}
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
