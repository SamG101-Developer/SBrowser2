#include "algorithm_internals.hpp"



#include "dom/detail/event_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "html/detail/task_internals.hpp"
#include "html/navigators/navigator.hpp"
#include "html/navigators/navigator_private.hpp"

#include <v8pp/convert.hpp>


template <ext::type_is<ext::boolean, ext::number<double>> T>
auto battery::algorithm_internals::update_battery_status_and_notify(
        T* property,
        T&& new_value,
        ext::string&& event_name)
        -> void
{
    // If the global object isn't a window, then return from the method, because the rest of the method relies on the
    // global object being a Window.
    auto e = js::env::env::current();
    decltype(auto) window = e.cpp.template global<dom::nodes::window*>();
    return_if (window);

    // If there is no Window.[[BatteryManager]], then return from the method, because the rest of the method relied on
    // the battery manager existing.
    decltype(auto) battery_manager = window->d_func()->navigator->d_func()->battery_manager.get();
    return_if (!battery_manager);

    // Queue a task on the idle task source to set the slot value, and fire the 'event_name' event at the BatteryManager
    // object.
    dom::detail::queue_task(html::detail::idle_task_source,
            [battery_manager, property, event_name = std::move(event_name), new_value = std::forward<T>(new_value)] mutable
            {*property = std::forward<T>(new_value); dom::detail::fire_event(std::move(event_name), battery_manager);});
}
