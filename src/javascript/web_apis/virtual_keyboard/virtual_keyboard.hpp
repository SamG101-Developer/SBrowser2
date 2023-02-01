#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIRTUAL_KEYBOARD_VIRTUAL_KEYBOARD_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIRTUAL_KEYBOARD_VIRTUAL_KEYBOARD_HPP

// Inheritance Includes & This Class

namespace virtual_keyboard {class virtual_keyboard;}
namespace virtual_keyboard {class virtual_keyboard_private;}

// Other Includes & Forward Declarations
namespace css::geometry {class dom_rect;}


class virtual_keyboard::virtual_keyboard
        : public dom::nodes::event_target
{
public constructors:
    virtual_keyboard();
    MAKE_PIMPL(virtual_keyboard);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_methods:
    auto show() -> void;
    auto hide() -> void;

private js_properties:
    DEFINE_GETTER(bounding_rext, css::geometry::dom_rect*);
    DEFINE_GETTER(overlays_context, ext::boolean);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIRTUAL_KEYBOARD_VIRTUAL_KEYBOARD_HPP
