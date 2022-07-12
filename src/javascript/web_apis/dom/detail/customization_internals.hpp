#ifndef SBROWSER2_CUSTOMIZATION_INTERNALS_HPP
#define SBROWSER2_CUSTOMIZATION_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include <queue>
#include <stack>
namespace dom::nodes {class document;}
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

    template <typename T>
    auto element_interface(
            ext::string_view local_name,
            ext::string_view namespace_)
            -> std::unique_ptr<T>;

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

    auto enqueue_custom_element_callback_reaction(
            nodes::element* element,
            ext::string_view callback_name,
            auto&&... args)
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


struct dom::detail::customization_internals::custom_element_reactions_stack
{
    std::queue<nodes::element*> backup_element_queue;
    std::queue<nodes::element*> current_element_queue() {return queues.top();};
    std::stack<std::queue<nodes::element*>> queues;
    ext::boolean processing_backup_element_queue_flag = false;

    auto operator->() -> auto {return &queues;}
};


struct dom::detail::customization_internals::custom_element_definition
{
    using lifecycle_callback_t = std::function<void()>;
    using html_element_constructor_t = std::function<nodes::element*()>;

    ext::boolean form_associated;
    ext::boolean disable_internals;
    ext::boolean disable_shadow;

    ext::string name;
    ext::string local_name;

    ext::vector<ext::string> observed_attributes;
    ext::vector<nodes::element*> construction_stack;
    html_element_constructor_t constructor;

    ext::map<ext::string, lifecycle_callback_t> lifecycle_callbacks
    {
            {"connectedCallback"     , [] {}}, {"disconnectedCallback"    , [] {}},
            {"adoptedCallback"       , [] {}}, {"attributeChangedCallback", [] {}},
            {"formAssociatedCallback", [] {}}, {"formDisabledCallback"    , [] {}},
            {"formResetCallback"     , [] {}}, {"formStateRestoreCallback", [] {}}
    };
};


#endif //SBROWSER2_CUSTOMIZATION_INTERNALS_HPP
