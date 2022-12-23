module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <range/v3/algorithm/find.hpp>
#include <range/v3/range/operations.hpp>


module apis.gamepad.gamepad;
import apis.gamepad.gamepad_private;
import apis.gamepad.gamepad_button;
import apis.gamepad.detail;
import apis.gamepad.types;

import apis.hr_time.detail;
import apis.hr_time.types;

import apis.dom.window;
import apis.dom.window_private;

import ext.core;

import js.env.realms;
import js.env.module_type;


gamepad::gamepad::gamepad()
{
    INIT_PIMPL; ACCESS_PIMPL;
    auto e = js::env::env::relevant(this);

    d->id = ext::to_string(ext::uuid::uuid_system_generator{}());
    d->timestamp = hr_time::detail::current_hr_time(e.js.global());
    d->mapping = detail::select_mapping(this);
    d->axes = detail::initialize_axes(this);
    d->buttons = detail::initialize_buttons(this);
}


auto gamepad::gamepad::get_id() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->id;
}


auto gamepad::gamepad::get_index() const -> ext::number<long>
{
    ACCESS_PIMPL;
    auto e = js::env::env::relevant(this);

    decltype(auto) gamepads = e.cpp.global<dom::window*>()->d_func()->navigator->d_func()->gamepads;
    decltype(auto) iterator = ranges::find(gamepads, this);
    return ranges::distance(gamepads.begin(), iterator);
}


auto gamepad::gamepad::get_connected() const -> ext::boolean
{
    ACCESS_PIMPL;
    return d->connected;
}


auto gamepad::gamepad::get_timestamp() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL;
    return ext::round(d->timestamp, 5);
}


auto gamepad::gamepad::get_mapping() const -> detail::gamepad_mapping_type_t
{
    ACCESS_PIMPL;
    return d->mapping;
}


auto gamepad::gamepad::get_axes() const -> ext::span<ext::number<double>>
{
    ACCESS_PIMPL;
    return d->axes;
}


auto gamepad::gamepad::get_buttons() const -> ext::span<gamepad_button*>
{
    ACCESS_PIMPL;
    return d->buttons;
}


auto gamepad::gamepad::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
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

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
