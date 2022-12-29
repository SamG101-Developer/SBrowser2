module;
#include "ext/macros/language_shorthand.hpp"
#include "ext/macros/macros.hpp"
#include <memory>
#include <tl/optional.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/action/remove.hpp>


module apis.dom.element_private;
import apis.dom.attr;
import apis.dom.detail;
import apis.dom.types;

import ext.core;


auto dom::element_private::set_attribute(std::unique_ptr<attr>&& attribute) -> attr*
{
    ACCESS_QIMPL;
    using enum detail::dom_exception_error_t;

    // Check that the attribute isn't being used by another element at the moment (can only be set to the element that
    // it is already in, or to a nullptr element).
    detail::throw_v8_exception<INUSE_ATTRIBUTE_ERR>(
            [q, attribute = attribute.get()] {return attribute->d_func()->element && attribute->d_func()->element.get() != q;},
            u8"The Attribute node's owner_element must be either Null or equal to the new owner element (attribute is"
            u8"currently in use for another element node at the moment");

    // Get the (possibly existing) attribute with the same local name and namespace as 'attribute'. Return the
    // underlying attribute pointer in 'attribute' if the 'attribute' is the same attribute as 'old_attribute'.
    decltype(auto) old_attribute = q->get_attribute_node_ns(attribute->d_func()->local_name, attribute->d_func()->namespace_);
    return_if (old_attribute == attribute.get()) attribute.get();

    // If there is an old attribute found (same namespace etc as 'attribute'), but it isn't the same Attr object as
    // 'attribute', then replace the 'old_attribute' with 'attribute'. Otherwise, the 'old_attribute' isn't the same
    // Attr object as the 'attribute', so append the 'attribute' into the 'new_owner_element', and change the
    // 'attribute' to the attribute's value (just to handle attribute changes / callbacks etc in the
    // 'new_owner_element')
    if (old_attribute)
        detail::replace(old_attribute, std::move(attribute));
    else
    {
        detail::append(std::move(attribute), q);
        detail::change(attribute.get(), std::move(attribute->d_func()->value));
    }

    // Return the 'old_attribute'.
    return old_attribute;
}


auto dom::element_private::remove_attribute(attr* attribute) -> attr*
{
    // Get the list of current attributes in the 'owner_element', and check if the 'attribute' is contained in the
    // attribute list. If it is contained, process with the rest of the steps, otherwise return the 'attribute' straight
    // away.
    if (ranges::contains(attribute_list, attribute, ext::underlying))
    {
        // Change the value to "" (calls update methods), and then call the 'remove()' method (calls update methods).
        // Remove the attribute from the list, and then return the removed attribute.
        detail::change(attribute, u"");
        detail::remove(attribute);
        attribute_list |= ranges::actions::remove(attribute, ext::underlying);
    }

    return attribute;
}


auto dom::element_private::toggle_attribute(
        element* owner_element,
        attr* attribute,
        ext::optional<ext::boolean> force,
        ext::string_view qualified_name,
        ext::string_view namespace_)
        -> attr*
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
            : detail::append(detail::create(qualified_name.data(), namespace_.data(), u"", u"", owner_element->d_func()->node_document.get()), owner_element);

    return attribute;
}
