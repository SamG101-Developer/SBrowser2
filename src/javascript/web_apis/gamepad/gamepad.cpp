#include "gamepad.hpp"

#include "ext/pimpl.hpp"
#include "ext/uuid.hpp"

#include "dom/nodes/window.hpp"
#include "hr_time/detail/time_internals.hpp"
#include "gamepad/detail/construction_internals.hpp"

#include "hr_time/performance.hpp"


gamepad::gamepad::gamepad()
        : index{detail::select_unused_gamepad_index(this)}
        , mapping{detail::select_mapping(this)}
{
    INIT_PIMPL(gamepad);
    ACCESS_PIMPL(gamepad);

    JS_REALM_GET_RELEVANT(this);

    d->id = ext::to_string(ext::uuid_system_generator{}());
    d->timestamp = hr_time::detail::current_hr_time(this_relevant_global_object);
    d->axes = detail::initialize_axes(this);
    d->buttons = detail::initialize_buttons(this);
}


auto gamepad::gamepad::get_id() const -> ext::string
{
    ACCESS_PIMPL(const gamepad);
    return d->id;
}


auto gamepad::gamepad::get_index() const -> ext::number<long>
{
    ACCESS_PIMPL(const gamepad);
    JS_REALM_GET_RELEVANT(this);
    return *ranges::find(v8pp::from_v8<dom::nodes::window*>(this_relevant_agent, this_relevant_global_object)->navigator->d_func()->gamepads, this));
}


auto gamepad::gamepad::get_connected() const -> ext::boolean
{
    ACCESS_PIMPL(const gamepad);
    return d->connected;
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
