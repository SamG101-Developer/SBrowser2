// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "node.hpp"

#include <queue>
#include <stack>

#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip.hpp>
#include <range/v3/to_container.hpp>

#include <javascript/environment/realms.hpp>

#include <web_apis/dom/detail/customization_internals.hpp>
#include <web_apis/dom/detail/exception_internals.hpp>
#include <web_apis/dom/detail/node_internals.hpp>
#include <web_apis/dom/detail/mutation_internals.hpp>
#include <web_apis/dom/detail/shadow_internals.hpp>
#include <web_apis/dom/detail/text_internals.hpp>
#include <web_apis/dom/detail/tree_internals.hpp>
#include <web_apis/dom/nodes/character_data.hpp>
#include <web_apis/dom/nodes/element.hpp>
#include <web_apis/dom/nodes/node.hpp>
#include <web_apis/dom/nodes/text.hpp>
#include <web_apis/dom/ranges/range.hpp>

#include <range/v3/view/remove.hpp>

#include <QtWidgets/QLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidgetAction>

namespace dom::nodes {class window;}


dom::nodes::node::node()
        : child_nodes(std::make_unique<ext::vector<node*>>())
        , parent_node(nullptr)
{
    bind_get(node_name);
    bind_get(node_value);
    bind_get(text_content);
    bind_get(base_uri);
    bind_get(first_child);
    bind_get(last_child);
    bind_get(previous_sibling);
    bind_get(next_sibling);

    bind_set(node_value);
    bind_set(text_content);
    bind_set(parent_node);
}


auto dom::nodes::node::compare_document_position(
        node* other)
        -> ext::number<ushort>
{
    // if the nodes are the same then return 0 ie there is no comparison to be done
    if (this == other) return 0;

    // set the nodes to the other node and this node, and the attributes to nullptr (don't exist yet)
    auto* node_1 = other;
    auto* node_2 = this;
    attr* attr_1 = dynamic_cast<attr*>(node_1);
    attr* attr_2 = dynamic_cast<attr*>(node_2);

    // if the nodes are attributes, set the 'attr' variables, and the nodes to the attributes' owner elements
    node_1 = attr_1 ? attr_1->owner_element() : node_1;
    node_2 = attr_2 ? attr_2->owner_element() : node_2;

    // if both the nodes being compared are attributes of the same element, compare their position in the attribute list
    if (attr_1 && attr_2 && node_1 && node_1 == node_2)
    {
        for (const auto& attr: *dynamic_cast<element*>(node_2)->attributes())
        {
            if (attr == attr_1) return DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC | DOCUMENT_POSITION_PRECEDING;
            if (attr == attr_2) return DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC | DOCUMENT_POSITION_FOLLOWING;
        }
    }

    // the nodes are disconnected when a node is null, or they belong to different trees
    if (!node_1 or !node_2 || detail::tree_internals::root(node_1) != detail::tree_internals::root(node_2))
        return DOCUMENT_POSITION_DISCONNECTED | DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC | (node_1 < node_2 ? DOCUMENT_POSITION_PRECEDING : DOCUMENT_POSITION_FOLLOWING);

    // the other node contains this node, if it is an ancestor, and not an attribute node
    if (detail::tree_internals::is_ancestor(node_1, node_2) and !attr_1)
        return DOCUMENT_POSITION_CONTAINS | DOCUMENT_POSITION_PRECEDING;

    // the other node contains this node, if it is the owner element of this node (an attribute)
    if (node_1 == node_2 && attr_2)
        return DOCUMENT_POSITION_CONTAINS | DOCUMENT_POSITION_PRECEDING;

    // the other node is contained by this node, if it is a descendant, and not an attribute node
    if (detail::tree_internals::is_descendant(node_1, node_2) and !attr_2)
        return DOCUMENT_POSITION_CONTAINED_BY | DOCUMENT_POSITION_FOLLOWING;

    // the other node is contained by this node, if it is the attribute of this node (an element)
    if (node_1 == node_2 && attr_1)
        return DOCUMENT_POSITION_CONTAINED_BY | DOCUMENT_POSITION_FOLLOWING;

    // the other node is preceding this node if is comes before it in the tree, otherwise it is following it
    return detail::tree_internals::is_preceding(node_1, node_2) ? DOCUMENT_POSITION_PRECEDING : DOCUMENT_POSITION_FOLLOWING;
}


auto dom::nodes::node::get_root_node(
        ext::string_any_map_view options)
        -> node*
{
    // get the shadow including root node if the 'composed' option is set, otherwise get the regular root of the node
    return options.at("composed").value_to_or<bool>(false)
            ? detail::shadow_internals::shadow_including_root(this)
            : detail::tree_internals::root(this);
}


auto dom::nodes::node::contains(
        node* other)
        -> ext::boolean
{
    // this node contains 'other' if 'other' is a descendant of this node
    return detail::tree_internals::is_descendant(other, this);
}


auto dom::nodes::node::has_child_nodes()
        -> ext::boolean
{
    // this node has child nodes if the 'child_nodes' list is not empty
    return !child_nodes->empty();
}


auto dom::nodes::node::normalize()
        -> void
{
    for (nodes::text* text_node: detail::tree_internals::descendant_text_nodes(this))
    {
        // if the length of the text node (ie the length of the text) is 0 then remove the text node
        auto length = dom::detail::tree_internals::length(text_node);
        continue_if(length <= 0);

        // combine the text from the next consecutive text nodes into the text node
        auto data = dom::detail::tree_internals::contiguous_text_nodes(text_node)
                    | ranges::views::transform([](nodes::text* contiguous_text_node) {return contiguous_text_node->data();})
                    | ranges::to<ext::string>();

        // replace the data in this node with the combined data from the contiguous nodes
        detail::text_internals::replace_data(text_node, 0, length, data);

        // get the current node as the next text node (whose text has been combined into the text node's text)
        auto* current_node = text_node->next_sibling();
        auto* live_ranges  = new ext::vector<node_ranges::range*>{}; // TODO javascript::environment::realms::realm<nodes::window*>::surrounding_realm(this).get<ext::vector<node_ranges::range*>*>("live_ranges");

        // iterate by incrementing the current_node to the next sibling
        while (detail::tree_internals::is_exclusive_text_node(current_node))
        {
            // ranges whose starting node is current_node: increment the starting offset by the length of the text of
            // the text node (text has shifted back to previous node) and set the starting node to the text node
            *live_ranges
                    | ranges::views::filter([&current_node](node_ranges::range* range) {return range->start_container == current_node;})
                    | ranges::for_each([&text_node, length](node_ranges::range* range) {range->start_offset += length; range->start_container = text_node;});

            // ranges whose ending node is current_node: increment the ending offset by the length of the text of this
            // text node (text has shifted back to previous node) abd set the ending node to the text node
            *live_ranges
                    | ranges::views::filter([&current_node](node_ranges::range* range) {return range->end_container == current_node;})
                    | ranges::for_each([&text_node, length](node_ranges::range* range) {range->end_offset += length; range->end_container = text_node;});

            // ranges whose starting node is current_node's parent: set the starting offset to the length of the text in
            // the text node and set the starting node to the text node TODO : why?
            *live_ranges
                    | ranges::views::filter([&current_node](node_ranges::range* range) {return range->start_container == current_node->parent_node();})
                    | ranges::for_each([&text_node, length](node_ranges::range* range) {range->start_offset = length; range->start_container = text_node;});

            // ranges whose ending node is current_node's parent: set the ending offset to the length of the text in
            // the text node and set the ending node to the text node TODO : why?
            *live_ranges
                    | ranges::views::filter([&current_node](node_ranges::range* range) {return range->end_container == current_node->parent_node();})
                    | ranges::for_each([&text_node, length](node_ranges::range* range) {range->end_offset = length; range->end_container = text_node;});

            // increment the length by the current_node's length (so that the next current_node's offset can be
            // incremented further as needed to be, and set the current node to the next sibling
            length += detail::tree_internals::length(current_node);
            current_node = current_node->next_sibling();
        }

        dom::detail::tree_internals::contiguous_text_nodes(text_node)
                | ranges::for_each([](node* contiguous_text_node) {detail::mutation_internals::remove(contiguous_text_node);});
    }
}


auto dom::nodes::node::clone_node(
        ext::boolean_view deep)
        -> node*
{
    // throw an error if there is an attempt to clone a shadow node
    detail::exception_internals::throw_v8_exception<NOT_SUPPORTED_ERR>(
            "Cannot clone a ShadowRoot node",
            [this] {return detail::shadow_internals::is_shadow_root(this);});

    // clone the node and return it
    return detail::node_internals::clone(this, nullptr, deep);
}


auto dom::nodes::node::is_equal_node(
        node* other)
        -> ext::boolean
{
    // the nodes aren't equal if the other node is null, there are a different amount of child nodes belonging to each
    // node, or the children aren't equal, (child node length check has to be done so that the zip view matches the
    // children without error)
    if (not other) return false;
    if (child_nodes->size() != other->child_nodes->size()) return false;
    return ranges::zip_view(*child_nodes(), *other->child_nodes())
            | ranges::all_of([](node* child_of_this, node* child_of_other) {return child_of_this == child_of_other;});
}


auto dom::nodes::node::is_default_namespace(
        ext::string_view namespace_)
        -> ext::boolean
{
    // the namespace is the default namespace if it matches locating an empty namespace for this noed
    return namespace_ == detail::node_internals::locate_a_namespace(this, "");
}


auto dom::nodes::node::lookup_prefix(
        ext::string_view namespace_)
        -> ext::string
{
    // element node: return the lookup for the element
    if (auto* element_cast = dynamic_cast<element*>(this))
        return detail::node_internals::locate_a_namespace_prefix(element_cast, namespace_);

    // document node: return the lookup for the document element
    if (auto* document_cast = dynamic_cast<document*>(this))
        return detail::node_internals::locate_a_namespace_prefix(document_cast->document_element, namespace_);

    // document type node: return empty string
    if (auto* document_type_cast = dynamic_cast<document_type*>(this))
        return "";

    // document fragment: return empty string
    if (auto* document_fragment_cast = dynamic_cast<document_fragment*>(this))
        return "";

    // attribute node: return the lookup for the owner element
    if (auto* attribute_cast = dynamic_cast<attr*>(this))
        return detail::node_internals::locate_a_namespace_prefix(attribute_cast->owner_element(), namespace_);

    // default: return the lookup for the parent element if it exists, otherwise empty string
    return parent_element()
           ? detail::node_internals::locate_a_namespace_prefix(parent_element(), namespace_)
           : "";
}


auto dom::nodes::node::lookup_namespace_uri(
        ext::string_view prefix)
        -> ext::string
{
    // lookup the namespace with the prefix
    return detail::node_internals::locate_a_namespace(this, prefix);
}


auto dom::nodes::node::insert_before(
        node* new_node,
        node* child)
        -> node*
{
    // insert 'new_node' into 'this->child_nodes', directly before 'child' node
    ce_reaction_method_def {return detail::mutation_internals::pre_insert(new_node, this, child);};
    ce_reaction_method_exe
}


auto dom::nodes::node::append_child(
        node* new_node)
        -> node*
{
    // append 'new_node' to 'this->child_nodes', at the end
    ce_reaction_method_def {return detail::mutation_internals::append(new_node, this);};
    ce_reaction_method_exe
}


auto dom::nodes::node::replace_child(
        node* old_node,
        node* new_node)
        -> node*
{
    // replace 'old_node' with 'new_node' in 'this->child_nodes'
    ce_reaction_method_def {return detail::mutation_internals::replace(new_node, old_node, this);};
    ce_reaction_method_exe
}


auto dom::nodes::node::remove_child(
        node* old_node)
        -> node*
{
    // remove 'old_node' from 'this->child_nodes'
    ce_reaction_method_def {return detail::mutation_internals::pre_remove(old_node, this);};
    ce_reaction_method_exe
}


auto dom::nodes::node::get_previous_sibling() const -> node*
{
    auto* siblings = parent_node->child_nodes();
    auto* this_node_iter = std::ranges::find(*siblings, this);
    return this_node_iter != siblings->begin() ? *(this_node_iter - 1) : nullptr;
}


auto dom::nodes::node::get_next_sibling() const -> node*
{
    auto* siblings = parent_node->child_nodes();
    auto* this_node_iter = std::ranges::find(*siblings, this);
    return (this_node_iter + 1 != siblings->end()) ? *(this_node_iter + 1) : nullptr;
}


auto dom::nodes::node::get_parent_element() const -> element*
{
    auto* parent_as_node = parent_node();
    auto* parent_as_element = dynamic_cast<element*>(parent_as_node);
    return parent_as_element;
}


auto dom::nodes::node::set_parent_node(node* val) -> void
{
    if (parent_node())
        *parent_node->child_nodes() |= ranges::views::remove(this);

    *parent_node = std::unique_ptr<node>(val);
    parent_node->child_nodes->push_back(this);

    if (m_rendered_widget->isWidgetType())
    {
        auto* this_widget = qobject_cast<QWidget*>(m_rendered_widget);

        if (auto* new_parent_scroll_widget = qobject_cast<QScrollArea*>(val->to_qt()))
            new_parent_scroll_widget->setWidget(this_widget);

        else if (auto* new_parent_action_widget = qobject_cast<QWidgetAction*>(val->to_qt()))
            new_parent_action_widget->setDefaultWidget(this_widget);

        else if (auto* new_parent_widget = qobject_cast<QWidget*>(val->to_qt()))
            new_parent_widget->layout()->addWidget(this_widget);

        else
        {
            std::cerr << "Unknown render method for " << typeid(*val->to_qt()).name() << std::endl;
            return;
        }

        m_rendered_widget->show();
    }
}


auto dom::nodes::node::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<node>{isolate}
            .inherit<event_target>()
            .static_("DOCUMENT_POSITION_DISCONNECTED", node::DOCUMENT_POSITION_DISCONNECTED, true)
            .static_("DOCUMENT_POSITION_PRECEDING", node::DOCUMENT_POSITION_PRECEDING, true)
            .static_("DOCUMENT_POSITION_FOLLOWING", node::DOCUMENT_POSITION_FOLLOWING, true)
            .static_("DOCUMENT_POSITION_CONTAINS", node::DOCUMENT_POSITION_CONTAINS, true)
            .static_("DOCUMENT_POSITION_CONTAINED_BY", node::DOCUMENT_POSITION_CONTAINED_BY, true)
            .static_("DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC", node::DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC, true)
            .function("normalize", &node::normalize)
            .function("hasChildNodes", &node::has_child_nodes)
            .function("contains", &node::contains)
            .function("isEqualNode", &node::is_equal_node)
            .function("isDefaultNamespace", &node::is_default_namespace)
            .function("lookupPrefix", &node::lookup_prefix)
            .function("lookupNamespaceURI", &node::lookup_namespace_uri)
            .function("compareDocumentPosition", &node::compare_document_position)
            .function("getRootNode", &node::get_root_node)
            .function("cloneNode", &node::clone_node)
            .function("insertBefore", &node::insert_before)
            .function("appendChild", &node::append_child)
            .function("replaceChild", &node::replace_child)
            .function("removeChild", &node::remove_child)
            .var("nodeName", &node::node_name, true)
            .var("nodeValue", &node::node_value, false)
            .var("textContent", &node::text_content, false)
            .var("baseURI", &node::base_uri, true)
            .var("isConnected", &node::is_connected, true)
            .var("childNodes", &node::child_nodes, true)
            .var("parentNode", &node::parent_node, true)
            .var("parentElement", &node::parent_element, true)
            .var("ownerDocument", &node::owner_document, true)
            .var("firstChild", &node::first_child, true)
            .var("lastChild", &node::last_child, true)
            .var("previousSibling", &node::previous_sibling, true)
            .var("nextSibling", &node::next_sibling, true)
            .auto_wrap_objects();
}
