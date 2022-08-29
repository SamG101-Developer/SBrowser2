#include "input_internals.hpp"

#include "ext/functional.hpp"

#include "javascript/environment/realms_2.hpp"

#include "dom/detail/event_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/observer_internals.hpp"

#include "gamepad/gamepad.hpp"
#include "gamepad/gamepad_event.hpp"

#include "high_resolution_time/performance.hpp"

#include "html/detail/task_internals.hpp"
#include "html/other/navigator.hpp"

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
    auto now = high_resolution_time::performance{}.now();
    gamepad->s_timestamp = now;

    map_and_normalize_axes(gamepad);
    map_and_normalize_buttons(gamepad);

    JS_REALM_GET_RELEVANT(gamepad);
    decltype(auto) navigator = javascript::environment::realms_2::get<html::other::navigator*>(gamepad_relevant_global_object, "$Navigator");

    if (!navigator->s_has_gamepad_gesture() && contains_gamepad_user_gesture(gamepad))
    {
        navigator->s_has_gamepad_gesture = true;
        auto connected_gamepads = navigator->s_gamepads();
        for (decltype(auto) connected_gamepad: connected_gamepads | ranges::views::filter(ext::pointer_not_null{}))
        {
            connected_gamepad->s_exposed = true;
            connected_gamepad->s_timestamp = now;

            decltype(auto) document = javascript::environment::realms_2::get<html::other::navigator*>(gamepad_relevant_global_object, "$AssociatedDocument");
            if (document && dom::detail::is_document_fully_active(document))
                dom::detail::queue_task(html::detail::gamepad_task_source,
                        [gamepad_relevant_global_object, gamepad]
                        {dom::detail::fire_event<gamepad_event>("gamepadconnected", gamepad_relevant_global_object, {{"gamepad", gamepad}});});
        }
    }
}
