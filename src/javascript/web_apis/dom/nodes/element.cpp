#include "element.hpp"
#include "element_private.hpp"

#include "ext/pimpl.hpp"
#include "ext/ranges.hpp"

#include "dom/detail/attribute_internals.hpp"
#include "dom/detail/customization_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/namespace_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/shadow_internals.hpp"

#include "dom/nodes/attr.hpp"
#include "dom/nodes/shadow_root.hpp"

#include "html/detail/context_internals.hpp"
#include "file_api/detail/blob_internals.hpp"
#include "url/detail/url_internals.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view/transform.hpp>


dom::nodes::element::element()
{
    INIT_PIMPL(element);
    ACCESS_PIMPL(element);
    d->shadow_root = nullptr;
}


auto dom::nodes::element::has_attributes()
        const -> ext::boolean
{
    // return true if the 'attributes' list of this Element is not empty; ie it must contain 1+ Attr nodes. used as
    // syntactic sugar around accessing the attributes list, and also allows it to be bound to as a parameter to another
    // function
    ACCESS_PIMPL(const element);
    return !d->attribute_list.empty();
}


auto dom::nodes::element::get_attribute_names()
        const -> ranges::any_view<ext::string>
{
    // transform each Attr node in the 'attribute' list to its name, using a range-transform view adapter. return as an
    // `any_view` object for type erasure
    ACCESS_PIMPL(const element);
    auto attribute_nodes = d->attribute_list | ranges::views::transform(&std::unique_ptr<attr>::get);
    auto attribute_names = attribute_nodes | ranges::views::transform(&detail::qualified_name);
    return attribute_names;
}


/* HAS ATTRIBUTE */


auto dom::nodes::element::has_attribute(
        ext::string_view name)
        const -> ext::boolean
{
    // transform each Attr node in the 'attribute' list to its name, using a range-transform view adapter. return if the
    // transformed range contains the 'name' parameter
    ACCESS_PIMPL(const element);
    auto attribute_names = d->attribute_list | ranges::views::transform(&detail::qualified_name);
    return ranges::contains(attribute_names, name);
}


auto dom::nodes::element::has_attribute_ns(
        ext::string_view namespace_,
        ext::string_view local_name)
        const -> ext::boolean
{
    // transform each Attr node in the 'attribute' list to its local name and namespace, using a range-transform view
    // adapter. return if the transformed range contains the 'local_nam' and 'namespace_' parameters
    ACCESS_PIMPL(const element);
    auto attribute_namespaces = d->attribute_list
            | ranges::views::transform(&attr::d_func)
            | ranges::views::transform_to_attrs(&attr_private::local_name, &attr_private::namespace_);
    return ranges::contains(attribute_namespaces, ext::make_tuple(namespace_, local_name));
}


auto dom::nodes::element::has_attribute_node(
        attr* attribute)
        const -> ext::boolean
{
    // return if the 'attribute' list contains the attribute, using a range-contains algorithm
    ACCESS_PIMPL(const element);
    auto attribute_nodes = d->attribute_list | ranges::views::transform(&std::unique_ptr<attr>::get);
    return ranges::contains(attribute_nodes, attribute);
}


auto dom::nodes::element::has_attribute_node_ns(
        attr* attribute)
        const -> ext::boolean
{
    // return if the 'attribute' list contains the attribute, using a range-contains algorithm - this is the same as the
    // 'has_attribute_node(...)' method
    return has_attribute_node(attribute);
}


/* GET ATTRIBUTE */


auto dom::nodes::element::get_attribute(
        ext::string_view qualified_name)
        const -> ext::string
{
    // get the Attr node by the 'qualified_name, and return the value of the node; syntactic sugar for
    // 'get_attribute_node(...).value'
    ACCESS_PIMPL(const element);
    decltype(auto) match_attribute = get_attribute_node(qualified_name);
    return match_attribute ? match_attribute->d->value : "";
}


auto dom::nodes::element::get_attribute_ns(
        ext::string_view namespace_,
        ext::string_view local_name)
        const -> ext::string
{
    // get the Attr node by the 'namespace_' and 'local_name', and return the value of the node; syntactic sugar for
    // 'get_attribute_node_ns(...).value'
    decltype(auto) match_attribute = get_attribute_node_ns(namespace_, local_name);
    return match_attribute ? match_attribute->d_func()->value : "";
}


auto dom::nodes::element::get_attribute_node(
        ext::string_view qualified_name)
        const -> attr*
{
    // get the Attr node by matching each Attr (in the 'attributes' list) 's qualified name against the 'qualified_name'
    // parameter; nullptr is returned if there is no matching Attr node. the qualified name has to be html adjusted
    ACCESS_PIMPL(const element);
    decltype(auto) html_adjusted_qualified_name = detail::html_adjust_string(detail::qualified_name(this), detail::is_html(this));
    decltype(auto) match_algorithm = [html_adjusted_qualified_name](attr* attribute) {return detail::qualified_name(attribute) == html_adjusted_qualified_name;};
    decltype(auto) match_attribute = *ranges::first_where(d->attribute_list | ranges::views::transform(&std::unique_ptr<attr>::get), std::move(match_algorithm));
    return match_attribute;
}


auto dom::nodes::element::get_attribute_node_ns(
        ext::string_view namespace_,
        ext::string_view local_name)
        const -> attr*
{
    // get the Attr node by matching each Attr (in the 'attributes' list) 's local name and namespace_uri against the
    // 'local_name' and 'namespace_' parameters; nullptr is returned if there is no matching Attr node
    decltype(auto) match_algorithm = [namespace_, local_name](attr* attribute) {return attribute->d_func()->local_name == local_name && attribute->d_func()->namespace_ == namespace_;};
    decltype(auto) match_attribute = *ranges::first_where(*attributes(), match_algorithm);
    return match_attribute;
}


/* SET ATTRIBUTE */


auto dom::nodes::element::set_attribute(
        ext::string_view qualified_name,
        ext::string_view value)
        -> attr*
{
    CE_REACTIONS_METHOD_DEF
        // set the new Attr node by creating a new attribute with the 'qualified_name' and 'value', and set it to this
        // element; the internal method will handle replacing an existing attribute etc
        decltype(auto) new_attribute = detail::create(qualified_name, "", value, "", owner_document());
        return detail::set_attribute(this, &new_attribute);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::element::set_attribute_ns(
        ext::string_view namespace_,
        ext::string_view qualified_name,
        ext::string_view value)
        -> attr*
{
    CE_REACTIONS_METHOD_DEF
        // set the new Attr node by creating a new attribute with the 'local_name', 'prefix' and 'value', and set it to this
        // element; the internal method will handle replacing an existing attribute etc
        decltype(auto) [prefix, local_name] = detail::validate_and_extract(namespace_, qualified_name);
        decltype(auto) new_attribute = detail::create(local_name, namespace_, value, prefix, owner_document());
        return detail::set_attribute(this, &new_attribute);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::element::set_attribute_node(
        attr* attribute)
        -> attr*
{
    CE_REACTIONS_METHOD_DEF
        // set the new Attr node by calling the internal method to append this new attribute, or replace an existing
        // attribute - this handles replacing an existing attribute / appending the Attr to the 'attributes' list, and
        // changing the Attr value
        return detail::set_attribute(this, attribute);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::element::set_attribute_node_ns(
        attr* attribute)
        -> attr*
{
    CE_REACTIONS_METHOD_DEF
        // set the new Attr node by calling the internal method to append this new attribute, or replace an existing
        // attribute - this handles replacing an existing attribute / appending the Attr to the 'attributes' list, and
        // changing the Attr value
        return detail::set_attribute(this, attribute);
    CE_REACTIONS_METHOD_EXE
}


/* REMOVE ATTRIBUTE */


auto dom::nodes::element::remove_attribute(
        ext::string_view qualified_name)
        -> attr*
{
    CE_REACTIONS_METHOD_DEF
        // find the Attr node in this 'attributes' list by the 'qualified_name' that is going to be removed (can be nullptr
        // if the Attr doesn't exist in this Element), and remove it by calling the internal method
        decltype(auto) existing_attribute = get_attribute_node(qualified_name);
        return detail::remove_attribute(this, existing_attribute);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::element::remove_attribute_ns(
        ext::string_view namespace_,
        ext::string_view local_name)
        -> attr*
{
    CE_REACTIONS_METHOD_DEF
        // find the Attr node in this 'attributes' list by the 'local_name' and 'namespace_' that is going to be removed
        // (can be nullptr if the Attr doesn't exist in this Element), and remove it by calling the internal method
        decltype(auto) existing_attribute = get_attribute_node_ns(namespace_, local_name);
        return detail::remove_attribute(this, existing_attribute);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::element::remove_attribute_node(
        attr* attribute)
        -> attr*
{
    CE_REACTIONS_METHOD_DEF
        // remove the Attr node by calling the internal method to remove this Attr node - this handles the Attr value reset,
        // deletion, and removal from this 'attributes' list
        return detail::remove_attribute(this, attribute);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::element::remove_attribute_node_ns(
        attr* attribute)
        -> attr*
{
    CE_REACTIONS_METHOD_DEF
        // remove the Attr node by calling the internal method to remove this Attr node - this handles the Attr value reset,
        // deletion, and removal from this 'attributes' list
        return detail::remove_attribute(this, attribute);
    CE_REACTIONS_METHOD_EXE
}


/* TOGGLE ATTRIBUTE */


auto dom::nodes::element::toggle_attribute(
        ext::string_view qualified_name,
        ext::optional<ext::boolean>&& force)
        -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        decltype(auto) existing_attribute = get_attribute_node(qualified_name);
        return detail::toggle_attribute(this, existing_attribute, std::move(force), qualified_name);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::element::toggle_attribute_ns(
        ext::string_view namespace_,
        ext::string_view local_name,
        ext::optional<ext::boolean>&& force)
        -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        decltype(auto) existing_attribute = get_attribute_node_ns(namespace_, local_name);
        return detail::toggle_attribute(this, existing_attribute, std::move(force), local_name, namespace_);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::element::toggle_attribute_node(
        attr* attribute,
        ext::optional<ext::boolean>&& force)
        -> attr*
{
    CE_REACTIONS_METHOD_DEF
        return_if (!attribute) ext::nullptr_cast<attr*>();
        return detail::toggle_attribute(this, attribute, std::move(force));
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::element::toggle_attribute_node_ns(
        attr* attribute,
        ext::optional<ext::boolean>&& force)
        -> attr*
{
    CE_REACTIONS_METHOD_DEF
        return_if(!attribute) static_cast<attr*>(nullptr);
        return detail::toggle_attribute(this, attribute, std::move(force));
    CE_REACTIONS_METHOD_EXE
}


/* OTHER */


auto dom::nodes::element::attach_shadow(
        ext::map<ext::string, ext::any>&& options)
        -> shadow_root
{
    using namespace detail;

    auto shadow_attachable_local_names = {
        "article", "aside", "blockquote", "body", "div", "footer", "h1", "h2", "h3", "h4", "h5", "h6", "header", "main",
        "nav", "p", "section", "span"};

    auto valid_custom = detail::is_valid_custom_element_name(local_name());
    auto valid_local  = ranges::contains(shadow_attachable_local_names, local_name());
    decltype(auto) definition = detail::lookup_custom_element_definition(owner_document(), namespace_uri(), local_name(), m_is);

    detail::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
            [this] {return namespace_uri() != HTML;});

    detail::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
            [valid_local, valid_custom] {return !(valid_local || valid_custom);});

    detail::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
            [valid_custom, definition] {return valid_custom && definition && definition->disable_shadow;});

    detail::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
            [this] {return detail::is_shadow_host(this);});

    shadow_root shadow {};
    shadow.owner_document = owner_document();
    shadow.host = this;
    shadow.mode = options.try_emplace("mode", "").first->second.to<ext::string>();
    shadow.delegates_focus = options.try_emplace("delegatesFocus", ext::boolean::FALSE_()).first->second.to<ext::boolean>();
    shadow.slot_assignment = options.try_emplace("slotAssignment", "").first->second.to<ext::string>();
    shadow_root_node = &shadow;
    return shadow;
}


/* ACCESSORS */


auto dom::nodes::element::get_namespace_uri() const -> ext::string
{
    ACCESS_PIMPL(const element);
    return d->namespace_;
}


auto dom::nodes::element::get_prefix() const -> ext::string
{
    ACCESS_PIMPL(const element);
    return d->namespace_prefix;
}


auto dom::nodes::element::get_local_name() const -> ext::string
{
    ACCESS_PIMPL(const element);
    return d->local_name;
}


auto dom::nodes::element::get_tag_name() const -> ext::string
{
    return detail::html_uppercase_qualified_name(this);
}


auto dom::nodes::element::get_class_list() const -> ext::vector<ext::string>
{
    ACCESS_PIMPL(const element);
    return d->class_ | ranges::views::split_string(',') | ranges::to<ext::vector<ext::string>>;
}


auto dom::nodes::element::get_class_name() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const element);
        return d->class_;
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::element::get_slot() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const element);
        return d->slot;
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::element::get_id() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const element);
        return d->id;
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::element::get_shadow_root() const -> nodes::shadow_root*
{
    ACCESS_PIMPL(const element);
    return d->shadow_root;
}


auto dom::nodes::element::get_attributes() const -> ext::vector_span<attr*>
{
    ACCESS_PIMPL(const element);
    return d->attribute_list
}
