#include "navigator_badge.hpp"


auto badging::mixins::navigator_badge::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<navigator_badge>{isolate}
        .inherit<dom_object>()
        .function("setAppBadge", &navigator_badge::set_app_badge)
        .function("clearAppBadge", &navigator_badge::clear_app_badge)
        .auto_wrap_objects();

    return std::move(conversion);
}
