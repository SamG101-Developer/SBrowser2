#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_EVENT_TARGET_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_EVENT_TARGET_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"



#include "ext/map.ixx"
#include "ext/string.hpp"
#include "ext/vector.hpp"
namespace dom::nodes {class event_target;}
namespace dom::events {class event;}


DEFINE_PRIVATE_CLASS(dom::nodes, event_target)
        : virtual dom_object_private
{
    MAKE_QIMPL(event_target);

    auto get_the_parent(events::event*) -> nodes::event_target*;

    ext::vector<ext::map<ext::string, ext::any>> event_listeners;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_EVENT_TARGET_PRIVATE_HPP
