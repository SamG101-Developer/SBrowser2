#include "input_internals.hpp"

#include "ext/hashing.ixx"
#include "ext/functional.ixx"
#include "ext/ranges.hpp"

#include "javascript/environment/realms.hpp"

#include "dom/detail/event_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "gamepad/gamepad.hpp"
#include "gamepad/gamepad_private.hpp"
#include "gamepad/gamepad_button.hpp"
#include "gamepad/gamepad_button_private.hpp"
#include "gamepad/gamepad_event.hpp"
#include "gamepad/gamepad_event_private.hpp"

#include "hr_time/detail/time_internals.hpp"

#include "html/detail/task_internals.hpp"
#include "html/navigators/navigator.hpp"

#include <range/v3/view/filter.hpp>


auto gamepad::detail::when_system_receives_new_button_or_axis_input_values(
        gamepad* gamepad)
        -> void
{
    dom::detail::queue_task(
            html::detail::gamepad_task_source,
            [gamepad] {update_gamepad_state(gamepad);});
}


auto gamepad::detail::update_gamepad_state(
        gamepad* gamepad)
        -> void
{
    auto e = js::env::env::relevant(gamepad);
    auto now = hr_time::detail::current_hr_time(e.js.global());
    gamepad->d_func()->timestamp = now;

    map_and_normalize_axes(gamepad);
    map_and_normalize_buttons(gamepad);

    decltype(auto) global_object = e.cpp.global<dom::nodes::window*>();
    decltype(auto) navigator = global_object->d_func()->navigator.get();

    if (!navigator->d_func()->has_gamepad_gesture() && contains_gamepad_user_gesture(gamepad))
    {
        navigator->d_func()->has_gamepad_gesture = true;
        auto connected_gamepads = navigator->d_func()->gamepads;
        for (decltype(auto) connected_gamepad: connected_gamepads | ranges::views::filter(ext::pointer_not_null))
        {
            connected_gamepad->d_func()->exposed = true;
            connected_gamepad->d_func()->timestamp = now;

            decltype(auto) document = global_object->d_func()->document.get();
            if (document && dom::detail::is_document_fully_active(document))
                dom::detail::queue_task(html::detail::gamepad_task_source,
                        [gamepad, &e] {dom::detail::fire_event<gamepad_event>(u"gamepadconnected", e.js.global(), {{u"gamepad", gamepad}});});
        }
    }
}


auto gamepad::detail::map_and_normalize_axes(
        gamepad* gamepad)
        -> void
{
    decltype(auto) axis_values = gamepad->d_func()->axes;

    for (auto raw_axis_index = 0; raw_axis_index < axis_values.size(); ++raw_axis_index)
    {
        auto mapped_index = gamepad->d_func()->axis_mapping.at(raw_axis_index);
        auto logical_value = axis_values.at(raw_axis_index);
        auto logical_minimum = gamepad->d_func()->axis_minimums.at(raw_axis_index);
        auto logical_maximum = gamepad->d_func()->axis_maximums.at(raw_axis_index);

        auto normalized_value = 2.0 * (logical_value - logical_minimum) / (logical_maximum - logical_minimum) - 1;
        gamepad->d_func()->axes.at(raw_axis_index) = std::move(normalized_value);
    }
}


auto gamepad::detail::map_and_normalize_buttons(
        gamepad* gamepad)
        -> void
{
    decltype(auto) button_values = *gamepad->d_func()->buttons() | ranges::views::transform_to_attr(&gamepad_button_private::value, ext::get_pimpl);
    
    for (auto raw_button_index = 0; raw_button_index < button_values.size(); ++raw_button_index)
    {
        auto mapped_index = gamepad->d_func()->button_mapping()->at(raw_button_index);
        auto logical_value = button_values->at(raw_button_index);
        auto logical_minimum = gamepad->d_func()->button_minimums()->at(raw_button_index);
        auto logical_maximum = gamepad->d_func()->button_maximums()->at(raw_button_index);

        auto normalized_value = 2.0 * (logical_value - logical_minimum) / (logical_maximum - logical_minimum) - 1;
        decltype(auto) button = gamepad->d_func()->buttons()->at(mapped_index);
        button.s_value = std::move(normalized_value);

        // TODO: button->s_pressed, button->s_touched
    }
}
