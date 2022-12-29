module;
#include "javascript/macros/expose.hpp"


module apis.dom.mixins.slottable;
import ext.core;
import js.env.module_type;


auto dom::mixins::slottable::get_assigned_slot() const -> ext::view_of_t<html::html_slot_element*>
{
    // Find a slot for this class, cast as a Node object. Return the found slot.
    decltype(auto) base = ext::cross_cast<const node*>(this);
    decltype(auto) slot = detail::find_slot(base, true);
    return slot;
}


auto dom::mixins::slottable::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("assignedSlot", &slottable::get_assigned_slot)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
