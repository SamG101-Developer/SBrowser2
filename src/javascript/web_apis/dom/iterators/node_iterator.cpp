#include "node_iterator.hpp"

#include "dom/detail/traversal_internals.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/document.hpp"
#include "dom/other/dom_implementation.hpp"
#include "dom/iterators/node_filter.hpp"


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
    // visit the next node that this NodeIterator is configured to find (with the NodeFilter interface), by calling the
    // detail traversal method, with the NEXT configuration
    using detail::traversal_direction_t;
    return detail::traverse(this, traversal_direction_t::NEXT);
}


auto dom::node_iterators::node_iterator::prev_node()
        -> nodes::node*
{
    // visit the previous node that this NodeIterator is configured to find (with the NodeFilter interface), by calling
    // the detail traversal method, with the PREVIOUS configuration
    using detail::traversal_direction_t;
    return detail::traverse(this, traversal_direction_t::PREVIOUS);
}


auto dom::node_iterators::node_iterator::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<node_iterator>{isolate}
        .inherit<abstract_iterator>()
        .function("nextNode", &node_iterator::next_node)
        .function("previousNode", &node_iterator::prev_node)
        .property("referenceNode", &node_iterator::get_reference_node)
        .property("pointerBeforeReferenceNode", &node_iterator::get_pointer_before_reference_node)
        .auto_wrap_objects();

    return std::move(conversion);
}
