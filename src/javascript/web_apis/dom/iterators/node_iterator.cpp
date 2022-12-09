module;
#include "ext/macros/pimpl.hpp"


module apis.dom.node_iterator;
import apis.dom.node_iterator_private;
import ext.boolean;


dom::node_iterator::node_iterator()
{
    INIT_PIMPL; ACCESS_PIMPL;

    d->reference = nullptr;
    d->pointer_before_reference = false;
}


auto dom::node_iterator::next_node() -> node*
{
    // Visit the next node that this NodeIterator is configured to find (with the NodeFilter interface), by calling the
    // detail traversal method, with the NEXT configuration.
    using detail::traversal_direction_t;
    return detail::traverse(this, traversal_direction_t::NEXT);
}


auto dom::node_iterator::prev_node() -> node*
{
    // Visit the previous node that this NodeIterator is configured to find (with the NodeFilter interface), by calling
    // the detail traversal method, with the PREVIOUS configuration.
    using detail::traversal_direction_t;
    return detail::traverse(this, traversal_direction_t::PREVIOUS);
}


auto dom::node_iterator::get_reference_node() const -> node*
{
    // The 'reference_node' getter returns the equivalent 'reference_node' attribute value that is stored in the private
    // class.
    ACCESS_PIMPL;
    return d->reference.get();
}


auto dom::node_iterator::get_pointer_before_reference_node() const -> ext::boolean
{
    // The 'pointer_before_reference_node' getter returns the equivalent 'pointer_before_reference_node' attribute value
    // that is stored in the private class.
    ACCESS_PIMPL;
    return d->pointer_before_reference;
}


auto dom::node_iterator::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<abstract_iterator>()
        .function("nextNode", &node_iterator::next_node)
        .function("previousNode", &node_iterator::prev_node)
        .property("referenceNode", &node_iterator::get_reference_node)
        .property("pointerBeforeReferenceNode", &node_iterator::get_pointer_before_reference_node)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
