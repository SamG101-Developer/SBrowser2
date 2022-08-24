#include "algorithm_internals.hpp"

#include "javascript/environment/realms_2.hpp"

#include "dom/detail/event_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/nodes/window.hpp"

#include "html/detail/task_internals.hpp"
#include "html/other/navigator.hpp"

#include <v8pp/convert.hpp>


template <typename T>
auto battery::algorithm_internals::update_battery_status_and_notify(
        ext::slot<T>& slot,
        T&& new_value,
        ext::string&& event_name)
        -> void
{
    JS_REALM_GET_CURRENT;
    auto* window = v8pp::from_v8<dom::nodes::window*>(current_agent, current_global_object);
    return_if (!window);

    decltype(auto) battery_manager = window->navigator()->s_battery_manager();
    return_if (!battery_manager);

    dom::detail::queue_task(
            html::detail::idle_task_source(),
            [battery_manager, &slot, event_name = std::move(event_name), new_value = std::forward<T>(new_value)] mutable
            {slot = std::forward<T>(new_value); dom::detail::fire_event(std::move(event_name), battery_manager);});
}
