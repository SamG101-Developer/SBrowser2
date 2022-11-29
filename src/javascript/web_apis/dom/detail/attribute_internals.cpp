#include "attribute_internals.hpp"

#include "ext/type_traits.hpp"
#include "ext/ranges.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/namespace_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/observer_internals.hpp"

#include "dom/nodes/attr.hpp"
#include "dom/nodes/attr_private.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/element_private.hpp"
#include "dom/nodes/shadow_root.hpp"
#include "dom/nodes/shadow_root_private.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/action/remove.hpp>
#include <range/v3/view/view.hpp>

#include <QWidget>


auto dom::detail::handle_attributes_changes(
        const nodes::attr* const attribute,
        nodes::element* owner_element,
        ext::string_view old_value,
        ext::string_view new_value)
        -> void
{
    using detail::mutation_type_t;
    using detail::custom_element_state_t;

    // Get the common variables required for the method, stored as string views to avoid an unnecessary copy.
    auto local_name = attribute->d_func()->local_name;
    auto namespace_ = attribute->d_func()->namespace_;

    // Queue a mutation record describing the change in the attribute. Pass the 'owner_element', 'local_name',
    // 'namespace_', and 'old_value' in.
    queue_mutation_record(
            mutation_type_t::ATTRIBUTES, owner_element,
            local_name, namespace_, old_value,
            {}, {}, nullptr, nullptr);

    // If the element is custom, enqueue a custom element reaction, so that the callback relateding to attrribute
    // changes can exeucute. Most of the same parameters as the 'queue_mutation_record(...)' call are used.
    if (owner_element->d_func()->custom_element_state == custom_element_state_t::CUSTOM)
        enqueue_custom_element_callback_reaction(owner_element, u"attributeCallbackChanged", local_name, old_value, new_value, namespace_);

    // Notify the node to execute its attribute-change behaviour steps
    owner_element->d_func()->attribute_change_steps(local_name, old_value, new_value, namespace_);
}


auto dom::detail::change(
        nodes::attr* const attribute,
        ext::string&& new_value)
        -> nodes::attr*
{
    // Handle the attribute changes. Set the 'attribute's value to the 'new_value'. Return the attribute that has just
    // been changed.
    handle_attributes_changes(attribute, attribute->d_func()->element, attribute->d_func()->value, new_value);
    attribute->d_func()->value = std::move(new_value);
    return attribute;
}


auto dom::detail::append(
        std::unique_ptr<nodes::attr>&& attribute,
        nodes::element* const new_owner_element)
        -> nodes::attr*
{
    // Handle the attribute changes. Set the attribute's 'owner_element' to 'new_owner_element', and append the
    // attribute to 'new_owner_element's attribute list. Return the underlying pointer to the new attribute, whose
    // unique_ptr<attr> has been moved into the 'new_owner_element's attribute list.
    handle_attributes_changes(attribute.get(), attribute->d_func()->element, u"", attribute->d_func()->value);
    new_owner_element->d_func()->attribute_list.push_back(std::move(attribute));
    attribute->d_func()->element = new_owner_element;
    return attribute.get();
}


auto dom::detail::remove(
        nodes::attr* attribute)
        -> std::unique_ptr<nodes::attr>
{
    // Handle the attribute changes. Remove 'attribute' from its owner element, and set its owner element to nullptr.
    // Return the attribute that has just been removed. Return a unique_ptr, because the ownership of the attr is
    // changing, ie it has been detached from the owner element.
    handle_attributes_changes(attribute, attribute->d_func()->element, attribute->d_func()->value, u"");
    auto unique_ptr_attribute = ranges::find(attribute->d_func()->element->d_func()->attribute_list, attribute, ext::underlying);
    attribute->d_func()->element->d_func()->attribute_list |= ranges::actions::remove(attribute, ext::underlying);
    return std::move(*unique_ptr_attribute);
}


auto dom::detail::replace(
        nodes::attr* old_attribute,
        std::unique_ptr<nodes::attr>&& new_attribute)
        -> nodes::attr*
{
    // Handle attribute changes. Replace the 'old_attribute' in the owner element's attribute list with the
    // 'new_attribute'. New attribute is a unique_ptr<attr>, as the ownership of the attribute is changing from the
    // 'old_attribute' to the 'new_attribute'. Set the 'new_attributes's owner element to the 'old_attributes' owner
    // element, and set the 'old_attribute's owner element to nullptr. Return the 'old_attribute'.
    handle_attributes_changes(old_attribute, old_attribute->d_func()->element, old_attribute->d_func()->value, new_attribute->d_func()->value);
    old_attribute->d_func()->element->d_func()->attribute_list |= ranges::actions::replace(old_attribute, std::move(new_attribute), ext::underlying);
    new_attribute->d_func()->element = old_attribute->d_func()->element;
    old_attribute->d_func()->element = nullptr;
    return old_attribute;
}


auto dom::detail::create(
        ext::string&& local_name,
        ext::string&& namespace_,
        ext::string&& value,
        ext::string&& prefix,
        nodes::document* const owner_document)
        -> std::unique_ptr<nodes::attr>
{
    // Create the attribute and set all the attributes of it to the parameter values (moved). Return the
    // unique_ptr<attr> attribute.
    auto attribute = std::make_unique<nodes::attr>();
    attribute.d_func()->local_name = std::move(local_name);
    attribute.d_func()->namespace_ = std::move(namespace_);
    attribute.d_func()->namespace_prefix = std::move(prefix);
    attribute.d_func()->value = std::move(value);
    attribute.d_func()->node_document = owner_document;
    return std::move(attribute);
}


auto dom::detail::set_attribute(
        nodes::element* const new_owner_element,
        std::unique_ptr<nodes::attr> attribute)
        -> nodes::attr*
{
    using enum dom::detail::dom_exception_error_t;

    // Check that the attribute isn't being used by another element at the moment (can only be set to the element that
    // it is already in, or to a nullptr element).
    throw_v8_exception<INUSE_ATTRIBUTE_ERR>(
            [&new_owner_element, attribute = attribute.get()]
            {return attribute->d_func()->element && attribute->d_func()->element.get() != new_owner_element;},
            u8"The Attribute node's owner_element must be either Null or equal to the new owner element (attribute is"
            u8"currently in use for another element node at the moment");

    // Get the (possibly existing) attribute with the same local name and namespace as 'attribute'. Return the
    // underlying attribute pointer in 'attribute' if the 'attribute' is the same attribute as 'old_attribute'.
    decltype(auto) old_attribute = new_owner_element->get_attribute_node_ns(attribute->d_func()->local_name, attribute->d_func()->namespace_);
    return_if (old_attribute == attribute.get()) attribute.get();

    // If there is an old attribute found (same namespace etc as 'attribute'), but it isn't the same Attr object as
    // 'attribute', then replace the 'old_attribute' with 'attribute'. Otherwise, the 'old_attribute' isn't the same
    // Attr object as the 'attribute', so append the 'attribute' into the 'new_owner_element', and change the
    // 'attribute' to the attribute's value (just to handle attribute changes / callbacks etc in the
    // 'new_owner_element')
    if (old_attribute)
        replace(old_attribute, std::move(attribute));
    else
    {
        append(std::move(attribute), new_owner_element);
        change(attribute.get(), std::move(attribute->d_func()->value));
    }

    // Return the 'old_attribute'.
    return old_attribute;
}


auto dom::detail::remove_attribute(
        const nodes::element* const owner_element,
        nodes::attr* attribute)
        -> dom::nodes::attr*
{
    // Get the list of current attributes in the 'owner_element', and check if the 'attribute' is contained in the
    // attribute list. If it is contained, process with the rest of the steps, otherwise return the 'attribute' straight
    // away.
    if (ranges::contains(owner_element->d_func()->attribute_list, attribute, ext::underlying))
    {
        // Change the value to "" (calls update methods), and then call the 'remove()' method (calls update methods).
        // Remove the attribute from the list, and then return the removed attribute.
        change(attribute, u"");
        remove(attribute);
        owner_element->d_func()->attribute_list |= ranges::actions::remove(attribute, ext::underlying);
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
    // If there is a valid attribute being toggled on, or a null attribute being toggled off, do nothing and return the
    // attribute (which can be nullptr). This is because a valid attribute being toggled on has no effect, and an
    // invalid (or null) attribute being toggled off has no effect either.
    if (attribute && force.value_or(false) || !attribute && !force.value_or(true))
        return attribute;

    // If there is an attribute, it is being toggled off (previous checks ensures this => remove the attribute)
    // If there is no attribute, it is being toggled on  (previous checks ensures this => create & append the attribute)
    attribute = attribute
            ? remove_attribute(owner_element, attribute)
            : append(create(qualified_name.data(), namespace_.data(), u"", u"", owner_element->d_func()->node_document.get()), owner_element);

    return attribute;
}


auto dom::detail::set_existing_attribute_value(
        nodes::attr* const attribute,
        ext::string&& value)
        -> void
{
    // If the 'attribute' doesn't have an owner element, then change the value normally (no need to call update
    // methods), but if there is an 'owner_element', then call the 'change(...)' method to call all the necessary
    // updates. This is because the update emthods require an owner element to have any effect at all.
    !attribute->d_func()->element
            ? attribute->d_func()->value = std::move(value)
            : change(attribute, std::move(value));
}


auto dom::detail::qualified_name(
        const nodes::attr* attribute)
        -> ext::string
{
    // The qualified name of an attribute is the 'attribute's prefix followed by a ":", followed by the 'attribute's
    // local name.
    return attribute->d_func()->namespace_prefix + u":" + attribute->d_func()->local_name;
}
