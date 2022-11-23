#include "navigator_badge.hpp"
#include "navigator_badge_private.hpp"


auto badging::mixins::navigator_badge::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .function("setAppBadge", &navigator_badge::set_app_badge)
        .function("clearAppBadge", &navigator_badge::clear_app_badge)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
