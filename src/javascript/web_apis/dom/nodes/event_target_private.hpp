#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_EVENT_TARGET_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_EVENT_TARGET_PRIVATE_HPP

#include "dom_object_private.hpp"

#include "ext/any.hpp"
#include "ext/functional.hpp"
#include "ext/pimpl.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
namespace dom::nodes {class event_target;}
namespace dom::events {class event;}


DEFINE_PRIVATE_CLASS(dom::nodes, event_target) : dom_object_private
{
    ext::function<nodes::event_target*(events::event*)> get_the_parent;
    ext::vector<ext::map<ext::string, ext::any>> event_listeners;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_EVENT_TARGET_PRIVATE_HPP
