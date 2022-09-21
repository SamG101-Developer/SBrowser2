#include "node_iterator.hpp"

#include "dom/detail/traversal_internals.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/document.hpp"
#include "dom/other/dom_implementation.hpp"


dom::node_iterators::node_iterator::node_iterator()
        : reference_node{nullptr}
        , pointer_before_reference_node{false}
{}


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
            .var("referenceNode", &node_iterator::reference_node, true)
            .var("pointerBeforeReferenceNode", &node_iterator::pointer_before_reference_node, true)
            .auto_wrap_objects();

    return std::move(conversion);
}
