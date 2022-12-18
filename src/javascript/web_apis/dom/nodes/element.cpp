module;
#include "ext/macros/custom_operator.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/errors.hpp"
#include "javascript/macros/expose.hpp"
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/transform.hpp>
#include <tl/optional.hpp>
#include <tuplet/tuple.hpp>


module apis.dom.element;
import apis.dom.element_private;
import apis.dom.attr;
import apis.dom.attr_private;
import apis.dom.shadow_root;
import apis.dom.shadow_root_private;
import apis.dom.detail;
import apis.dom.types;

import ext.any;
import ext.boolean;
import ext.casting;
import ext.functional;
import ext.map;
import ext.optional;
import ext.ranges;
import ext.string;
import ext.tuple;

import js.env.module_type;
import js.env.realms;
import js.env.slots;


dom::element::element()
{
    INIT_PIMPL; ACCESS_PIMPL;
    d->shadow_root = nullptr;
}


auto dom::element::has_attributes() const -> ext::boolean
{
    // Return true if the 'attributes' list of this Element is not empty; ie it must contain 1+ Attr node. Used as
    // syntactic sugar around accessing the attributes list, and also allows it to be bound to as a parameter to another
    // function.
    ACCESS_PIMPL;
    return !d->attribute_list.empty();
}


auto dom::element::get_attribute_names() const -> ranges::any_helpful_view<ext::string>
{
    // Transform each Attr node in the 'attribute' list to its name, using a range-transform view adapter. Return as an
    // `any_helpful_view` object for type erasure (no need to know the internal range-type workings).
    ACCESS_PIMPL;
    decltype(auto) attribute_nodes = d->attribute_list | ranges::views::transform(&std::unique_ptr<attr>::get);
    decltype(auto) attribute_names = attribute_nodes | ranges::views::transform(std::mem_fn(&attr_private::qualified_name));
    return attribute_names;
}


/* HAS ATTRIBUTE */


auto dom::element::has_attribute(
        ext::string_view name)
        const -> ext::boolean
{
    // Transform each Attr node in the 'attribute' list to its name, using a range-transform view adapter. Return if the
    // transformed range contains the 'name' parameter.
    ACCESS_PIMPL;
    decltype(auto) attribute_names = d->attribute_list | ranges::views::transform(std::mem_fn(&attr_private::qualified_name));
    return ranges::contains(attribute_names, name);
}


auto dom::element::has_attribute_ns(
        ext::string_view namespace_,
        ext::string_view local_name)
        const -> ext::boolean
{
    // Transform each Attr node in the 'attribute' list to its local name and namespace, using a range-transform view
    // adapter. Return if the transformed range contains the 'local_name' and 'namespace_' parameters.
    ACCESS_PIMPL;
    decltype(auto) attribute_namespaces = d->attribute_list
            | ranges::views::transform(&ext::underlying)
            | ranges::views::transform_to_attr(&attr_private::local_name, &attr_private::namespace_, ext::get_pimpl);

    return ranges::contains(attribute_namespaces, ext::make_tuple(namespace_, local_name));
}


auto dom::element::has_attribute_node(
        attr* attribute)
        const -> ext::boolean
{
    // return if the 'attribute' list contains the attribute, using a range-contains algorithm
    ACCESS_PIMPL;
    decltype(auto) attribute_nodes = d->attribute_list | ranges::views::transform(&std::unique_ptr<attr>::get);
    return ranges::contains(attribute_nodes, attribute);
}


auto dom::element::has_attribute_node_ns(
        attr* attribute)
        const -> ext::boolean
{
    // return if the 'attribute' list contains the attribute, using a range-contains algorithm - this is the same as the
    // 'has_attribute_node(...)' method
    return has_attribute_node(attribute);
}


/* GET ATTRIBUTE */


auto dom::element::get_attribute(
        ext::string_view qualified_name)
        const -> ext::string
{
    // get the Attr node by the 'qualified_name, and return the value of the node; syntactic sugar for
    // 'get_attribute_node(...).value'
    ACCESS_PIMPL;
    decltype(auto) match_attribute = get_attribute_node(qualified_name);
    return match_attribute ? match_attribute->d_func()->value : u"";
}


auto dom::element::get_attribute_ns(
        ext::string_view namespace_,
        ext::string_view local_name)
        const -> ext::string
{
    // get the Attr node by the 'namespace_' and 'local_name', and return the value of the node; syntactic sugar for
    // 'get_attribute_node_ns(...).value'
    decltype(auto) match_attribute = get_attribute_node_ns(namespace_, local_name);
    return match_attribute ? match_attribute->d_func()->value : u"";
}


auto dom::element::get_attribute_node(
        ext::string_view qualified_name)
        const -> attr*
{
    ACCESS_PIMPL;

    // get the Attr node by matching each Attr (in the 'attributes' list) 's qualified name against the 'qualified_name'
    // parameter; nullptr is returned if there is no matching Attr node. the qualified name has to be html adjusted
    decltype(auto) html_adjusted_qualified_name = detail::html_adjust_string(d->qualified_name(), d->is_html());
    decltype(auto) match_algorithm = [html_adjusted_qualified_name](attr* attribute) {return attribute->d_func()->qualified_name() == html_adjusted_qualified_name;};
    decltype(auto) match_attribute = *ranges::first_where(d->attribute_list | ranges::views::transform(ext::underlying), std::move(match_algorithm));
    return match_attribute;
}


auto dom::element::get_attribute_node_ns(
        ext::string_view namespace_,
        ext::string_view local_name)
        const -> attr*
{
    ACCESS_PIMPL;

    // get the Attr node by matching each Attr (in the 'attributes' list) 's local name and namespace_uri against the
    // 'local_name' and 'namespace_' parameters; nullptr is returned if there is no matching Attr node
    decltype(auto) match_algorithm = [namespace_, local_name](attr* attribute) {return attribute->d_func()->local_name == local_name && attribute->d_func()->namespace_ == namespace_;};
    decltype(auto) match_attribute = *ranges::first_where(d->attribute_list, match_algorithm);
    return match_attribute;
}


/* SET ATTRIBUTE */


auto dom::element::set_attribute(
        ext::string_view qualified_name,
        ext::string_view value)
        -> attr*
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;

        // set the new Attr node by creating a new attribute with the 'qualified_name' and 'value', and set it to this
        // element; the internal method will handle replacing an existing attribute etc
        decltype(auto) new_attribute = detail::create(qualified_name, u"", value, u"", d->node_document);
        return d->set_attribute(std::move(new_attribute));
    _CE_REACTIONS_METHOD_EXE
}


auto dom::element::set_attribute_ns(
        ext::string_view namespace_,
        ext::string_view qualified_name,
        ext::string_view value)
        -> attr*
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;

        // set the new Attr node by creating a new attribute with the 'local_name', 'prefix' and 'value', and set it to this
        // element; the internal method will handle replacing an existing attribute etc
        auto&& [prefix, local_name] = detail::validate_and_extract(namespace_, qualified_name);
        decltype(auto) new_attribute = detail::create(local_name, namespace_, value, prefix, d->node_document);
        return d->set_attribute(std::move(new_attribute));
    _CE_REACTIONS_METHOD_EXE
}


auto dom::element::set_attribute_node(
        std::unique_ptr<attr>&& attribute)
        -> attr*
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;

        // set the new Attr node by calling the internal method to append this new attribute, or replace an existing
        // attribute - this handles replacing an existing attribute / appending the Attr to the 'attributes' list, and
        // changing the Attr value
        return d->set_attribute(this, std::move(attribute));
    _CE_REACTIONS_METHOD_EXE
}


auto dom::element::set_attribute_node_ns(
        std::unique_ptr<attr>&& attribute)
        -> attr*
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;

        // set the new Attr node by calling the internal method to append this new attribute, or replace an existing
        // attribute - this handles replacing an existing attribute / appending the Attr to the 'attributes' list, and
        // changing the Attr value
        return d->set_attribute(std::move(attribute));
    _CE_REACTIONS_METHOD_EXE
}


/* REMOVE ATTRIBUTE */


auto dom::element::remove_attribute(
        ext::string_view qualified_name)
        -> attr*
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;

        // find the Attr node in this 'attributes' list by the 'qualified_name' that is going to be removed (can be nullptr
        // if the Attr doesn't exist in this Element), and remove it by calling the internal method
        decltype(auto) existing_attribute = get_attribute_node(qualified_name);
        return d->remove_attribute(existing_attribute);
    _CE_REACTIONS_METHOD_EXE
}


auto dom::element::remove_attribute_ns(
        ext::string_view namespace_,
        ext::string_view local_name)
        -> attr*
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;

        // find the Attr node in this 'attributes' list by the 'local_name' and 'namespace_' that is going to be removed
        // (can be nullptr if the Attr doesn't exist in this Element), and remove it by calling the internal method
        decltype(auto) existing_attribute = get_attribute_node_ns(namespace_, local_name);
        return d->remove_attribute(existing_attribute);
    _CE_REACTIONS_METHOD_EXE
}


auto dom::element::remove_attribute_node(
        attr* attribute)
        -> attr*
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;

        // remove the Attr node by calling the internal method to remove this Attr node - this handles the Attr value reset,
        // deletion, and removal from this 'attributes' list
        return d->remove_attribute(attribute);
    _CE_REACTIONS_METHOD_EXE
}


auto dom::element::remove_attribute_node_ns(
        attr* attribute)
        -> attr*
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;

        // remove the Attr node by calling the internal method to remove this Attr node - this handles the Attr value reset,
        // deletion, and removal from this 'attributes' list
        return d->remove_attribute(attribute);
    _CE_REACTIONS_METHOD_EXE
}


/* TOGGLE ATTRIBUTE */


auto dom::element::toggle_attribute(
        ext::string_view qualified_name,
        ext::optional<ext::boolean>&& force)
        -> ext::boolean
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        decltype(auto) attribute = get_attribute_node(qualified_name);
        return d->toggle_attribute(attribute, std::move(force), qualified_name);
    _CE_REACTIONS_METHOD_EXE
}


auto dom::element::toggle_attribute_ns(
        ext::string_view namespace_,
        ext::string_view local_name,
        ext::optional<ext::boolean>&& force)
        -> ext::boolean
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        decltype(auto) attribute = get_attribute_node_ns(namespace_, local_name);
        return d->toggle_attribute(attribute, std::move(force), local_name, namespace_);
    _CE_REACTIONS_METHOD_EXE
}


auto dom::element::toggle_attribute_node(
        attr* attribute,
        ext::optional<ext::boolean>&& force)
        -> attr*
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return_if (!attribute) ext::nullptr_cast<attr*>();
        return d->toggle_attribute(attribute, std::move(force));
    _CE_REACTIONS_METHOD_EXE
}


auto dom::element::toggle_attribute_node_ns(
        attr* attribute,
        ext::optional<ext::boolean>&& force)
        -> attr*
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return_if(!attribute) static_cast<attr*>(nullptr);
        return d->toggle_attribute(attribute, std::move(force));
    _CE_REACTIONS_METHOD_EXE
}


/* OTHER */


auto dom::element::attach_shadow(
        ext::map<ext::string, ext::any>&& options)
        -> std::unique_ptr<shadow_root>
{
    ACCESS_PIMPL;
    using enum dom::detail::dom_exception_error_t;

    auto shadow_attachable_local_names = {
        u"article", u"aside", u"blockquote", u"body", u"div", u"footer", u"h1", u"h2", u"h3", u"h4", u"h5",
        u"h6", u"header", u"main", u"nav", u"p", u"section", u"span"};

    auto valid_custom = detail::is_valid_custom_element_name(d->local_name);
    auto valid_local  = ranges::contains(shadow_attachable_local_names, d->local_name);
    auto definition = detail::lookup_custom_element_definition(d->node_document.get(), d->namespace_, d->local_name, d->is);

    detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d] {return d->namespace_ != detail::HTML;},
            u8"");

    detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [valid_local, valid_custom] {return !valid_local && !valid_custom;},
            u8"");

    detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [valid_custom, definition] {return valid_custom && definition && definition->disable_shadow;},
            u8"");

    detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [this] {return detail::is_shadow_host(this);},
            u8"");

    auto shadow = std::make_unique<shadow_root>();
    shadow->d_func()->node_document = d->node_document.get();
    shadow->d_func()->host = this;
    shadow->d_func()->mode = options[u"mode"].to<detail::shadow_root_mode_t>();
    shadow->d_func()->delegates_focus = options[u"delegatesFocus"].to<ext::boolean>();
    shadow->d_func()->slot_assignment = options[u"slotAssignment"].to<detail::slot_assignment_mode_t>();
    d->shadow_root = shadow.get();
    return shadow;
}


/* ACCESSORS */


auto dom::element::get_namespace_uri() const -> ext::string
{
    ACCESS_PIMPL;
    return d->namespace_;
}


auto dom::element::get_prefix() const -> ext::string
{
    ACCESS_PIMPL;
    return d->namespace_prefix;
}


auto dom::element::get_local_name() const -> ext::string
{
    ACCESS_PIMPL;
    return d->local_name;
}


auto dom::element::get_tag_name() const -> ext::string
{
    return detail::html_uppercase_qualified_name(this);
}


auto dom::element::get_class_list() const -> ext::vector<ext::string>
{
    ACCESS_PIMPL;
    return d->class_ | ranges::views::split_string(',') | ranges::to<ext::vector<ext::string>>; // TODO : live?
}


auto dom::element::get_class_name() const -> ext::string
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->class_;
    _CE_REACTIONS_METHOD_EXE
}


auto dom::element::get_slot() const -> ext::string
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->slot;
    _CE_REACTIONS_METHOD_EXE
}


auto dom::element::get_id() const -> ext::string
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->id;
    _CE_REACTIONS_METHOD_EXE
}


auto dom::element::get_shadow_root() const -> shadow_root*
{
    ACCESS_PIMPL;
    return d->shadow_root.get();
}


auto dom::element::get_attributes() const -> ranges::any_helpful_view<attr*>
{
    ACCESS_PIMPL;
    return d->attribute_list | ranges::views::transform(&std::unique_ptr<attr>::get);
}


/* [DOM_PARSING] */
auto dom::element::get_outer_html() const -> ext::string
{
    _CE_REACTIONS_DEF
        return dom_parsing::detail::fragment_serialize(this);
    _CE_REACTIONS_EXE
}


dom::element::set_outer_html(ext::string&& new_outer_html) -> ext::view_of_t<ext::string&&>
{
    _CE_REACTIONS_DEF
        ACCESS_PIMPL;
        decltype(auto) parent = d->parent_node.get();

        return_if (!parent);
        detail::throw_exception<NO_MODIFICATION_ALLOWED_ERR>(
                [parent] {return dom_cast<document*>(parent)},
                u8"Cannot set the outer HTML of a Document-parented Node");

        if (dom_cast<document_fragment*>(parent))
        {
            parent = std::make_unique<element>();
            parent->d_func()->body = local_name;
            parent->d_func()->namespace_uri = detail::namespaces::HTML;
            parent->d_func()->node_document = d->node_document;
        }

        auto fragment = dom_parser::detail::fragment_parse(std::move(new_outer_html), parent);
        return detail::replace(this, std::move(fragment), parent);
    _CE_REACTIONS_EXE
}
/* [DOM_PARSING] */


auto dom::element::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<node>()
        .inherit<child_node>()
        .inherit<document_or_element_node>()
        .inherit<non_document_type_child_node>()
        .inherit<parentable_node>()
        .inherit<slottable>()
        .inherit<aria::aria_mixin>()
        .inherit<css::css_web_animations::animatable>()
        .function("hasAttributes", &element::has_attributes)
        .function("getAttributeNames", &element::get_attribute_names)
        .function("hasAttribute", &element::has_attribute)
        .function("hasAttributeNS", &element::has_attribute_ns)
        .function("hasAttributeNode", &element::has_attribute_node)
        .function("hasAttributeNodeNS", &element::has_attribute_node_ns)
        .function("getAttribute", &element::get_attribute)
        .function("getAttributeNS", &element::get_attribute_ns)
        .function("getAttributeNode", &element::get_attribute_node)
        .function("getAttributeNodeNS", &element::get_attribute_node_ns)
        .function("setAttribute", &element::set_attribute)
        .function("setAttributeNS", &element::set_attribute_ns)
        .function("setAttributeNode", &element::set_attribute_node)
        .function("setAttributeNodeNS", &element::set_attribute_node_ns)
        .function("removeAttribute", &element::remove_attribute)
        .function("removeAttributeNS", &element::remove_attribute_ns)
        .function("removeAttributeNode", &element::remove_attribute_node)
        .function("removeAttributeNodeNS", &element::remove_attribute_node_ns)
        .function("toggleAttribute", &element::toggle_attribute)
        .function("toggleAttributeNS", &element::toggle_attribute_ns)
        .function("toggleAttributeNode", &element::toggle_attribute_node)
        .function("toggleAttributeNodeNS", &element::toggle_attribute_node_ns)
        .function("attachShadow", &element::attach_shadow)
        .function("closest", &element::closest)
        .function("matches", &element::matches)
        .property("namespaceURI", &element::get_namespace_uri)
        .property("prefix", &element::get_prefix)
        .property("localName", &element::get_local_name)
        .property("tagName", &element::get_tag_name)
        .property("classList", &element::get_class_list)
        .property("className", &element::get_class_name)
        .property("slot", &element::get_slot)
        .property("id", &element::get_id)
        .property("shadowRoot", &element::get_shadow_root)
        .property("attributes", &element::get_attributes)
        .auto_wrap_objects();

    V8_INTEROP_EXTEND_JS_OBJECT(ALL)
        .property("editContext", &element::get_edit_context);

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
