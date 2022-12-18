module;
#include "ext/macros/language_shorthand.hpp"


module apis.edit_context.edit_context_private;

import apis.dom.event;
import apis.dom.event_private;
import apis.dom.event_target;
import apis.dom.event_target_private;
import apis.css.geometry.dom_rect;


edit_context::edit_context_private::edit_context_private()
        : text{""}
        , selection_start{0}, selection_end{0}
        , composition_ange_start{0}, composition_range_end{0}
        , character_bounds_range_start{0}
        , is_in_composiiton{false}
        , contol_bound{std::make_unique<css::geometry::dom_rect>(0, 0, 0, 0)}
        , selection_bound{std::make_unique<css::geometry::dom_rect>(0, 0, 0, 0)}
{
    activation_behaviour = [](dom::event* event)
    {
        if (true /* TODO : in a composition? */)
        {
            auto element = new dom::event_target{}; // TODO : associated element

            element->d_func()->fire_event(u"beforeinput");
            return_if (event->d_func()->canceled_flag);

            // TODO : update text, selection_start, selection_end, composition_range_start, composition_range_end, is_in_compsition
            // TODO : conditionally fire events
        }

        else
        {
            // TODO : fire event
            // TODO : update text, selection_start, selection_end, composition_range_start, composition_range_end, is_in_compsition
            // TODO : conditionally fire events
        }
    };
}
