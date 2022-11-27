#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIRTUAL_KEYBOARD_DETAIL_VIRTUAL_KEYBOARD_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIRTUAL_KEYBOARD_DETAIL_VIRTUAL_KEYBOARD_INTERNALS_HPP

#include <memory>
namespace css::geometry {class dom_rect;}


namespace virtual_keyboard::detail
{
    auto set_virtual_keyboard_bounding_rect(
            css::geometry::dom_rect* on_screen_keyboard,
            css::geometry::dom_rect* viewport)
            -> std::unique_ptr<css::geometry::dom_rect>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIRTUAL_KEYBOARD_DETAIL_VIRTUAL_KEYBOARD_INTERNALS_HPP
