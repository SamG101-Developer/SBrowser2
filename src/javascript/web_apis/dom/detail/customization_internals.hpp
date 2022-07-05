#ifndef SBROWSER2_CUSTOMIZATION_INTERNALS_HPP
#define SBROWSER2_CUSTOMIZATION_INTERNALS_HPP


#include <ext/boolean.hpp>
#include <ext/string.hpp>
namespace dom::nodes {class element;}
namespace html::elements {class html_element;}
namespace html::elements {class html_unknown_element;}

namespace dom::detail::customization_internals
{
    // detail structs and enums
    enum custom_element_state_t {CUSTOM, UNCUSTOMIZED, PRECUSTOMIZED, UNDEFINED, FAILED, NONE};
    struct custom_element_reactions_stack;
    struct custom_element_definition;
    struct reaction {};
    struct upgrade_reaction : public reaction {};
    struct callback_reaction : public reaction {};

    using element_interface_t = nodes::element;

    // custom element creation and upgrading
    auto create_an_element(
            nodes::document* document,
            ext::string_view local_name,
            ext::string_view namespace_,
            ext::string_view prefix = "",
            ext::string_view is = "",
            ext::boolean_view synchronous_custom_elements_flag = false)
            -> nodes::element*;

    auto upgrade_element(
            custom_element_definition* definition,
            nodes::element* element)
            -> void;

    auto try_to_upgrade_element(
            nodes::element* element)
            -> void;

    auto lookup_custom_element_definition(
            nodes::document* document,
            ext::string_view namespace_,
            ext::string_view local_name,
            ext::string_view is)
            -> custom_element_definition*;

    // enqueue methods for custom elements
    auto enqueue_element_on_appropriate_element_queue(
            nodes::element* element)
            -> void;

    template <typename ...Args>
    auto enqueue_custom_element_callback_reaction(
            nodes::element* element,
            ext::string_view callback_name,
            Args&&... args)
            -> void;

    auto enqueue_custom_element_upgrade_reaction(
            nodes::element* element,
            custom_element_definition* definition)
            -> void;

    auto enqueue_custom_element_reaction(
            std::queue<nodes::element*>& element_queue)
            -> void;

    // custom element checks
    auto is_valid_custom_element_name(
            ext::string_view element_name)
            -> ext::boolean;

    auto is_custom_node(
            nodes::element* element)
            -> ext::boolean;

    // other custom element methods
    auto invoke_custom_elements_reactions(
            std::queue<nodes::element*>& queue)
            -> void;

    auto is_custom(
            nodes::element* element)
            -> ext::boolean;
}


#endif //SBROWSER2_CUSTOMIZATION_INTERNALS_HPP
