#include "virtual_keyboard_internals.hpp"

#include "css/geometry/dom_rect.hpp"
#include "css/geometry/dom_rect_private.hpp"
#include "css/geometry/dom_rect_readonly.hpp"
#include "css/geometry/dom_rect_readonly_private.hpp"

#include <qguiapplication.h>
#include <qrect.h>


auto virtual_keyboard::detail::set_virtual_keyboard_bounding_rect(
        css::geometry::dom_rect* on_screen_keyboard,
        css::geometry::dom_rect* viewport)
        -> std::unique_ptr<css::geometry::dom_rect>
{
    auto mapped_osk = on_screen_keyboard->d_func()->map_to(viewport);
    auto bounds = std::make_unique<css::geometry::dom_rect>(mapped_osk->d_func()->intersected_with(viewport));
    return bounds->d_func()->map_to(viewport);
}
