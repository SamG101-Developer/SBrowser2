#include "construction_internals.hpp"

#include "ext/functional.hpp"
#include "ext/initializer_list.hpp"
#include "ext/ranges.hpp"
#include "javascript/environment/realms_2.hpp"

#include "dom/nodes/window.hpp"
#include "gamepad/gamepad.hpp"
#include "html/other/navigator.hpp"

#include <initializer_list>
#include <range/v3/range/operations.hpp>
#include <range/v3/action/push_back.hpp>
#include <range/v3/view/repeat_n.hpp>


auto gamepad::detail::select_unused_gamepad_index(
        gamepad* gamepad)
        -> ext::number<int>
{
    JS_REALM_GET_RELEVANT(gamepad);
    decltype(auto) global_object = v8pp::from_v8<dom::nodes::window*>(gamepad_relevant_agent, gamepad_relevant_global_object);
    decltype(auto) navigator = global_object->navigator();

    if (!ranges::contains(navigator->s_gamepads(), nullptr))
        navigator->s_gamepads().push_back(nullptr);

    return ranges::distance(
            ranges::begin(navigator->s_gamepads())
            ranges::first_where(navigator->s_gamepads(), ext::pointer_not_null{}));
}


auto gamepad::detail::initialize_axes(
        gamepad* gamepad)
        -> ext::vector<ext::number<double>>
{
    decltype(auto) input_count = static_cast<int>(gamepad->axes()->size());
    gamepad->s_axis_minimums() |= ranges::actions::push_back(ext::make_initializer_list_repeat(ext::number<double>::min(), input_count));
    gamepad->s_axis_maximums() |= ranges::actions::push_back(ext::make_initializer_list_repeat(ext::number<double>::max(), input_count));

    auto unmapped_input_list = ext::vector<ext::number<int>>{};
    auto mapped_index_list = ext::vector<ext::number<int>>{};
    auto axes_size = ext::number{0};

    for (auto raw_input_index = 0; raw_input_index < input_count; ++raw_input_index)
    {
        if
    }
}
