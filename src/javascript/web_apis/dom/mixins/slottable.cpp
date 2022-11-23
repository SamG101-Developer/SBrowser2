#include "slottable.hpp"
#include "slottable_private.hpp"

#include "ext/casting.hpp"
#include "dom/nodes/node.hpp"
#include "dom/detail/shadow_internals.hpp"
#include "html/elements/html_slot_element.hpp"


auto dom::mixins::slottable::get_assigned_slot() const -> html::elements::html_slot_element*
{
    // Find a slot for this class, cast as a Node object. Return the found slot.
    decltype(auto) base = ext::cross_cast<const nodes::node*>(this);
    decltype(auto) slot = detail::find_slot(base, true);
    return slot;
}


auto dom::mixins::slottable::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("assignedSlot", &slottable::get_assigned_slot)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
