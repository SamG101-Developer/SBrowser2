#include "pointer_internals.hpp"

#include "ext/boolean.hpp"

#include "dom/detail/event_internals.hpp"
#include "pointer_events/pointer_event.hpp"


auto pointer_events::pointer_internals::fire_pointer_event(
        ext::string&& e,
        dom::nodes::event_target* target,
        ext::map<ext::string, ext::any>&& init) -> ext::boolean
{
    ext::boolean supports_hover; // TODO

    if (supports_hover)
    {
        if (!init.try_emplace("isPrimary").first->second.to<ext::boolean>())
            return dom::detail::event_internals::fire_event<pointer_event>(std::move(e), target, std::move(init));

        auto canceled = !dom::detail::event_internals::fire_event<pointer_event>(std::move(e), target, std::move(init));
        // TODO : pointer type stuff
    }

    else
    {
        // TODO
    }
}
