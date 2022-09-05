#include "gamepad.hpp"

#include "ext/uuid.hpp"

#include "gamepad/detail/construction_internals.hpp"

#include "high_resolution_time/performance.hpp"


gamepad::gamepad::gamepad()
        : id{ext::to_string(ext::uuid_system_generator{}())}
        , index{detail::select_unused_gamepad_index(this)}
        , mapping{detail::select_mapping(this)}
        , s_connected{true}
        , s_timestamp{high_resolution_time::performance{}.now()}
        , s_axes{detail::initialize_axes(this)}
        , s_buttons{detail::initialize_buttons(this)}
{
    bind_get(connected);
    bind_get(timestamp);
    bind_get(axes);
    bind_get(buttons);
}


auto gamepad::gamepad::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<gamepad>{isolate}
        .ctor<>()
        .inherit<dom_object>()
        .var("id", &gamepad::id, true)
        .var("index", &gamepad::index, true)
        .var("connected", &gamepad::connected, true)
        .var("timestamp", &gamepad::timestamp, true)
        .var("mapping", &gamepad::mapping, true)
        .var("axes", &gamepad::axes, true)
        .var("buttons", &gamepad::buttons, true)
        .slot("Connected", &gamepad::s_connected)
        .slot("Timestamp", &gamepad::s_timestamp)
        .slot("Axes", &gamepad::s_axes)
        .slot("Buttons", &gamepad::s_buttons)
        .slot("Exposed", &gamepad::s_exposed)
        .slot("AxisMapping", &gamepad::s_axis_mapping)
        .slot("AxisMinimums", &gamepad::s_axis_minimums)
        .slot("AxisMaximums", &gamepad::s_axis_maximums)
        .slot("ButtonMapping", &gamepad::s_button_mapping)
        .slot("ButtonMinimums", &gamepad::s_button_minimums)
        .slot("ButtonMaximums", &gamepad::s_button_maximums)
        .auto_wrap_objects();
}
