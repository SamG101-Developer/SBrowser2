#ifndef SBROWSER2_SHADOW_INTERNALS_HPP
#define SBROWSER2_SHADOW_INTERNALS_HPP


#include "ext/vector.hpp"
#include <range/v3/view/any_view.hpp>
namespace dom::mixins {class slottable;}
namespace dom::nodes {class event_target;}
namespace dom::nodes {class node;}
namespace dom::nodes {class shadow_root;}
namespace html::elements {class html_slot_element;}


namespace dom::detail
{


    // find slots and slottables

    auto find_slottables(
            const html::elements::html_slot_element* slot)
            -> ranges::any_view<dom::mixins::slottable*>; // TODO <- correct template type?

    auto find_flattened_slottables(
            const html::elements::html_slot_element* slot)
            -> ranges::any_view<dom::mixins::slottable*>; // TODO <- correct template type?

    // assign slots and slottables

    auto assign_slottables(
            const html::elements::html_slot_element* slot)
            -> void;

    auto assign_slottables_for_tree(
            const html::elements::html_slot_element* descendant)
            -> void;

    // other general helper methods for shadows

}


#endif //SBROWSER2_SHADOW_INTERNALS_HPP
