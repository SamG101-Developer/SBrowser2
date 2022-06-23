#ifndef SBROWSER2_ATTRIBUTE_INTERNALS_HPP
#define SBROWSER2_ATTRIBUTE_INTERNALS_HPP

#include <ext/type_traits.hpp>

#include <web_apis/dom/nodes/attr.hpp>
#include <web_apis/dom/nodes/element.hpp>
#include <web_apis/dom/nodes/shadow_root.hpp>
#include <web_apis/dom/detail/customization_internals.hpp>
#include <web_apis/dom/detail/exception_internals.hpp>
#include <web_apis/dom/detail/namespace_internals.hpp>
#include <web_apis/dom/detail/node_internals.hpp>
#include <web_apis/dom/detail/observer_internals.hpp>

#include <range/v3/view/remove.hpp>
#include <range/v3/view/replace.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/algorithm/find_if.hpp>


namespace dom::detail::attribute_internals
{
    // handle changes
    auto handle_attributes_changes(
            nodes::attr* attribute,
            nodes::element* owner_element,
            ext::string_view old_value,
            ext::string_view new_value)
            -> void;

    // general mutations to attributes
    auto change(
            nodes::attr* attribute,
            ext::string_view new_value)
            -> nodes::attr*;

    auto append(
            nodes::attr* attribute,
            nodes::element* new_owner_element)
            -> nodes::attr*;

    auto remove(
            nodes::attr* attribute)
            -> nodes::attr*;

    auto replace(
            nodes::attr* old_attribute,
            nodes::attr* new_attribute)
            -> nodes::attr*;

    auto create(
            ext::string_view local_name,
            ext::string_view namespace_ = "",
            ext::string_view value = "",
            ext::string_view prefix = "",
            nodes::document* owner_document = nullptr)
            -> nodes::attr*;

    // get attribute
    auto get_attribute_value(
            nodes::element* owner_element,
            ext::string_view local_name,
            ext::string_view namespace_)
            -> ext::string;

    auto get_attribute_by_name(
            nodes::element* owner_element,
            ext::string_view qualified_name)
            -> nodes::attr*;

    auto get_attribute_by_ns(
            nodes::element* owner_element,
            ext::string_view local_name,
            ext::string_view namespace_)
            -> nodes::attr*;

    // set attribute

    auto set_attribute_by_name(
            nodes::element* owner_element,
            ext::string_view qualified_name,
            ext::string_view value)
            -> nodes::attr*;

    auto set_attribute_by_ns(
            nodes::element* owner_element,
            ext::string_view qualified_name,
            ext::string_view namespace_,
            ext::string_view value)
            -> nodes::attr*;

    auto set_attribute(
            nodes::element* new_owner_element,
            nodes::attr* attribute)
            -> nodes::attr*;

    // remove attribute
    auto remove_attribute_by_name(
            nodes::element* owner_element,
            ext::string_view qualified_name)
            -> nodes::attr*;

    auto remove_attribute_by_ns(
            nodes::element* owner_element,
            ext::string_view local_name,
            ext::string_view namespace_)
            -> nodes::attr*;

    auto remove_attribute(
            nodes::element* owner_element,
            nodes::attr* attribute)
            -> nodes::attr*;

    // toggle attribute
    auto toggle_attribute_by_name(
            nodes::element* owner_element,
            ext::string_view qualified_name,
            ext::optional<ext::boolean> force)
            -> nodes::attr*;

    auto toggle_attribute_by_ns(
            nodes::element* owner_element,
            ext::string_view local_name,
            ext::string_view namespace_,
            ext::optional<ext::boolean> force)
            -> nodes::attr*;

    auto toggle_attribute(
            nodes::element* owner_element,
            nodes::attr* attribute,
            ext::optional<ext::boolean> force,
            ext::string_view qualified_name = "")
            -> nodes::attr*;

    // setter helpers
    auto set_existing_attribute_value(
            nodes::attr* attribute,
            ext::string_view value)
            -> void;
}


auto dom::detail::attribute_internals::handle_attributes_changes(
        nodes::attr* attribute,
        nodes::element* owner_element,
        ext::string_view old_value,
        ext::string_view new_value)
        -> void
{
    // get common variables
    auto local_name = attribute->local_name();
    auto namespace_ = attribute->namespace_uri();

    // queue a mutation record describing the change in the attribute
    observer_internals::queue_mutation_record("attributes", owner_element, local_name, namespace_, old_value, {}, {}, nullptr, nullptr);

    // if the element is custom, enqueue a custom element reaction
    if (owner_element->m_custom_element_state == customization_internals::CUSTOM)
        customization_internals::enqueue_custom_element_callback_reaction(owner_element, "attributeCallbackChanged", local_name, old_value, new_value, namespace_);

    // notify the node to execute its attribute-change behaviour steps
    owner_element->m_dom_behaviour.attribute_change_steps(local_name, old_value, new_value, namespace_);
}


auto dom::detail::attribute_internals::change(nodes::attr* attribute, ext::string_view new_value) -> nodes::attr*
{
    // handle the attribute changes, and set the attribute 'value' to 'new_value'
    handle_attributes_changes(attribute, attribute->owner_element(), attribute->value(), new_value);
    attribute->value = new_value;
    return attribute;
}


auto dom::detail::attribute_internals::append(nodes::attr* attribute, nodes::element* new_owner_element) -> nodes::attr*
{
    // handle the attribute changes, and set the attribute's 'owner_element' to 'new_owner_element', and append the
    // attribute to 'new_owner_element''s attribute list
    handle_attributes_changes(attribute, attribute->owner_element(), "", attribute->value());
    new_owner_element->attributes->push_back(attribute);
    attribute->owner_element = new_owner_element;
    return attribute;
}


auto dom::detail::attribute_internals::remove(nodes::attr* attribute) -> nodes::attr*
{
    // handle the attribute changes, remove 'attribute' from its 'owner_element', and set its 'owner_element' to nullptr
    handle_attributes_changes(attribute, attribute->owner_element(), attribute->value(), "");
    *attribute->owner_element->attributes() |= ranges::views::remove(attribute);
    return attribute;
}


auto dom::detail::attribute_internals::replace(nodes::attr* old_attribute, nodes::attr* new_attribute) -> nodes::attr*
{
    // handle the attribute changes, replace 'old_attribute' with 'new_attribute', switch the parent from
    // 'old_attribute' into 'new_attribute', and set the owner element of 'old_attribute' to nullptr
    handle_attributes_changes(old_attribute, old_attribute->owner_element(), old_attribute->value(), new_attribute->value());
    *old_attribute->owner_element->attributes() |= ranges::views::replace(old_attribute, new_attribute);
    new_attribute->owner_element = old_attribute->owner_element();
    old_attribute->owner_element = nullptr;
    return old_attribute;
}


auto dom::detail::attribute_internals::create(
        ext::string_view local_name, ext::string_view namespace_, ext::string_view value, ext::string_view prefix,
        nodes::document* owner_document) -> nodes::attr*
{
    // create the attribute and set all the attributes of it to the parameter values
    auto* attribute = new nodes::attr{};
    attribute->local_name = local_name;
    attribute->namespace_uri = namespace_;
    attribute->value = value;
    attribute->prefix = prefix;
    attribute->owner_document = owner_document;
    return attribute;
}


auto dom::detail::attribute_internals::get_attribute_value(
        nodes::element* owner_element, ext::string_view local_name, ext::string_view namespace_) -> ext::string
{
    // get the attribute by the 'namespace_', and return the value associated with the attribute
    auto* attribute = get_attribute_by_ns(owner_element, local_name, namespace_);
    return attribute->value();
}


auto dom::detail::attribute_internals::get_attribute_by_name(
        nodes::element* owner_element, ext::string_view qualified_name) -> nodes::attr*
{
    // the html qualified name must be lowercase for html documents, otherwise it is just the regular qualified name
    auto html_qualified_name = node_internals::is_html(owner_element)
            ? qualified_name | std::views::transform([](char character) {return std::tolower(character);}) | ranges::to<ext::string>
            : qualified_name;

    // get the first attribute that has the same name as the 'html_qualified_name'
    auto match_qualified_name = [html_qualified_name](nodes::attr* attribute) {return attribute->name() == html_qualified_name;};
    return *owner_element->attributes() | ranges::find_if(match_qualified_name);
}


auto dom::detail::attribute_internals::get_attribute_by_ns(
        nodes::element* owner_element, ext::string_view local_name, ext::string_view namespace_) -> nodes::attr*
{
    // get the first attribute that has the same 'local_name' and 'namespace_uri' as 'local_name' and 'namespace_'
    auto match_local_name_and_namespace = [local_name, namespace_](nodes::attr* attribute) {return attribute->local_name() == local_name && attribute->namespace_uri() == namespace_;};
    return *owner_element->attributes() | ranges::find_if(match_local_name_and_namespace);
}


auto dom::detail::attribute_internals::set_attribute_by_name(
        nodes::element* owner_element, ext::string_view qualified_name, ext::string_view value) -> nodes::attr*
{
    // get the attribute by matching 'qualified name', and set 'attribute'
    auto* attribute = create(qualified_name, "", value, "", owner_element->owner_document());
    set_attribute(owner_element, attribute);
    return attribute;
}


auto dom::detail::attribute_internals::set_attribute_by_ns(
        nodes::element* owner_element, ext::string_view qualified_name, ext::string_view namespace_, ext::string_view value) -> nodes::attr*
{
    auto [prefix, local_name] = namespace_internals::validate_and_extract(namespace_, qualified_name);

    // get the attribute by matching 'local_name' and 'namespace_', and set 'attribute'
    auto* attribute = create(local_name, namespace_, value, prefix, owner_element->owner_document());
    set_attribute(owner_element, attribute);
    return attribute;
}


auto dom::detail::attribute_internals::set_attribute(
        nodes::element* new_owner_element, nodes::attr* attribute) -> nodes::attr*
{
    // check that the attribute isn't being used by another element at the moment (can only be set to the element that
    // it is already in, or to a nullptr element)
    exception_internals::throw_v8_exception<INUSE_ATTRIBUTE_ERR>(
            "The Attribute node's owner_element must be either Null or equal to the new owner element (attribute is"
            "currently in use for another element node at the moment",
            [&attribute, &new_owner_element] {return attribute->owner_element() && attribute->owner_element() != new_owner_element;});

    // get the (possibly existing) attribute with the same local name and namespace as 'attribute', and either return
    // 'attribute' if the 'attribute' is the same attribute as 'old_attribute', replace the 'old_attribute' with
    // 'attribute', or append the new attribute to the new owner element
    auto* old_attribute = get_attribute_by_ns(new_owner_element, attribute->local_name(), attribute->namespace_uri());
    if (old_attribute == attribute) return attribute;
    if (old_attribute) replace(old_attribute, attribute);
    else
    {
        append(attribute, new_owner_element);
        change(attribute, attribute->value());
    }

    return old_attribute;
}


auto dom::detail::attribute_internals::remove_attribute_by_name(
        nodes::element* owner_element, ext::string_view qualified_name) -> nodes::attr*
{
    // get the attribute by matching 'qualified name', and remove 'attribute'
    auto* attribute = get_attribute_by_name(owner_element, qualified_name);
    remove_attribute(owner_element, attribute);
    return attribute;
}


auto dom::detail::attribute_internals::remove_attribute_by_ns(
        nodes::element* owner_element, ext::string_view local_name, ext::string_view namespace_) -> nodes::attr*
{
    // get the attribute by matching 'local_name' and 'namespace_', and remove 'attribute'
    auto* attribute = get_attribute_by_ns(owner_element, local_name, namespace_);
    remove_attribute(owner_element, attribute);
    return attribute;
}


auto dom::detail::attribute_internals::remove_attribute(
        nodes::element* owner_element, nodes::attr* attribute) -> dom::nodes::attr*
{
    // get the list of attributes, and change / remove the attribute if it exists
    auto* attributes = owner_element->attributes();
    if (*attributes | ranges::contains(attribute))
    {
        // change the value to "" (calls update methods), call the 'remove()' method (calls update methods), and then remove
        // the attribute from the list, before returning the attribute
        change(attribute, "");
        remove(attribute);
        *attributes |= ranges::views::remove(attribute);
    }

    return attribute;
}


auto dom::detail::attribute_internals::toggle_attribute_by_name(
        nodes::element* owner_element, ext::string_view qualified_name, ext::optional<ext::boolean> force) -> nodes::attr*
{
    // get the attribute by matching 'qualified name', and toggle 'attribute'
    auto* attribute = get_attribute_by_name(owner_element, qualified_name);
    toggle_attribute(owner_element, attribute, std::move(force));
    return attribute;
}


auto dom::detail::attribute_internals::toggle_attribute_by_ns(
        nodes::element* owner_element, ext::string_view local_name, ext::string_view namespace_, ext::optional<ext::boolean> force) -> nodes::attr*
{
    // get the attribute by matching 'local_name' and 'namespace_', and toggle 'attribute'
    auto* attribute = get_attribute_by_ns(owner_element, local_name, namespace_);
    toggle_attribute(owner_element, attribute, std::move(force));
    return attribute;
}


auto dom::detail::attribute_internals::toggle_attribute(
        nodes::element* owner_element, nodes::attr* attribute, ext::optional<ext::boolean> force, ext::string_view qualified_name) -> nodes::attr*
{
    // if there is an attribute being toggled on, or a null attribute being toggled off, do nothing and return the
    // attribute (which can be nullptr)
    if (attribute && force.value_or(false) || !attribute && !force.value_or(true))
        return attribute;

    // if there is an attribute, it is being toggled off (previous checks ensures this => remove the attribute)
    // if there is no attribute, it is being toggled on (previous check ensures this => create the attribute)
    attribute = attribute
            ? remove_attribute(owner_element, attribute) // toggle off
            : append(create(qualified_name, "", "", "", owner_element->owner_document()), owner_element); // toggle on

    return attribute;
}


auto dom::detail::attribute_internals::set_existing_attribute_value(
        nodes::attr* attribute, ext::string_view value) -> void
{
    // if there is not 'owner_element', then change the value normally (no need to call update methods), but if there is
    // an 'owner_element', then call the 'change(...)' method to call all the necessary updates
    !attribute->owner_element()
            ? static_cast<void>(attribute->value = value)
            : static_cast<void>(change(attribute, value));
}

#endif //SBROWSER2_ATTRIBUTE_INTERNALS_HPP
