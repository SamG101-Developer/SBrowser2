#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_DETAIL_CONSTRUCTION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_DETAIL_CONSTRUCTION_INTERNALS_HPP

#include <memory>
#include "ext/number.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(gamepad)

namespace gamepad {class gamepad;}
namespace gamepad {class gamepad_button;}


namespace gamepad::detail
{
    auto select_unused_gamepad_index(
            gamepad* gamepad)
            -> ext::number<int>;

    auto select_mapping(
            gamepad* gamepad)
            -> detail::gamepad_mapping_type_t;

    auto initialize_axes(
            gamepad* gamepad)
            -> ext::vector<ext::number<double>>;

    auto initialize_buttons(
            gamepad* gamepad)
            -> ext::vector<gamepad_button*>;

    auto is_standard_gamepad(
            ext::number<int> gamepad_axis)
            -> ext::boolean;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_DETAIL_CONSTRUCTION_INTERNALS_HPP
