#include "attribute_internals.hpp"

#include "ext/type_traits.hpp"
#include "ext/ranges.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/namespace_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/observer_internals.hpp"

#include "dom/nodes/attr.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/shadow_root.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/action/remove.hpp>
#include <range/v3/view/view.hpp>


auto dom::detail::handle_attributes_changes(
        const nodes::attr* const attribute,
        nodes::element* const owner_element,
        ext::string_view old_value,
        ext::string_view new_value)
        -> void
{
    using detail::mutation_type_t;
    using detail::custom_element_state_t;

    // get common variables
    auto local_name = attribute->local_name();
    auto namespace_ = attribute->namespace_uri();

    // queue a mutation record describing the change in the attribute
    observer_internals::queue_mutation_record(mutation_type_t::ATTRIBUTES, owner_element, local_name, namespace_, old_value, {}, {}, nullptr, nullptr);

    // if the element is custom, enqueue a custom element reaction
    if (owner_element->m_custom_element_state == custom_element_state_t::CUSTOM)
        enqueue_custom_element_callback_reaction(owner_element, "attributeCallbackChanged", local_name, old_value, new_value, namespace_);

    // notify the node to execute its attribute-change behaviour steps
    owner_element->m_dom_behaviour.attribute_change_steps(local_name, old_value, new_value, namespace_);
}


auto dom::detail::change(
        nodes::attr* const attribute,
        ext::string_view new_value)
        -> nodes::attr*
{
    // handle the attribute changes, and set the attribute 'value' to 'new_value'
    handle_attributes_changes(attribute, attribute->owner_element(), attribute->value(), new_value);
    attribute->value = new_value;
    return attribute;
}


auto dom::detail::append(
        nodes::attr* const attribute,
        nodes::element* const new_owner_element)
        -> nodes::attr*
{
    // handle the attribute changes, and set the attribute's 'owner_element' to 'new_owner_element', and append the
    // attribute to 'new_owner_element''s attribute list
    handle_attributes_changes(attribute, attribute->owner_element(), "", attribute->value());
    new_owner_element->attributes()->push_back(attribute);
    attribute->owner_element = new_owner_element;
    return attribute;
}


auto dom::detail::remove(
        nodes::attr* attribute)
        -> nodes::attr*
{
    // handle the attribute changes, remove 'attribute' from its 'owner_element', and set its 'owner_element' to nullptr
    handle_attributes_changes(attribute, attribute->owner_element(), attribute->value(), "");
    *attribute->owner_element()->attributes() |= ranges::actions::remove(attribute);
    return attribute;
}


auto dom::detail::replace(
        nodes::attr* old_attribute,
        nodes::attr* new_attribute)
        -> nodes::attr*
{
    // handle the attribute changes, replace 'old_attribute' with 'new_attribute', switch the parent from
    // 'old_attribute' into 'new_attribute', and set the owner element of 'old_attribute' to nullptr
    handle_attributes_changes(old_attribute, old_attribute->owner_element(), old_attribute->value(), new_attribute->value());
    *old_attribute->owner_element()->attributes() |= ranges::actions::replace(old_attribute, new_attribute);
    new_attribute->owner_element = old_attribute->owner_element();
    old_attribute->owner_element = nullptr;
    return old_attribute;
}


auto dom::detail::create(
        ext::string_view local_name,
        ext::string_view namespace_,
        ext::string_view value,
        ext::string_view prefix,
        nodes::document* const owner_document)
        -> nodes::attr
{
    // create the attribute and set all the attributes of it to the parameter values
    nodes::attr attribute;
    attribute.local_name = local_name;
    attribute.namespace_uri = namespace_;
    attribute.owner_document = owner_document;
    attribute.prefix = prefix;
    attribute.value = value;
    return attribute;
}


auto dom::detail::set_attribute(
        nodes::element* const new_owner_element,
        nodes::attr* const attribute)
        -> nodes::attr*
{
    // check that the attribute isn't being used by another element at the moment (can only be set to the element that
    // it is already in, or to a nullptr element)
    exception_internals::throw_v8_exception_formatted<INUSE_ATTRIBUTE_ERR>(
            [&attribute, &new_owner_element] {return attribute->owner_element() && attribute->owner_element() != new_owner_element;},
            "The Attribute node's owner_element must be either Null or equal to the new owner element (attribute is"
            "currently in use for another element node at the moment");

    // get the (possibly existing) attribute with the same local name and namespace as 'attribute', and either return
    // 'attribute' if the 'attribute' is the same attribute as 'old_attribute', replace the 'old_attribute' with
    // 'attribute', or append the new attribute to the new owner element
    auto* const old_attribute = new_owner_element->get_attribute_node_ns(attribute->local_name(), attribute->namespace_uri());
    return_if (old_attribute == attribute) attribute;

    if (old_attribute)
        replace(old_attribute, attribute);
    else
    {
        append(attribute, new_owner_element);
        change(attribute, attribute->value());
    }

    return old_attribute;
}


auto dom::detail::remove_attribute(
        const nodes::element* const owner_element,
        nodes::attr* attribute)
        -> dom::nodes::attr*
{
    // get the list of attributes, and change / remove the attribute if it exists
    if (auto& attributes = *owner_element->attributes(); ranges::contains(attributes, attribute))
    {
        // change the value to "" (calls update methods), call the 'remove()' method (calls update methods), and then remove
        // the attribute from the list, before returning the attribute
        change(attribute, "");
        remove(attribute);
        attributes |= ranges::actions::remove(attribute);
    }

    return attribute;
}


auto dom::detail::toggle_attribute(
        nodes::element* const owner_element,
        nodes::attr* attribute,
        const ext::optional<ext::boolean> force,
        const ext::string_view qualified_name,
        const ext::string_view namespace_)
        -> nodes::attr*
{
    // if there is an attribute being toggled on, or a null attribute being toggled off, do nothing and return the
    // attribute (which can be nullptr)
    if (attribute && force.value_or(false) || !attribute && !force.value_or(true))
        return attribute;

    // if there is an attribute, it is being toggled off (previous checks ensures this => remove the attribute)
    // if there is no attribute, it is being toggled on (previous check ensures this => create the attribute)
    attribute = attribute
            ? remove_attribute(owner_element, attribute) // toggle off
            : append(&create(qualified_name, namespace_, "", "", owner_element->owner_document()), owner_element); // toggle on

    return attribute;
}


auto dom::detail::set_existing_attribute_value(
        nodes::attr* const attribute,
        ext::string_view value)
        -> void
{
    // if there is not 'owner_element', then change the value normally (no need to call update methods), but if there is
    // an 'owner_element', then call the 'change(...)' method to call all the necessary updates
    !attribute->owner_element()
            ? static_cast<void>(attribute->value = ext::string{value})
            : static_cast<void>(change(attribute, value));
}
