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
{}
