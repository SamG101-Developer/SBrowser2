#include "slottable.hpp"

#include "ext/casting.hpp"
#include "dom/nodes/node.hpp"
#include "dom/detail/shadow_internals.hpp"
#include "html/elements/html_slot_element.hpp"


dom::mixins::slottable::slottable()
{
    bind_get(assigned_slot);
}


auto dom::mixins::slottable::get_assigned_slot()
        const -> decltype(this->assigned_slot)::value_t
{

    // find a slot for the 'base' cast version of this class
    decltype(auto) base = ext::cross_cast<const nodes::node*>(this);
    decltype(auto) slot = detail::find_slot(base, true);
    return slot;
}


auto dom::mixins::slottable::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<slottable>{isolate}
        .inherit<dom_object>()
        .var("assignedSlot", &slottable::assigned_slot, false)
        .auto_wrap_objects();

    return std::move(conversion);
}
