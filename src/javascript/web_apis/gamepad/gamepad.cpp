#include "gamepad.hpp"
#include "gamepad_private.hpp"

#include "ext/pimpl.hpp"
#include "ext/uuid.hpp"

#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "hr_time/detail/time_internals.hpp"
#include "hr_time/performance.hpp"

#include "gamepad/detail/construction_internals.hpp"

#include <range/v3/algorithm/find.hpp>


gamepad::gamepad::gamepad()
        : index{detail::select_unused_gamepad_index(this)}
{
    INIT_PIMPL(gamepad);
    auto e = js::env::env::relevant(this);

    ACCESS_PIMPL(gamepad);
    d->id = ext::to_string(ext::uuid::uuid_system_generator{}());
    d->timestamp = hr_time::detail::current_hr_time(e.js.global());
    d->mapping = detail::select_mapping(this);
    d->axes = detail::initialize_axes(this);
    d->buttons = detail::initialize_buttons(this);
}


auto gamepad::gamepad::get_id() const -> ext::string_view
{
    ACCESS_PIMPL(const gamepad);
    return d->id;
}


auto gamepad::gamepad::get_index() const -> ext::number<long>
{
    ACCESS_PIMPL(const gamepad);
    auto e = js::env::env::relevant(this);

    decltype(auto) gamepads = e.cpp.global<dom::nodes::window*>()->d_func()->navigator->d_func()->gamepads;
    decltype(auto) iterator = ranges::find(gamepads, this);
    return ranges::distance(gamepads.begin(), iterator);
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


auto gamepad::gamepad::get_axes() const -> ext::vector_span<ext::number<double>>
{
    ACCESS_PIMPL(const gamepad);
    return d->axes;
}


auto gamepad::gamepad::get_buttons() const -> ext::vector_span<gamepad_button*>
{
    ACCESS_PIMPL(const gamepad);
    return d->buttons;
}


auto gamepad::gamepad::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
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
