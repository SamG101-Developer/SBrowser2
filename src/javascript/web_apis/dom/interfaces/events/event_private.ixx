module;
#include "ext/macros.hpp"


export module apis.dom.event:p;
import apis.dom_object;

import apis.dom.types;
import ext.core;


DEFINE_PRIVATE_CLASS(dom, event)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(event);
    using touch_targets_t = ext::vector<event_target*>;
    using path_t = ext::vector<std::unique_ptr<detail::event_path_struct_t>>;

public:
    ext::string  type;
    ext::boolean bubbles;
    ext::boolean cancelable;
    ext::boolean composed;

    std::observer_ptr<event_target> target;
    std::observer_ptr<event_target> current_target;
    std::observer_ptr<event_target> related_target;

    ext::number<ushort> event_phase;
    ext::number<double> time_stamp;
    ext::boolean is_trusted;

    touch_targets_t touch_targets;
    path_t path;

    ext::boolean stop_propagation_flag = false;
    ext::boolean stop_immediate_propagation_flag = false;
    ext::boolean canceled_flag = false;
    ext::boolean in_passive_listener_flag = false;
    ext::boolean initialized_flag = true;
    ext::boolean dispatch_flag = false;
};
