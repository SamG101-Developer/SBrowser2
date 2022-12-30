module;
#include <utility>


module apis.dom.attr:p;
import apis.dom.element;
import apis.dom.types;

import ext.core;


auto dom::attr_private::qualified_name() const -> ext::string
{
    // The qualified name of an attribute is the 'attribute's prefix followed by a ":", followed by the 'attribute's
    // local name.
    return namespace_prefix + u":" + local_name;
}


auto dom::attr_private::handle_attributes_changes(
        attr* attribute,
        class element* owner_element,
        ext::string_view old_value,
        ext::string_view new_value)
        -> void
{
    using detail::mutation_type_t;
    using detail::custom_element_state_t;

    // Queue a mutation record describing the change in the attribute. Pass the 'owner_element', 'local_name',
    // 'namespace_', and 'old_value' in.
    detail::queue_mutation_record(mutation_type_t::ATTRIBUTES, owner_element, local_name, namespace_, old_value, {}, {}, nullptr, nullptr);

    // If the element is custom, enqueue a custom element reaction, so that the callback relating to attribute changes
    // can execute. Most of the same parameters as the 'queue_mutation_record(...)' call are used.
    if (owner_element->d_func()->custom_element_state == custom_element_state_t::CUSTOM)
        detail::enqueue_custom_element_callback_reaction(owner_element, u"attributeCallbackChanged", local_name, old_value, new_value, namespace_);

    // Notify the node to execute its attribute-change behaviour steps
    owner_element->d_func()->attribute_change_steps(local_name, old_value, new_value, namespace_);
}


auto dom::attr_private::set_existing_attribute_value(ext::string&& value) -> void
{
    // If the 'attribute' doesn't have an owner element, then change the value normally (no need to call update
    // methods), but if there is an 'owner_element', then call the 'change(...)' method to call all the necessary
    // updates. This is because the update emthods require an owner element to have any effect at all.
    ACCESS_QIMPL;

    !element
            ? value = std::move(value)
            : detail::change(q, std::move(value));
}
