#include "element.hpp"

#include "ext/ranges.hpp"

#include "dom/detail/attribute_internals.hpp"
#include "dom/detail/customization_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/namespace_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/shadow_internals.hpp"

#include "dom/nodes/attr.hpp"
#include "dom/nodes/shadow_root.hpp"

#include <memory>

#include <QtCore/QPointer>
#include <QtWidgets/QWidget>

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view/transform.hpp>

#define attribute_to_name ranges::views::transform([](nodes::attr* attribute) {return attribute->name();});
#define attribute_to_nsln ranges::views::transform([](nodes::attr* attribute) {return std::make_tuple(attribute->local_name(), attribute->namespace_uri());});


dom::nodes::element::element()
        : shadow_root_node{nullptr}
        , attributes{std::make_unique<ext::vector<attr*>>()}
        , class_list{std::make_unique<ext::vector<ext::string>>()}
        , m_custom_element_reaction_queue{{}}
{
    bind_get(tag_name);
    bind_get(shadow_root_node);

    m_rendered_widget = QPointer<QWidget>{};
}


dom::nodes::element::~element()
{
    // attributes are created on the heap, and so need to be deleted after being used; use the std::default_delete
    // functor to delete each Attr pointer in the 'attributes' list
    ranges::for_each(*attributes(), std::default_delete<attr>{});
}


auto dom::nodes::element::has_attributes()
        const -> ext::boolean
{
    // return true if the 'attributes' list of this Element is not empty; ie it must contain 1+ Attr nodes. used as
    // syntactic sugar around accessing the attributes list, and also allows it to be bound to as a parameter to another
    // function
    return !attributes()->empty();
}


auto dom::nodes::element::get_attribute_names()
        const -> ranges::any_view<ext::string>
{
    // transform each Attr node in the 'attribute' list to its name, using a range-transform view adapter. return as an
    // `any_view` object for type erasure
    auto attribute_nodes = *attributes();
    auto attribute_names = attribute_nodes | attribute_to_name
    return attribute_names;
}


/* HAS ATTRIBUTE */


auto dom::nodes::element::has_attribute(
        ext::string_view name)
        const -> ext::boolean
{
    // transform each Attr node in the 'attribute' list to its name, using a range-transform view adapter. return if the
    // transformed range contains the 'name' parameter
    auto attribute_names = *attributes() | attribute_to_name;
    return ranges::contains(attribute_names, name);
}


auto dom::nodes::element::has_attribute_ns(
        ext::string_view namespace_,
        ext::string_view local_name)
        const -> ext::boolean
{
    // transform each Attr node in the 'attribute' list to its local name and namespace, using a range-transform view
    // adapter. return if the transformed range contains the 'local_nam' and 'namespace_' parameters
    auto attribute_namespaces = *attributes() | attribute_to_nsln;
    return ranges::contains(attribute_namespaces, std::make_tuple(namespace_, local_name));
}


auto dom::nodes::element::has_attribute_node(
        attr* attribute)
        const -> ext::boolean
{
    // return if the 'attribute' list contains the attribute, using a range-contains algorithm
    auto attribute_nodes = *attributes();
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
    auto match_attribute = get_attribute_node(qualified_name);
    return match_attribute ? match_attribute->value() : "";
}


auto dom::nodes::element::get_attribute_ns(
        ext::string_view namespace_,
        ext::string_view local_name)
        const -> ext::string
{
    // get the Attr node by the 'namespace_' and 'local_name', and return the value of the node; syntactic sugar for
    // 'get_attribute_node_ns(...).value'
    auto match_attribute = get_attribute_node_ns(namespace_, local_name);
    return match_attribute ? match_attribute->value() : "";
}


auto dom::nodes::element::get_attribute_node(
        ext::string_view qualified_name)
        const -> attr*
{
    // get the Attr node by matching each Attr (in the 'attributes' list) 's qualified name against the 'qualified_name'
    // parameter; nullptr is returned if there is no matching Attr node. the qualified name has to be html adjusted
    auto html_adjusted_qualified_name = detail::namespace_internals::html_adjust_string(qualified_name, detail::node_internals::is_html(this));
    auto match_algorithm = [html_adjusted_qualified_name](attr* attribute) {return attribute->name() == html_adjusted_qualified_name;};
    auto match_attribute = ranges::first_where(*attributes(), match_algorithm);
    return match_attribute;
}


auto dom::nodes::element::get_attribute_node_ns(
        ext::string_view namespace_,
        ext::string_view local_name)
        const -> attr*
{
    // get the Attr node by matching each Attr (in the 'attributes' list) 's local name and namespace_uri against the
    // 'local_name' and 'namespace_' parameters; nullptr is returned if there is no matching Attr node
    auto match_algorithm = [namespace_, local_name](attr* attribute) {return attribute->local_name() == local_name && attribute->namespace_uri() == namespace_;};
    auto match_attribute = ranges::first_where(*attributes(), match_algorithm);
    return match_attribute;
}


/* SET ATTRIBUTE */


auto dom::nodes::element::set_attribute(
        ext::string_view qualified_name,
        ext::string_view value)
        -> attr*
{
    ce_reactions_method_def
        // set the new Attr node by creating a new attribute with the 'qualified_name' and 'value', and set it to this
        // element; the internal method will handle replacing an existing attribute etc
        auto new_attribute = detail::attribute_internals::create(qualified_name, "", value, "", owner_document());
        return detail::attribute_internals::set_attribute(this, &new_attribute);
    ce_reactions_method_exe
}


auto dom::nodes::element::set_attribute_ns(
        ext::string_view namespace_,
        ext::string_view qualified_name,
        ext::string_view value)
        -> attr*
{
    ce_reactions_method_def
        // set the new Attr node by creating a new attribute with the 'local_name', 'prefix' and 'value', and set it to this
        // element; the internal method will handle replacing an existing attribute etc
        auto [prefix, local_name] = detail::namespace_internals::validate_and_extract(namespace_, qualified_name);
        auto new_attribute = detail::attribute_internals::create(local_name, namespace_, value, prefix, owner_document());
        return detail::attribute_internals::set_attribute(this, &new_attribute);
    ce_reactions_method_exe
}


auto dom::nodes::element::set_attribute_node(
        attr* attribute)
        -> attr*
{
    ce_reactions_method_def
        // set the new Attr node by calling the internal method to append this new attribute, or replace an existing
        // attribute - this handles replacing an existing attribute / appending the Attr to the 'attributes' list, and
        // changing the Attr value
        return detail::attribute_internals::set_attribute(this, attribute);
    ce_reactions_method_exe
}


auto dom::nodes::element::set_attribute_node_ns(
        attr* attribute)
        -> attr*
{
    ce_reactions_method_def
        // set the new Attr node by calling the internal method to append this new attribute, or replace an existing
        // attribute - this handles replacing an existing attribute / appending the Attr to the 'attributes' list, and
        // changing the Attr value
        return detail::attribute_internals::set_attribute(this, attribute);
    ce_reactions_method_exe
}


/* REMOVE ATTRIBUTE */


auto dom::nodes::element::remove_attribute(
        ext::string_view qualified_name)
        -> attr*
{
    ce_reactions_method_def
        // find the Attr node in this 'attributes' list by the 'qualified_name' that is going to be removed (can be nullptr
        // if the Attr doesn't exist in this Element), and remove it by calling the internal method
        auto* existing_attribute = get_attribute_node(qualified_name);
        return detail::attribute_internals::remove_attribute(this, existing_attribute);
    ce_reactions_method_exe
}


auto dom::nodes::element::remove_attribute_ns(
        ext::string_view namespace_,
        ext::string_view local_name)
        -> attr*
{
    ce_reactions_method_def
        // find the Attr node in this 'attributes' list by the 'local_name' and 'namespace_' that is going to be removed
        // (can be nullptr if the Attr doesn't exist in this Element), and remove it by calling the internal method
        auto* existing_attribute = get_attribute_node_ns(namespace_, local_name);
        return detail::attribute_internals::remove_attribute(this, existing_attribute);
    ce_reactions_method_exe
}


auto dom::nodes::element::remove_attribute_node(
        attr* attribute)
        -> attr*
{
    ce_reactions_method_def
        // remove the Attr node by calling the internal method to remove this Attr node - this handles the Attr value reset,
        // deletion, and removal from this 'attributes' list
        return detail::attribute_internals::remove_attribute(this, attribute);
    ce_reactions_method_exe
}


auto dom::nodes::element::remove_attribute_node_ns(
        attr* attribute)
        -> attr*
{
    ce_reactions_method_def
        // remove the Attr node by calling the internal method to remove this Attr node - this handles the Attr value reset,
        // deletion, and removal from this 'attributes' list
        return detail::attribute_internals::remove_attribute(this, attribute);
    ce_reactions_method_exe
}


/* TOGGLE ATTRIBUTE */


auto dom::nodes::element::toggle_attribute(
        ext::string_view qualified_name,
        ext::optional<ext::boolean> force)
        -> ext::boolean
{
    ce_reactions_method_def
        auto* existing_attribute = get_attribute_node(qualified_name);
        return detail::attribute_internals::toggle_attribute(this, existing_attribute, std::move(force), qualified_name);
    ce_reactions_method_exe
}


auto dom::nodes::element::toggle_attribute_ns(
        ext::string_view namespace_,
        ext::string_view local_name,
        ext::optional<ext::boolean> force)
        -> ext::boolean
{
    ce_reactions_method_def
        auto* existing_attribute = get_attribute_node_ns(namespace_, local_name);
        return detail::attribute_internals::toggle_attribute(this, existing_attribute, std::move(force), local_name, namespace_);
    ce_reactions_method_exe
}


auto dom::nodes::element::toggle_attribute_node(
        dom::nodes::attr* attribute,
        ext::optional<ext::boolean> force)
        -> attr*
{
    ce_reactions_method_def
        return_if(!attribute) static_cast<attr*>(nullptr);
        return detail::attribute_internals::toggle_attribute(this, attribute, std::move(force));
    ce_reactions_method_exe
}


auto dom::nodes::element::toggle_attribute_node_ns(
        dom::nodes::attr* attribute,
        ext::optional<ext::boolean> force)
        -> attr*
{
    ce_reactions_method_def
        return_if(!attribute) static_cast<attr*>(nullptr);
        return detail::attribute_internals::toggle_attribute(this, attribute, std::move(force));
    ce_reactions_method_exe
}


/* OTHER */


auto dom::nodes::element::attach_shadow(
        ext::map<ext::string, ext::any>&& options)
        -> shadow_root*
{
    using namespace detail::namespace_internals;

    ext::string shadow_attachable_local_names[] {"article", "aside", "blockquote", "body", "div", "footer", "h1", "h2", "h3", "h4", "h5", "h6", "header", "main", "nav", "p", "section", "span"};
    auto valid_custom = detail::customization_internals::is_valid_custom_element_name(local_name());
    auto valid_local  = ranges::contains(shadow_attachable_local_names, local_name());
    auto definition = detail::customization_internals::lookup_custom_element_definition(owner_document(), namespace_uri(), local_name(), m_is);

    detail::exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
            [this] {return namespace_uri() != HTML;});

    detail::exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
            [valid_local, valid_custom] {return !(valid_local || valid_custom);});

    detail::exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
            [valid_custom, definition] {return valid_custom && definition && definition->disable_shadow;});

    detail::exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
            [this] {return detail::shadow_internals::is_shadow_host(this);});

    auto* shadow = new shadow_root{};
    shadow->owner_document = owner_document();
    shadow->host = this;
    shadow->mode = options.try_emplace("mode", "").first->second.to<ext::string>();
    shadow->delegates_focus = options.try_emplace("delegatesFocus", ext::boolean::FALSE_()).first->second.to<ext::boolean>();
    shadow->slot_assignment = options.try_emplace("slotAssignment", "").first->second.to<ext::string>();
    shadow_root_node = shadow;
    return shadow;
}


#undef attribute_to_name
#undef attribute_to_nsln
