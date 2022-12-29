module;
#include "ext/macros/macros.hpp"
#include <libgamepad.hpp>


export module apis.gamepad.detail;
import apis.gamepad.types;

import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(gamepad)
{
    const auto hook = ::gamepad::hook::make();
    auto init() -> void;

    /* [3.1.2] */ auto update_gamepad_state(gamepad* gamepad) -> void;
    /* [3.1.3] */ auto map_and_normalize_axes(gamepad* gamepad) -> void;
    /* [3.1.4] */ auto map_and_normalize_buttons(gamepad* gamepad) -> void;
    /* [3.2.1] */ auto initialize_axes(gamepad* gamepad)-> ext::vector<ext::number<double>>;
    /* [3.2.2] */ auto initialize_buttons(gamepad* gamepad) -> ext::vector<gamepad_button*>;
}
