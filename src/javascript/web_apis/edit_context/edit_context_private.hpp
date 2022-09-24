#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EDIT_CONTEXT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EDIT_CONTEXT_PRIVATE_HPP

#include "dom/nodes/event_target_private.hpp"

#include "ext/pimpl.hpp"
#include <memory>
namespace css::geometry {class dom_rect;}


DEFINE_PRIVATE_CLASS(edit_context, edit_context) : dom::nodes::event_target_private
{
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


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EDIT_CONTEXT_PRIVATE_HPP
