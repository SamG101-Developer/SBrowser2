#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_IDLE_DEADLINE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_IDLE_DEADLINE_HPP

#include "dom_object.hpp"
#include USE_INNER_TYPES(high_resolution_time)
namespace background_tasks {class idle_deadline;}


class background_tasks::idle_deadline
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(idle_deadline);
    idle_deadline() = default;

public js_methods:
    auto time_remaining() -> high_resolution_time::detail::dom_high_res_time_stamp_t;

public js_properties:
    ext::property<ext::boolean> did_timeout;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_IDLE_DEADLINE_HPP
