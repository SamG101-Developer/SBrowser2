#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_ELEMENT_PRIVATE_HPP

#include "ext/boolean.hpp"
#include "ext/pimpl.hpp"
#include "ext/queue.hpp"
#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(html)


DEFINE_PRIVATE_CLASS(dom::nodes, element)
{
    ext::string is;
    detail::custom_element_definition_t* custom_element_definition;
    detail::custom_element_state_t custom_element_state;
    ext::queue<detail::reaction_t*> custom_element_reaction_queue;
    std::unique_ptr<html::detail::browsing_context_t> nested_browsing_context;

    /* FULLSCREEN */
    ext::boolean fullscreen_flag;

    /* HTML */
    ext::boolean click_in_progress_flag;

    /* INTERSECTION_OBSERVERS */
    ext::vector<intersection_observer::detail::intersection_observer_registration_t*> registration_intersection_observers;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_ELEMENT_PRIVATE_HPP
