#include "gamepad.hpp"

#include "ext/pimpl.hpp"
#include "ext/uuid.hpp"

#include "dom/nodes/window.hpp"
#include "hr_time/detail/time_internals.hpp"
#include "gamepad/detail/construction_internals.hpp"

#include "hr_time/performance.hpp"


gamepad::gamepad::gamepad()
        : index{detail::select_unused_gamepad_index(this)}
{
    INIT_PIMPL(gamepad);
    ACCESS_PIMPL(gamepad);

    JS_REALM_GET_RELEVANT(this);

    d->id = ext::to_string(ext::uuid_system_generator{}());
    d->timestamp = hr_time::detail::current_hr_time(this_relevant_global_object);
    d->mapping = detail::select_mapping(this);
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


auto gamepad::gamepad::get_timestamp() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const gamepad);
    return d->timestamp;
}


auto gamepad::gamepad::get_mapping() const -> detail::gamepad_mapping_type_t
{
    ACCESS_PIMPL(const gamepad);
    return d->mapping;
}


auto gamepad::gamepad::get_axes() const -> ext::vector_view<ext::number<double>>
{
    ACCESS_PIMPL(const gamepad);
    return {d->axes.begin(), d->axes.end()};
}


auto gamepad::gamepad::get_buttons() const -> ext::vector_view<gamepad_button*>
{
    ACCESS_PIMPL(const gamepad);
    return {d->buttons.begin(), d->buttons.end()};
}


auto gamepad::gamepad::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<gamepad>{isolate}
        .inherit<dom_object>()
        .ctor<>()
        .property("id", &gamepad::get_id)
        .property("index", &gamepad::get_index)
        .property("connected", &gamepad::get_connected)
        .property("timestamp", &gamepad::get_timestamp)
        .property("mapping", &gamepad::get_mapping)
        .property("axes", &gamepad::get_axes)
        .property("buttons", &gamepad::get_buttons)
        .auto_wrap_objects();

    return std::move(conversion);
}
