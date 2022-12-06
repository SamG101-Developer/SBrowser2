#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIRTUAL_KEYBOARD_VIRTUAL_KEYBOARD_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIRTUAL_KEYBOARD_VIRTUAL_KEYBOARD_PRIVATE_HPP

#include "ext/pimpl.ixx"

namespace css::geometry {class dom_rect;}


DEFINE_PRIVATE_CLASS(virtual_keyboard, virtual_keyboard)
        : dom::nodes::event_target_private
{
    MAKE_QIMPL(virtual_keyboard);

    std::unique_ptr<css::geometry::dom_rect> bounding_rect;
    ext::boolean overlays_content;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIRTUAL_KEYBOARD_VIRTUAL_KEYBOARD_PRIVATE_HPP
