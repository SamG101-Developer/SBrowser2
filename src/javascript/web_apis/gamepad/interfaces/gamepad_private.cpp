module;
#include <libgamepad.hpp>


module apis.gamepad.gamepad:p;

import ext.core;


auto gamepad::gamepad_private::select_unused_gamepad_index() const -> detail::gamepad_mapping_type_t
{
    auto platform_axis = platform_gamepad->get_axis();
    auto platform_buttons = platform_gamepad->get_buttons();
    // TODO

    return detail::gamepad_mapping_type_t::STANDARD;
}
