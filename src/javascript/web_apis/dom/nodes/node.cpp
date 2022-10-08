#include "node.hpp"
#include "node_private.hpp"

#include "dom/_typedefs.hpp"
#include "ext/pimpl.hpp"
#include "ext/ranges.hpp"
#include "javascript/environment/realms_2.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/mutation_internals.hpp"
#include "dom/detail/range_internals.hpp"
#include "dom/detail/shadow_internals.hpp"
#include "dom/detail/text_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/mixins/slottable_private.hpp"
#include "dom/nodes/attr.hpp"
#include "dom/nodes/character_data.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_fragment.hpp"
#include "dom/nodes/document_type.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/node.hpp"
#include "dom/nodes/text.hpp"
#include "dom/ranges/range.hpp"

#include "file_api/detail/blob_internals.hpp"
#include "fullscreen/detail/fullscreen_internals.hpp"
#include "html/detail/document_internals.hpp"
#include "url/detail/url_internals.hpp"

#include <range/v3/to_container.hpp>
#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/algorithm/find.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/remove.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip.hpp>

namespace dom::nodes {class window;}


dom::nodes::node::node()
{
    INIT_PIMPL(node);
    ACCESS_PIMPL(node);

    d->get_the_parent =
            [this, d](events::event* event)
            {return detail::is_assigned(this) ? ext::cross_cast<mixins::slottable*>(this)->d_func()->assigned_slot : d->parent_node;};

    /* FULLSCREEN */
    d->remove_steps = [this, d](dom::nodes::node*)
    {
        using enum ranges::views::filter_compare_t;

        decltype(auto) document = d->node_document;
        auto nodes = detail::shadow_including_descendants(document)
                | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<element*>()
                | ranges::views::filter_eq<EQ>(&element::m_fullscreen_flag, true, ext::identity{});

        for (element* element: nodes)
        {
            if (document->d_func()->fullscreen_element == element)
                fullscreen::detail::fully_exit_fullscreen(document);
            else
                fullscreen::detail::unfullscreen_element(element);

            // TODO : layers
            // TODO : unloading document cleanup steps
        }
    };
}


auto dom::nodes::node::compare_document_position(
        node* other)
        -> ext::number<ushort>
{
    // if the nodes are the same then return 0 ie there is no comparison to be done
    if (this == other) return 0;

    // set the nodes to the other node and this node, and the attributes to nullptr (don't exist yet)
    decltype(auto) node_1 = other;
    decltype(auto) node_2 = this;
    decltype(auto) attr_1 = dynamic_cast<attr*>(node_1);
    decltype(auto) attr_2 = dynamic_cast<attr*>(node_2);

    // if the nodes are attributes, set the 'attr' variables, and the nodes to the attributes' owner elements
    node_1 = attr_1 ? attr_1->d_func()->element : node_1;
    node_2 = attr_2 ? attr_2->d_func()->element : node_2;

    // if both the nodes being compared are attributes of the same element, compare their position in the attribute list
    if (attr_1 && attr_2 && node_1 && node_1 == node_2)
    {
        for (decltype(auto) attr: dynamic_cast<element*>(node_2)->d_func()->attribute_list | ranges::views::transform(&std::unique_ptr<attr>::get))
        {
            if (attr == attr_1) return DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC | DOCUMENT_POSITION_PRECEDING;
            if (attr == attr_2) return DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC | DOCUMENT_POSITION_FOLLOWING;
        }
    }

    // the nodes are disconnected when a node is null, or they belong to different trees
    if (!node_1 or !node_2 || detail::root(node_1) != detail::root(node_2))
        return DOCUMENT_POSITION_DISCONNECTED | DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC | (node_1 < node_2 ? DOCUMENT_POSITION_PRECEDING : DOCUMENT_POSITION_FOLLOWING);

    // the other node contains this node, if it is an ancestor, and not an attribute node
    if (detail::is_ancestor(node_1, node_2) and !attr_1)
        return DOCUMENT_POSITION_CONTAINS | DOCUMENT_POSITION_PRECEDING;

    // the other node contains this node, if it is the owner element of this node (an attribute)
    if (node_1 == node_2 && attr_2)
        return DOCUMENT_POSITION_CONTAINS | DOCUMENT_POSITION_PRECEDING;

    // the other node is contained by this node, if it is a descendant, and not an attribute node
    if (detail::is_descendant(node_1, node_2) and !attr_2)
        return DOCUMENT_POSITION_CONTAINED_BY | DOCUMENT_POSITION_FOLLOWING;

    // the other node is contained by this node, if it is the attribute of this node (an element)
    if (node_1 == node_2 && attr_1)
        return DOCUMENT_POSITION_CONTAINED_BY | DOCUMENT_POSITION_FOLLOWING;

    // the other node is preceding this node if is comes before it in the tree, otherwise it is following it
    return detail::is_preceding(node_1, node_2) ? DOCUMENT_POSITION_PRECEDING : DOCUMENT_POSITION_FOLLOWING;
}


auto dom::nodes::node::get_root_node(
        ext::map<ext::string, ext::any>&& options)
        -> node*
{
    // get the shadow including root node if the 'composed' option is set, otherwise get the regular root of the node
    return options["composed"].to<ext::boolean>()
            ? detail::shadow_including_root(this)
            : detail::root(this);
}


auto dom::nodes::node::contains(
        node* other)
        -> ext::boolean
{
    // this node contains 'other' if 'other' is a descendant of this node
    return detail::is_descendant(other, this);
}


auto dom::nodes::node::has_child_nodes()
        -> ext::boolean
{
    // this node has child nodes if the 'child_nodes' list is not empty
    ACCESS_PIMPL(node);
    return !d->child_nodes.empty();
}


auto dom::nodes::node::normalize()
        -> node*
{
    CE_REACTIONS_METHOD_DEF
        for (nodes::text* text_node: detail::descendant_text_nodes(this))
        {
            // if the length of the text node (ie the length of the text) is 0 then remove the text node
            auto length = dom::detail::length(text_node);
            continue_if(length <= 0ul);

            // combine the text from the next consecutive text nodes into the text node
            auto data = dom::detail::contiguous_text_nodes(text_node)
                        | ranges::views::transform([](nodes::text* contiguous_text_node) {return contiguous_text_node->d_func()->data;})
                        | ranges::to<ext::string>();

            // replace the data in this node with the combined data from the contiguous nodes
            detail::replace_data(text_node, 0, length, data);

            // get the current node as the next text node (whose text has been combined into the text node's text)
            auto* current_node = text_node->next_sibling();

            JS_REALM_GET_SURROUNDING(this);
            auto live_ranges = javascript::environment::realms::get<ext::vector<node_ranges::range*>>(this_surrounding_global_object, "live_ranges");

            // iterate by incrementing the current_node to the next sibling
            while (detail::is_exclusive_text_node(current_node))
            {
                // ranges whose starting node is current_node: increment the starting offset by the length of the text of
                // the text node (text has shifted back to previous node) and set the starting node to the text node
                ranges::for_each(
                        live_ranges | ranges::views::filter([&current_node](node_ranges::range* range) {return range->d_func()->start->node == current_node;}),
                        [&text_node, length](node_ranges::range* range) {range->d_func()->start->offset = range->d_func()->start->offset + length; range->d_func()->start->node = text_node;});

                // ranges whose ending node is current_node: increment the ending offset by the length of the text of the
                // text node (text has shifted back to previous node) abd set the ending node to the text node
                ranges::for_each(
                       live_ranges | ranges::views::filter([&current_node](node_ranges::range* range) {return range->d_func()->end->node == current_node;}),
                       [&text_node, length](node_ranges::range* range) {range->d_func()->end->offset = range->d_func()->end->offset + length; range->d_func()->end->node = text_node;});

                // ranges whose starting node is current_node's parent: set the starting offset to the length of the text in
                // the text node and set the starting node to the text node TODO : why?
                ranges::for_each(
                        live_ranges | ranges::views::filter([&current_node](node_ranges::range* range) {return range->d_func()start->node == current_node->d_func()->parent_node;}),
                        [&text_node, length](node_ranges::range* range) {range->d_func()->start->offset = length; range->d_func()->start->node = text_node;});

                // ranges whose ending node is current_node's parent: set the ending offset to the length of the text in the
                // text node and set the ending node to the text node TODO : why?
                ranges::for_each(
                        live_ranges | ranges::views::filter([&current_node](node_ranges::range* range) {return range->d_func()->end->node == current_node->d_func()->parent_node;}),
                        [&text_node, length](node_ranges::range* range) {range->d_func()->end->offset = length; range->d_func()->end->node = text_node;});

                // increment the length by the current_node's length (so that the next current_node's offset can be
                // incremented further as needed to be, and set the current node to the next sibling
                length += detail::length(current_node);
                current_node = current_node->next_sibling();
            }

            ranges::for_each(
                    dom::detail::contiguous_text_nodes(text_node),
                    [](node* contiguous_text_node) {detail::remove(contiguous_text_node);});
        }

        return this; // TODO : what to return
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::node::clone_node(
        ext::boolean deep)
        -> std::unique_ptr<node>
{
    ACCESS_PIMPL(node);
    using enum detail::dom_exception_error_t;

    CE_REACTIONS_METHOD_DEF
        // throw an error if there is an attempt to clone a shadow node
        detail::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
                [this] {return detail::is_shadow_root(this);},
                "Cannot clone a ShadowRoot node");

        // clone the node and return it
        return std::move(detail::clone(this, nullptr, deep));
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::node::is_equal_node(
        node* other)
        -> ext::boolean
{
    // the nodes aren't equal if the other node is null, there are a different amount of child nodes belonging to each
    // node, or the children aren't equal, (child node length check has to be done so that the zip view matches the
    // children without error)
    ACCESS_PIMPL(node);

    if (not other) return false;
    if (d->child_nodes.size() != other->d_func()->child_nodes.size()) return false;
    return ranges::all_of(
            ranges::zip_view(d->child_nodes, other->d_func()->child_nodes),
            [](auto&& compare_children) {return compare_children.first == compare_children.second;});
}


auto dom::nodes::node::is_default_namespace(
        ext::string_view namespace_)
        -> ext::boolean
{
    // the namespace is the default namespace if it matches locating an empty namespace for this noed
    return namespace_ == detail::locate_a_namespace(this, "");
}


auto dom::nodes::node::lookup_prefix(
        ext::string_view namespace_)
        -> ext::string
{
    ACCESS_PIMPL(node);

    // element node: return the lookup for the element
    if (auto* element_cast = dynamic_cast<element*>(this))
        return detail::locate_a_namespace_prefix(element_cast, namespace_);

    // document node: return the lookup for the document element
    if (auto* document_cast = dynamic_cast<document*>(this))
        return detail::locate_a_namespace_prefix(document_cast->d_func()->document_element, namespace_);

    // document type node: return empty string
    if (auto* document_type_cast = dynamic_cast<document_type*>(this))
        return "";

    // document fragment: return empty string
    if (auto* document_fragment_cast = dynamic_cast<document_fragment*>(this))
        return "";

    // attribute node: return the lookup for the owner element
    if (auto* attribute_cast = dynamic_cast<attr*>(this))
        return detail::locate_a_namespace_prefix(attribute_cast->d_func()->element, namespace_);

    // default: return the lookup for the parent element if it exists, otherwise empty string
    return d->parent_element
           ? detail::locate_a_namespace_prefix(d->parent_element, namespace_)
           : "";
}


auto dom::nodes::node::lookup_namespace_uri(
        ext::string_view prefix)
        -> ext::string
{
    // lookup the namespace with the prefix
    return detail::locate_a_namespace(this, prefix);
}


auto dom::nodes::node::insert_before(
        std::unique_ptr<node>&& new_node,
        node* child)
        -> node*
{
    // insert 'new_node' into 'this->child_nodes', directly before 'child' node
    CE_REACTIONS_METHOD_DEF
        return detail::pre_insert(std::move(new_node), this, child);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::node::append_child(
        std::unique_ptr<node>&& new_node)
        -> node*
{
    // append 'new_node' to 'this->child_nodes', at the end
    CE_REACTIONS_METHOD_DEF
        return detail::append(std::move(new_node), this);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::node::replace_child(
        node* old_node,
        std::unique_ptr<node>&& new_node)
        -> node*
{
    // replace 'old_node' with 'new_node' in 'this->child_nodes'
    CE_REACTIONS_METHOD_DEF
        return detail::replace(std::move(new_node), old_node, this);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::node::remove_child(
        node* old_node)
        -> node*
{
    // remove 'old_node' from 'this->child_nodes'
    CE_REACTIONS_METHOD_DEF
        return detail::pre_remove(old_node, this);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::node::get_base_uri() const -> ext::string
{
    ACCESS_PIMPL(const node);
    return url::detail::url_serializer(html::detail::document_base_url(d->node_document));
}


auto dom::nodes::node::get_is_connected() const -> ext::boolean
{
    return detail::is_connected(this);
}


auto dom::nodes::node::get_child_nodes() const -> ranges::any_view<node*>
{
    ACCESS_PIMPL(const node);
    return d->child_nodes | ranges::views::transform([](auto&& child) {return child.get();});
}


auto dom::nodes::node::get_parent_node() const -> node*
{
    ACCESS_PIMPL(const node);
    return d->parent_node;
}


auto dom::nodes::node::get_parent_element() const -> element*
{
    ACCESS_PIMPL(const node);
    return dom_cast<element*>(d->parent_node);
}


auto dom::nodes::node::get_owner_document() const -> document*
{
    ACCESS_PIMPL(const node);
    return d->node_document;
}


auto dom::nodes::node::get_first_child() const -> node*
{
    return detail::first_child(this);
}


auto dom::nodes::node::get_last_child() const -> node*
{
    return detail::last_child(this);
}


auto dom::nodes::node::get_previous_sibling() const -> node*
{
    return detail::previous_sibling(this);
}


auto dom::nodes::node::get_next_sibling() const -> node*
{
    return detail::next_sibling(this);
}


auto dom::nodes::node::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<node>{isolate}
        .inherit<event_target>() // TODO : other static attributes
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
        .property("nodeType", &node::get_node_type)
        .property("nodeName", &node::get_node_name)
        .property("nodeValue", &node::get_node_value, &node::set_node_value)
        .property("textContent", &node::get_text_content, &node::set_text_content)
        .property("baseURI", &node::get_base_uri)
        .property("isConnected", &node::get_is_connected)
        .property("childNodes", &node::get_child_nodes)
        .property("parentNode", &node::get_parent_node)
        .property("parentElement", &node::get_parent_element)
        .property("ownerDocument", &node::get_owner_document)
        .property("firstChild", &node::get_first_child)
        .property("lastChild", &node::get_last_child)
        .property("previousSibling", &node::get_previous_sibling)
        .property("nextSibling", &node::get_next_sibling)
        .auto_wrap_objects();

    return std::move(conversion);
}
