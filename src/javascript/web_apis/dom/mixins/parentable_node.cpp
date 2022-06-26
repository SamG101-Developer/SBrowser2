#include "parentable_node.hpp"


#include <web_apis/dom/nodes/node.hpp>
#include <web_apis/dom/nodes/window.hpp>
#include <web_apis/dom/detail/customization_internals.hpp>
#include <web_apis/dom/detail/node_internals.hpp>
#include <web_apis/dom/detail/mutation_internals.hpp>

#include <range/v3/view/remove.hpp>


dom::mixins::parentable_node::parentable_node()
{
    bind_get(children);
    bind_get(first_element_child);
    bind_get(last_element_child);
    bind_get(child_element_count);
}


auto dom::mixins::parentable_node::prepend(
        same_as_any<nodes::node*, ext::string> auto&&... nodes)
        -> void
{
    // parse the 'nodes' parameter, and pre insert the derived 'node' into this's child nodes, before the first node in
    // the child nodes list
    ce_reactions_method_def
        auto* base = ext::cross_cast<nodes::node*>(this);
        auto* node = detail::node_internals::convert_nodes_into_node(base->owner_document(), std::forward<decltype(nodes)>(nodes)...);
        detail::mutation_internals::pre_insert(node, base, base->child_nodes->front());
    ce_reactions_method_exe
}


auto dom::mixins::parentable_node::append(
        same_as_any<nodes::node*, ext::string> auto&&... nodes)
        -> void
{
    // parse the 'nodes' parameter, and append the derived 'node' into this's child nodes, after the first node in the
    // child nodes list
    ce_reactions_method_def
        auto* base = ext::cross_cast<nodes::node*>(this);
        auto* node = detail::node_internals::convert_nodes_into_node(base->owner_document(), std::forward<decltype(nodes)>(nodes)...);
        detail::mutation_internals::append(node, base, base->child_nodes->front());
    ce_reactions_method_exe
}


auto dom::mixins::parentable_node::replace_children(
        same_as_any<nodes::node*, ext::string> auto&&... nodes)
        -> void
{
    // parse the 'nodes' parameter, and replace the derived 'node' from this's child nodes, after ensuring pre insertion
    // validity of the node, at the end of the child nodes list
    ce_reactions_method_def
        auto* base = ext::cross_cast<nodes::node*>(this);
        auto* node = detail::node_internals::convert_nodes_into_node(base->owner_document(), std::forward<decltype(nodes)>(nodes)...);
        detail::mutation_internals::ensure_pre_insertion_validity(node, base, nullptr);
        detail::mutation_internals::replace_all(node, base);
    ce_reactions_method_exe
}


auto dom::mixins::parentable_node::get_children() const -> ranges::ref_view<ext::vector<nodes::element*>>
{
    const auto* base = ext::cross_cast<const nodes::node*>(this);
    const auto element_children = *base->child_nodes() | ranges::views::cast_all_to<nodes::element*>();

    return element_children;
}


auto dom::mixins::parentable_node::to_v8(
        v8::Isolate* isolate) const &&
        -> ext::any
{
    return v8pp::class_<parentable_node>{isolate}
            .inherit<web_apis::dom_object>()
            .function("prepend", &parentable_node::prepend, v8::DontEnum)
            .function("append", &parentable_node::append, v8::DontEnum)
            .function("replaceChildren", &parentable_node::replace_children, v8::DontEnum)
            .auto_wrap_objects();

    v8::Local<v8::Object> v;
}
