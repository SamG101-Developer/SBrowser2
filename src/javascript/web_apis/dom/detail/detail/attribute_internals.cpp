#include "attribute_internals.hpp"

















#include <range/v3/algorithm/contains.hpp>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/action/remove.hpp>
#include <range/v3/view/view.hpp>

#include <QWidget>



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






