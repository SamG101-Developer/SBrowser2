#include "construction_internals.hpp"



#include "javascript/environment/realms.hpp"

#include "gamepad/gamepad.hpp"
#include "gamepad/gamepad_private.hpp"

#include "dom/nodes/window.hpp"
#include "html/navigators/navigator.hpp"


#include <range/v3/range/operations.hpp>
#include <range/v3/action/push_back.hpp>
#include <range/v3/view/repeat_n.hpp>


auto gamepad::detail::select_unused_gamepad_index(
        gamepad* gamepad)
        -> ext::number<int>
{
    auto e = js::env::env::relevant(gamepad);
    decltype(auto) global_object = e.cpp.global<dom::nodes::window*>();
    decltype(auto) navigator = global_object->navigator();

    if (!ranges::contains(navigator->s_gamepads(), nullptr))
        navigator->s_gamepads().push_back(nullptr);

    return ranges::distance(
            ranges::begin(navigator->d_func()->gamepads()),
            ranges::first_where(navigator->d_func()->gamepads(), ext::pointer_not_null));
}


auto gamepad::detail::initialize_axes(
        gamepad* gamepad)
        -> ext::vector<ext::number<double>>
{
    decltype(auto) input_count = static_cast<int>(gamepad->d_func()->axes.size());
    gamepad->d_func()->axis_minimums |= ranges::actions::push_back(ext::make_initializer_list_repeat(ext::number<double>::min(), input_count));
    gamepad->d_func()->axis_maximums |= ranges::actions::push_back(ext::make_initializer_list_repeat(ext::number<double>::max(), input_count));

    auto unmapped_input_list = ext::vector<ext::number<int>>{};
    auto mapped_index_list = ext::vector<ext::number<int>>{};
    auto axes_size = ext::number{0};

    for (auto raw_input_index = 0; raw_input_index < input_count; ++raw_input_index)
    {
        // TODO
    }
}
