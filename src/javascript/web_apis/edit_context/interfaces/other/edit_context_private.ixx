module;
#include "ext/macros.hpp"
#include <utility>


export module apis.edit_context.edit_context:p;
import apis.dom.event_target;
import apis.css.geometry.types;


DEFINE_PRIVATE_CLASS(edit_context, edit_context)
        : dom::event_target_private
{
public:
    edit_context_private();
    MAKE_QIMPL(edit_context);

public:
    ext::string text;
    ext::number<ulong> selection_start;
    ext::number<ulong> selection_end;
    ext::number<ulong> selection_composition_range_start;
    ext::number<ulong> selection_composition_range_end;
    ext::number<ulong> character_bounds_range_start;
    ext::boolean is_in_composition;
    std::unique_ptr<css::geometry::dom_rect> control_bound;
    std::unique_ptr<css::geometry::dom_rect> selection_bound;

    ext::boolean activated;
    ext::vector<std::unique_ptr<css::geometry::dom_rect>> cached_character_bounds;
};
