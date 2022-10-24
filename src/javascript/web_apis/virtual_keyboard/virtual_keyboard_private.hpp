#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIRTUAL_KEYBOARD_VIRTUAL_KEYBOARD_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIRTUAL_KEYBOARD_VIRTUAL_KEYBOARD_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/event_target.hpp"

namespace css::geometry {class dom_rect;}


DEFINE_PRIVATE_CLASS(virtual_keyboard, virtual_keyboard) : dom::nodes::event_target
{
    ext::boolean overlays_content;
    css::geometry::dom_rect
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIRTUAL_KEYBOARD_VIRTUAL_KEYBOARD_PRIVATE_HPP
