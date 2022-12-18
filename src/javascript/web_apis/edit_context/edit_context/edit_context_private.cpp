module apis.edit_context.edit_context_private;

import css.geometry.dom_rect;


edit_context::edit_context_private::edit_context_private()
        : text{""}
        , selection_start{0}, selection_end{0}
        , composition_ange_start{0}, composition_range_end{0}
        , character_bounds_range_start{0}
        , is_in_composiiton{false}
        , contol_bound{std::make_unique<css::geometry::dom_rect>(0, 0, 0, 0)}
        , selection_bound{std::make_unique<css::geometry::dom_rect>(0, 0, 0, 0)}
{}
