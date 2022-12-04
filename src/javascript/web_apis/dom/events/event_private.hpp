#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_EVENTS_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_EVENTS_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"



#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(dom)

namespace dom::nodes {class event_target;}


DEFINE_PRIVATE_CLASS(dom::events, event)
        : virtual dom_object_private
{
    MAKE_QIMPL(event);

    ext::string  type;
    ext::boolean bubbles;
    ext::boolean cancelable;
    ext::boolean composed;

    std::observer_ptr<nodes::event_target> target;
    std::observer_ptr<nodes::event_target> current_target;
    std::observer_ptr<nodes::event_target> related_target;

    ext::number<ushort> event_phase;
    ext::number<double> time_stamp;
    ext::boolean is_trusted;

    detail::touch_targets_t touch_targets;
    detail::path_t path;

    ext::boolean stop_propagation_flag = false;
    ext::boolean stop_immediate_propagation_flag = false;
    ext::boolean canceled_flag = false;
    ext::boolean in_passive_listener_flag = false;
    ext::boolean initialized_flag = true;
    ext::boolean dispatch_flag = false;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_EVENTS_EVENT_PRIVATE_HPP
