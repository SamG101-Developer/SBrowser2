#ifndef SBROWSER2_CUSTOMIZATION_INTERNALS_HPP
#define SBROWSER2_CUSTOMIZATION_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/queue.hpp"
#include "ext/stack.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(dom)
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace html::elements {class html_element;}
namespace html::elements {class html_unknown_element;}

namespace dom::detail
{
    auto element_interface(
            ext::string_view local_name,
            ext::string_view namespace_)
            -> nodes::element*;

    // custom element creation and upgrading
    auto create_an_element(
            nodes::document* document,
            const ext::string& local_name,
            const ext::string& namespace_,
            const ext::string& prefix = "",
            const ext::string& is = "",
            const ext::boolean& synchronous_custom_elements_flag = false)
            -> nodes::element*;

    auto upgrade_element(
            custom_element_definition_t* definition,
            nodes::element* element)
            -> void;

    auto try_to_upgrade_element(
            nodes::element* element)
            -> void;

    auto lookup_custom_element_definition(
            const nodes::document* document,
            ext::string_view namespace_,
            ext::string_view local_name,
            ext::string_view is)
            -> custom_element_definition_t*;

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
            custom_element_definition_t* definition)
            -> void;

    auto enqueue_custom_element_reaction(
            ext::queue<nodes::element*>& element_queue)
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
            ext::queue<nodes::element*>& queue)
            -> void;

    auto is_custom(
            nodes::element* element)
            -> ext::boolean;
}


struct dom::detail::custom_element_reactions_stack_t
{
    ext::queue<nodes::element*> backup_element_queue;
    ext::queue<nodes::element*> current_element_queue() {return queues.top();};
    ext::stack<ext::queue<nodes::element*>> queues;
    ext::boolean processing_backup_element_queue_flag = false;

    auto operator->() -> auto {return &queues;}
};


struct dom::detail::custom_element_definition_t
{
    using lifecycle_callback_t = ext::function<void()>;
    using html_element_constructor_t = ext::function<nodes::element*()>;

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
