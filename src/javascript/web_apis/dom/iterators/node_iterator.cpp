#include "node_iterator.ixx"
#include "node_iterator_private.ixx"

#include "dom/detail/traversal_internals.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/document.hpp"
#include "dom/other/dom_implementation.hpp"



dom::node_iterators::node_iterator::node_iterator()
{
    INIT_PIMPL(node_iterator)

    ACCESS_PIMPL(node_iterator);
    d->reference = nullptr;
    d->pointer_before_reference = false;
}


auto dom::node_iterators::node_iterator::next_node()
        -> nodes::node*
{
    // Visit the next node that this NodeIterator is configured to find (with the NodeFilter interface), by calling the
    // detail traversal method, with the NEXT configuration.
    using detail::traversal_direction_t;
    return detail::traverse(this, traversal_direction_t::NEXT);
}


auto dom::node_iterators::node_iterator::prev_node()
        -> nodes::node*
{
    // Visit the previous node that this NodeIterator is configured to find (with the NodeFilter interface), by calling
    // the detail traversal method, with the PREVIOUS configuration.
    using detail::traversal_direction_t;
    return detail::traverse(this, traversal_direction_t::PREVIOUS);
}


auto dom::node_iterators::node_iterator::get_reference_node() const -> nodes::node*
{
    // The 'reference_node' getter returns the equivalent 'reference_node' attribute value that is stored in the private
    // class.
    ACCESS_PIMPL(const node_iterator);
    return d->reference.get();
}


auto dom::node_iterators::node_iterator::get_pointer_before_reference_node() const -> ext::boolean
{
    // The 'pointer_before_reference_node' getter returns the equivalent 'pointer_before_reference_node' attribute value
    // that is stored in the private class.
    ACCESS_PIMPL(const node_iterator);
    return d->pointer_before_reference;
}


auto dom::node_iterators::node_iterator::_to_v8(
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
