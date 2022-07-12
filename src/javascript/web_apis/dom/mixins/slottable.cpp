#include "slottable.hpp"

#include "ext/casting.hpp"
#include "dom/nodes/node.hpp"
#include "dom/detail/shadow_internals.hpp"


dom::mixins::slottable::slottable()
{
    bind_get(assigned_slot);
}


auto dom::mixins::slottable::get_assigned_slot()
        const -> html::elements::html_slot_element*
{

    // find a slot for the 'base' cast version of this class
    auto* base = ext::cross_cast<const nodes::node*>(this);
    auto* slot = detail::shadow_internals::find_slot(base, true);
    return slot;
}


auto dom::mixins::slottable::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<slottable>{isolate}
        .inherit<web_apis::dom_object>()
        .var("assignedSlot", &slottable::assigned_slot, false)
        .auto_wrap_objects();
}
