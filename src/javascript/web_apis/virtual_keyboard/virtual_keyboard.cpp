#include "virtual_keyboard.hpp"
#include "virtual_keyboard_private.hpp"

#include "css/geometry/dom_rect.hpp"

#include "dom/detail/event_internals.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "virtual_keyboard/detail/virtual_keyboard_internals.hpp"

#include <qguiapplication.h>


auto virtual_keyboard::virtual_keyboard::show() -> void
{
    auto window = js::env::env::relevant(this).cpp.global<dom::nodes::window*>();
    ASSERT(window);

    return_if (!html::detail::has_sticky_activation(window));
    return_if (!html::detail::is_form_control(html::detail::focused_element()));
    // TODO : policy
    QGuiApplication::inputMethod()->show();

    GO [this, window]
    {
        // TODO : wait for virtual keyboard to be shown
        detail::set_virtual_keyboard_bounding_rect(
                std::make_unique<css::geometry::dom_rect>(QGuiApplication::inputMethod()->keyboardRectangle()).get())
                css::detail::viewport(window->d_func()->bounding_rect.get()));

        dom::detail::fire_event(u"geometrychange", this);
    };
}


auto virtual_keyboard::virtual_keyboard::hide() -> void
{
    decltype(auto) window = js::env::env::relevant(this).cpp.global<dom::nodes::window*>();
    ASSERT(window);

    return_if (!html::detail::has_sticky_activation(window));
    // TODO : policy
    QGuiApplication::inputMethod()->hide();

    GO [this, window]
    {
        // TODO : wait for virtual keyboard to be hidden
        detail::set_virtual_keyboard_bounding_rect(
                std::make_unique<css::geometry::dom_rect>(QGuiApplication::inputMethod()->keyboardRectangle()).get()),
                css::detail::viewport(window->d_func()->bounding_rect)));

        dom::detail::fire_event(u"geometrychange", this);
    };
}
