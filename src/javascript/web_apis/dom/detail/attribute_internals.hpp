#ifndef SBROWSER2_ATTRIBUTE_INTERNALS_HPP
#define SBROWSER2_ATTRIBUTE_INTERNALS_HPP

#include <web_apis/dom/nodes/attr.hpp>
#include <web_apis/dom/nodes/element.hpp>
#include <web_apis/dom/detail/customization_internals.hpp>
#include <web_apis/dom/detail/observer_internals.hpp>

namespace dom::detail::attribute_internals
{
    // handle changes
    auto handle_attributes_changes(
            const nodes::attr* attribute,
            const nodes::element* owner_element,
            const ext::string& old_value,
            const ext::string& new_value)
            -> void;

    // general mutations to attributes
    auto change(
            nodes::attr* attribute,
            const ext::string& new_value)
            -> void;

    auto append(
            nodes::attr* attribute,
            nodes::element* new_owner_element)
            -> void;

    auto remove(
            nodes::attr* attribute)
            -> void;

    auto replace(
            nodes::attr* old_attribute,
            nodes::attr* new_attribute)
            -> void;

    // get attribute
    auto get_attribute_value(
            const nodes::element* owner_element,
            const ext::string& local_name,
            const ext::string& namespace_)
            -> ext::string;

    auto get_attribute_by_name(
            const nodes::element* owner_element,
            const ext::string& qualified_name)
            -> nodes::attr*;

    auto get_attribute_by_ns(
            const nodes::element* owner_element,
            const ext::string& local_name,
            const ext::string& namespace_)
            -> nodes::attr*;

    // set attribute

    auto set_attribute_by_name(
            nodes::element* owner_element,
            const ext::string& qualified_name,
            const ext::string& value)
            -> nodes::attr*;

    auto set_attribute_by_ns(
            nodes::element* owner_element,
            const ext::string& qualified_name,
            const ext::string& namespace_,
            const ext::string& value)
            -> nodes::attr*;

    auto set_attribute(
            nodes::element* new_owner_element,
            nodes::attr* attribute)
            -> nodes::attr*;

    // remove attribute
    auto remove_attribute_by_name(
            nodes::element* owner_element,
            const ext::string& qualified_name)
            -> nodes::attr*;

    auto remove_attribute_by_ns(
            nodes::element* owner_element,
            const ext::string& local_name,
            const ext::string& namespace_)
            -> nodes::attr*;

    auto remove_attribute(
            nodes::element* owner_element,
            nodes::attr* attribute)
            -> nodes::attr*;

    // toggle attribute
    auto toggle_attribute_by_name(
            const nodes::element* owner_element,
            const ext::string& qualified_name,
            bool force)
            -> nodes::attr*;

    auto toggle_attribute_by_ns(
            const nodes::element* owner_element,
            const ext::string& local_name,
            const ext::string& namespace_, bool force)
            -> nodes::attr*;

    auto toggle_attribute(
            nodes::attr* attribute,
            bool force)
            -> nodes::attr*;

    // setter helpers
    auto set_attribute_value(
            nodes::element* owner_element,
            const ext::string& local_name,
            const ext::string& value,
            const ext::string& prefix = "",
            const ext::string& namespace_ = "")
            -> nodes::attr*;

    auto set_existing_attribute_value(
            nodes::attr* attribute,
            const ext::string& value)
            -> void;
}


auto dom::detail::attribute_internals::handle_attributes_changes(
        const nodes::attr* attribute,
        const nodes::element* owner_element,
        const ext::string& old_value,
        const ext::string& new_value)
        -> void
{
    // get common variables
    auto local_name = attribute->local_name();
    auto namespace_ = attribute->namespace_uri();

    // queue a mutation record describing the change in the attribute
    observer_internals::queue_mutation_record("attributes", owner_element, local_name, namespace_, old_value, {}, {}, nullptr, nullptr);

    // if the element is custom, enqueue a custom element reaction
    if (owner_element->m_custom_element_state == customization_internals::CUSTOM)
        customization_internals::enqueue_custom_element_callback_reaction(owner_element, "attributeCallbackChanged", {local_name, old_value, new_value, namespace_});

    // notify the node to execute its attribute-change behaviour steps
    owner_element->m_dom_behaviour.attribute_change_steps(local_name, old_value, new_value, namespace_);
}


#endif //SBROWSER2_ATTRIBUTE_INTERNALS_HPP
