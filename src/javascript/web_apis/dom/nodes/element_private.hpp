#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_ELEMENT_PRIVATE_HPP

#include "dom/nodes/node_private.hpp"

#include "ext/boolean.hpp"
#include "ext/pimpl.hpp"
#include "ext/queue.hpp"
#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(html)


DEFINE_PRIVATE_CLASS(dom::nodes, element)
        : node_private
        , mixins::child_node_private
        , mixins::document_or_element_node_private
        , mixins::non_document_type_child_node_private
        , mixins::parentable_node_private
        , mixins::slottable_private
        , aria::mixins::aria_mixin_private
        , css::css_web_animations::mixins::animatable_private
{
    ext::string namespace_;
    ext::string namespace_prefix;
    ext::string local_name;
    detail::custom_element_definition_t* custom_element_definition;
    detail::custom_element_state_t custom_element_state;
    ext::string is;

    shadow_root* shadow_root;
    ext::string id;
    ext::string class_;
    ext::string slot;

    ext::vector<std::unique_ptr<attr>> attribute_list;

    ext::queue<detail::reaction_t*> custom_element_reaction_queue;
    std::unique_ptr<html::detail::browsing_context_t> nested_browsing_context;

    /* FULLSCREEN */
    ext::boolean fullscreen_flag;

    /* HTML */
    ext::boolean click_in_progress_flag;

    /* INTERSECTION_OBSERVERS */
    ext::vector<std::unique_ptr<intersection_observer::detail::intersection_observer_registration_t>> registration_intersection_observers;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_ELEMENT_PRIVATE_HPP
