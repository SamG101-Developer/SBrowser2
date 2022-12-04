#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_DETAIL_INPUT_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_DETAIL_INPUT_INTERNALS_HPP


namespace gamepad {class gamepad;}


namespace gamepad::detail
{
    auto when_system_receives_new_button_or_axis_input_values(
            gamepad* gamepad)
            -> void;

    auto when_gamepad_available_on_system()
            -> void;

    auto when_gamepad_unavailable_on_system()
            -> void;

    auto update_gamepad_state(
            gamepad* gamepad)
            -> void;

    auto map_and_normalize_axes(
            gamepad* gamepad)
            -> void;

    auto map_and_normalize_buttons(
            gamepad* gamepad)
            -> void;

    auto contains_gamepad_user_gesture(
            gamepad* gamepad)
            -> ext::boolean;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_DETAIL_INPUT_INTERNALS_HPP
